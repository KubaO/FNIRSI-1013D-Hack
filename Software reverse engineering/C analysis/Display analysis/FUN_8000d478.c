void FUN_8000d478(int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  ushort uVar5;
  ushort *puVar6;
  int iVar7;
  uint uVar8;
  undefined2 *puVar9;
  ushort *puVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  
  puVar1 = PTR_DAT_8000d61c;
  uVar8 = *(uint *)(PTR_DAT_8000d61c + 4);
  *(ushort *)PTR_DAT_8000d61c =
       (ushort)(((uVar8 << 0x10) >> 0x1a) << 5) | (ushort)((uVar8 >> 0x13) << 0xb) |
       (ushort)((uVar8 << 0x18) >> 0x1b);
  uVar8 = *(uint *)(puVar1 + 8);
  *(ushort *)(puVar1 + 2) =
       (ushort)((uVar8 >> 0x13) << 0xb) | (ushort)(((uVar8 << 0x10) >> 0x1a) << 5) |
       (ushort)((uVar8 << 0x18) >> 0x1b);
  set_frame_to_global_pointer();
  uVar8 = DAT_8000d628;
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_8000d620;
  uVar13 = DAT_8000d628 >> 0x10 | 0x2e3;
  if (param_1 == 0) {
    uVar11 = 0;
    do {
      iVar12 = 0x3c;
      puVar6 = (ushort *)((*piVar3 + uVar11 * 0x640) - uVar8);
      puVar10 = (ushort *)(puVar2 + uVar11 * 0xf0);
      do {
        uVar5 = *puVar10;
        if (uVar5 == uVar13) {
          uVar5 = *(ushort *)puVar1;
        }
        iVar12 = iVar12 + -1;
        *puVar6 = uVar5;
        puVar6 = puVar6 + 1;
        puVar10 = puVar10 + 2;
      } while (iVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x37);
    set_display_color(DAT_8000d62c);
    FUN_80018e68(0x2e3,0x41,0x316,0x73,2);
  }
  else {
    set_display_color(*(uint *)(puVar1 + 8));
    FUN_80018ff0(0x2e3,0x41,0x316,0x73,2);
    uVar11 = 0;
    do {
      iVar12 = 0x3c;
      puVar9 = (undefined2 *)((*piVar3 + uVar11 * 0x640) - uVar8);
      puVar6 = (ushort *)(puVar2 + uVar11 * 0xf0);
      do {
        if (*puVar6 == uVar13) {
          *puVar9 = *(undefined2 *)(puVar1 + 2);
        }
        iVar12 = iVar12 + -1;
        puVar9 = puVar9 + 1;
        puVar6 = puVar6 + 2;
      } while (iVar12 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x37);
  }
  iVar4 = Start_Of_Screen_Mem;
  iVar12 = Screen_Frame_Buffer;
  uVar8 = 0x3f;
  do {
    iVar7 = uVar8 * 800 + 0x2df;
    copy_short((void *)(iVar4 + iVar7 * 2),(void *)(iVar12 + iVar7 * 2),0x40);
    uVar8 = uVar8 + 1;
  } while (uVar8 < 0x76);
  return;
}


