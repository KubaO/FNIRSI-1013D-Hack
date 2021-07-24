//----------------------------------------------------------------------------------------------------------------------------------

#ifndef DISPLAY_LIB_H
#define DISPLAY_LIB_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "font_structs.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define DISPLAY_DRAW_CLOCK_WISE             0
#define DISPLAY_DRAW_COUNTER_CLOCK_WISE     1

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagDisplayData   DISPLAYDATA,  *PDISPLAYDATA;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagDisplayData
{
  PFONTDATA  font;
  uint16     fg_color;
  uint16     bg_color;
  uint16    *screenbuffer;
  uint16    *sourcebuffer;         //For copy to screen or slide function the source from where to get the data from
  uint16    *destbuffer;           //For copy from screen the destination where to put the data
  uint16    *linepointer;
  uint16     xpos;
  uint16     ypos;
  uint16     width;
  uint16     height;
  uint16     pixelsperline;
};

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_position(uint16 xpos, uint16 ypos);
void display_set_dimensions(uint16 width, uint16 height);
void display_set_font(PFONTDATA font);
void display_set_fg_color(uint32 color);
void display_set_bg_color(uint32 color);
void display_set_screen_buffer(uint16 *buffer);
void display_set_source_buffer(uint16 *buffer);
void display_set_destination_buffer(uint16 *buffer);

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_line(uint16 xstart, uint16 ystart, uint16 xend, uint16 yend);
void display_draw_horz_line(uint16 ypos, uint16 xstart, uint16 xend);
void display_draw_vert_line(uint16 xpos, uint16 ystart, uint16 yend);
void display_draw_rect(uint16 xpos, uint16 ypos, uint16 width, uint16 height);
void display_draw_rounded_rect(uint16 xpos, uint16 ypos, uint16 width, uint16 height, uint16 radius);
void display_draw_arc(uint16 xpos, uint16 ypos, uint16 radius, uint16 startangle, uint16 endangle, uint16 direction);

//----------------------------------------------------------------------------------------------------------------------------------

void display_fill_rect(uint16 xpos, uint16 ypos, uint16 width, uint16 height);
void display_fill_rounded_rect(uint16 xpos, uint16 ypos, uint16 width, uint16 height, uint16 radius);

//----------------------------------------------------------------------------------------------------------------------------------

void display_slide_top_rect_onto_screen(uint16 xpos, uint16 ypos, uint16 width, uint16 height, uint32 speed);

//----------------------------------------------------------------------------------------------------------------------------------

void display_copy_rect_from_screen(uint16 xpos, uint16 ypos, uint16 width, uint16 height);
void display_copy_rect_to_screen(uint16 xpos, uint16 ypos, uint16 width, uint16 height);

//----------------------------------------------------------------------------------------------------------------------------------

void display_copy_icon(const uint16 *icon, uint16 xpos, uint16 ypos, uint16 width, uint16 height);

//----------------------------------------------------------------------------------------------------------------------------------

void display_text(uint16 xpos, uint16 ypos, int8 *text);

//----------------------------------------------------------------------------------------------------------------------------------
//Variable width font handling functions

void draw_vw_character(uint16 character);

PFONTINFORMATION check_char_in_vw_font(PFONTINFORMATION info, uint16 character);

//----------------------------------------------------------------------------------------------------------------------------------
//Fixed width font handling functions

void draw_fw_character(uint16 character);
void render_fw_character(uint16 character);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* DISPLAY_LIB_H */
