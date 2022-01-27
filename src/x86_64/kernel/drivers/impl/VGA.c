#include "../VGA.h"


void fillScreen(char** vga, unsigned char bg, unsigned char fg) {
    unsigned short attrib = (bg << 4) | (fg & 0x0F);
    *vga = (char*)0xB8000;

    for (int i = 0; i < 5000; ++i) {
        **vga = ' ';
        *vga += 1;
        **vga = attrib;
        *vga += 1;
    }

    *vga = (char*)0xB8000;

}


void kputs(const char* string, char** vga, unsigned short nlDepth) {
    const unsigned short VGA_WIDTH = 80;

    for (int i = 0; i < strlen(string); ++i) {
        **vga = string[i];
        *vga += 2;
    }

    if (nlDepth > 0) {
        for (int i = 0; i < VGA_WIDTH - strlen(string); ++i) {
            **vga = ' ';
            *vga += 2;
        }

        if (nlDepth > 1) {
            for (int i = 0; i < nlDepth - 1; ++i) {
                for (int j = 0; j < VGA_WIDTH; ++j) {
                    **vga = ' ';
                    *vga += 2;
                }
            }
        }
    }
}
