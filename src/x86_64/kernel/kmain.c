#include "drivers/VGA.h"
#include "drivers/IO.h"

char* vga = (char*)0xB8000;


void panic(const char* const PANIC_MESSAGE) {
    outportb(0x3D4, 0x0A);
    outportb(0x3D5, 0x20);
    fillScreen(&vga, 0x4, 0xF);
    kputs("*** KERNEL PANIC! ***", &vga, 2);
    kputs(PANIC_MESSAGE, &vga, 0);
    __asm__ __volatile__("cli; hlt");
}


int _start() {
    fillScreen(&vga, 0x1, 0xE);
    kputs("Kernel Loaded!", &vga, 1);
    return 0;
}
