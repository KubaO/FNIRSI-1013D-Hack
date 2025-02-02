//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

#include "ccu_control.h"
#include "spi_control.h"
#include "timer.h"
#include "interrupt.h"
#include "display_control.h"
#include "fpga_control.h"
#include "touchpanel.h"
#include "power_and_battery.h"

#include "fnirsi_1013d_scope.h"
#include "display_lib.h"
#include "scope_functions.h"
#include "statemachine.h"

#include "sd_card_interface.h"
#include "ff.h"

#include "usb_interface.h"

#include "arm32.h"

#include "variables.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

extern IRQHANDLERFUNCION interrupthandlers[];

//----------------------------------------------------------------------------------------------------------------------------------

int main(void)
{
  //Initialize data in BSS section
  memset(&BSS_START, 0, &BSS_END - &BSS_START);
  
  //Initialize the clock system
  sys_clock_init();
  
  //Instead of full memory management just the caches enabled
  arm32_icache_enable();
  arm32_dcache_enable();
  
  //Clear the interrupt variables
  memset(interrupthandlers, 0, 256);
  
  //Setup timer interrupt
  timer0_setup();
  
  //Setup power monitoring
  power_interrupt_init();
  
  //Setup battery monitoring
  battery_check_init();
  
  //Enable interrupts only once. In the original code it is done on more then one location.
  arm32_interrupt_enable();
  
  //Initialize SPI for flash (PORT C + SPI0)
  sys_spi_flash_init();
  
  //Initialize FPGA (PORT E)
  fpga_init();
  
  //Turn of the display brightness
  fpga_set_backlight_brightness(0x0000);
  
  //Initialize display (PORT D + DEBE)
  sys_init_display(SCREEN_WIDTH, SCREEN_HEIGHT, (uint16 *)maindisplaybuffer);
  
  //Setup the display library for the scope hardware
  scope_setup_display_lib();
  
  //Setup the touch panel interface
  tp_i2c_setup();

  //Setup and check SD card on file system being present
  if(f_mount(&fs, "0", 1))
  {
    //Show SD card error message on failure
    //Set max screen brightness
    fpga_set_backlight_brightness(0xEA60);

    //Clear the display
    display_set_fg_color(0x00000000);
    display_fill_rect(0, 0, 800, 480);

    //Display the message in red
    display_set_fg_color(0x00FF0000);
    display_set_font(&font_3);
    display_text(30, 50, "SD ERROR");
    
    //On error just hang
    while(1);
  }
  
//Just to test it displaying of the new startup screen  
//  fpga_set_backlight_brightness(0xEA60);
//  scope_draw_startup_screen();
  
//  while(1);
  
  
  //In the original code there is some hardware check function here. Actions are not performed unless some data in the FLASH is not set
  //This tests the basic hardware and verifies the touch panel
  
  //Setup the USB interface
  usb_device_init();
  
  //Load configuration data from FLASH
  scope_load_configuration_data();

  //Enable or disable the channels based on the scope loaded settings
  fpga_set_channel_1_enable();
  fpga_set_channel_2_enable();
  
  //Set the volts per div for each channel based on the loaded scope settings
  fpga_set_channel_1_voltperdiv();
  fpga_set_channel_2_voltperdiv();
  
  //Set the channels AC or DC coupling based on the loaded scope settings
  fpga_set_channel_1_coupling();
  fpga_set_channel_2_coupling();
  
  //Enable something in the FPGA
  fpga_enable_system();
  
  //Initialize the communication with the parameter IC
  fpga_init_parameter_ic();
  
  //Setup the trigger system in the FPGA based on the loaded scope settings
  fpga_set_trigger_timebase();
  fpga_set_trigger_channel();
  fpga_swap_trigger_channel();   //This is a bit redundant since the correct channel should be in the loaded settings.
  fpga_set_trigger_edge();
  fpga_set_trigger_level();
  fpga_set_trigger_mode();
  
  fpga_set_channel_1_offset();
  fpga_set_channel_2_offset();
  
  //Some initialization of the FPGA??. Data written with command 0x3C
  fpga_set_battery_level();      //Only called here and in hardware check

  //In the original code there is another hardware check function here. Actions are not performed unless some data in the FLASH is not set
  //This is for testing the analog response
  //When all tests run through the flash is updated to no longer run the hardware tests.
  

  //Here a function is called that looks at some system file????? Firmware upgrade!!!

  
  //Setup the main parts of the screen
  scope_setup_main_screen();
    
  //Set screen brightness
  fpga_set_translated_brightness();
  
  //Monitor the battery, process and display trace data and handle user input until power is switched off
  while(1)
  {
    //Monitor the battery status
    battery_check_status();
    
    //Go through the trace data and make it ready for displaying
    scope_process_trace_data();
    
    //Display the trace data
    scope_display_trace_data();
    
    //Handle the touch panel input
    touch_handler();
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
