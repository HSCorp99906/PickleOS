#ifndef PIC_H
#define PIC_H

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21

#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

#include "IO.h"

void send_eoi();


#endif
