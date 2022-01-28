#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "IO.h"
#include "PIC.h"


void unmask_kb_irq() {
    outportb(PIC1_DATA_PORT, 0xFD);
}


#endif
