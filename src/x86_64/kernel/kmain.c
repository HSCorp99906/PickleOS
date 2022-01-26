#include "drivers/VGA.h"

char* vga = (char*)0xB8000;


int _start() {
    fillScreen(&vga, 0x1, 0xE);
    kputs("Kernel Loaded!", &vga, 3); 
}
