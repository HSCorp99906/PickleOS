#include "../PIC.h"


void send_eoi() {
    outportb(0x20, 0x20);   
}
