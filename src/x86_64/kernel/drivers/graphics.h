#ifndef GRAPHICS_H
#define GRAPHICS_H

#define MENU_ENTRY_1 0x1
#define MENU_ENTRY_2 0x2
#define MENU_ENTRY_3 0x4
#define MENU_ENTRY_4 0x8
#define MENU_ENTRY_ALL 0x1 | 0x2 | 0x4 | 0x8
#define MENU_ENTRY_NONE 0x0

#include "VGA.h"
#include "../util/strings.h"

typedef char* ch;


void draw_top_menu(unsigned short flags, ch arg1, ch arg2, ch arg3, ch arg4);

#endif
