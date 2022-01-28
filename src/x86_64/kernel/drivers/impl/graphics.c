#include "../graphics.h"


void draw_top_menu(unsigned short flags, ch arg1, ch arg2, ch arg3, ch arg4) {
    // This should be used first thing at kernel.
    extern char* vga_main;
    vga_main = (char*)0xB8000;

    kputs("-------------------------------", &vga_main, 1);

    if (flags & MENU_ENTRY_1) {
        kputs(arg1, &vga_main, 0);
        kputs(" |X|", &vga_main, 0);
    } else {
        kputs(arg1, &vga_main, 0);
        kputs(" | |", &vga_main, 0);
    }

    if (flags & MENU_ENTRY_2) {
        kputs(arg2, &vga_main, 0);
        kputs(" |X|", &vga_main, 0);
    } else {
        kputs(arg2, &vga_main, 0);
        kputs(" ||", &vga_main, 0);
    }

    if (flags & MENU_ENTRY_3) {
        kputs(arg3, &vga_main, 0);
        kputs(" |X|", &vga_main, 0);
    } else {
        kputs(arg3, &vga_main, 0);
        kputs(" ||", &vga_main, 0);
    }

    if (flags & MENU_ENTRY_4) {
        kputs(arg4, &vga_main, 0);
        kputs(" |X|", &vga_main, 1);
    } else {
        kputs(arg4, &vga_main, 0);
        kputs(" ||", &vga_main, 1);
    }

    vga_main -= 80 + 2;

    kputs("-------------------------------", &vga_main, 2);
}
