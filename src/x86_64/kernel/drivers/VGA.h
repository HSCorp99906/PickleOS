#ifndef VGA_H
#define VGA_H

#include "../util/strings.h"


void fillScreen(char** vga, unsigned char bg, unsigned char fg);
void kputs(const char* string, char** vga, unsigned short nlDepth);


#endif
