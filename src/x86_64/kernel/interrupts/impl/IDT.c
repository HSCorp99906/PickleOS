#include "../IDT.h"


static idt_entry32_t idt32[IDT_MAX_ENTRIES];
static idtr32_t idtr32;



void set_idt_desc(unsigned char entry, void* isr, uint8_t flags) {
    idt_entry32_t* desc = &idt32[entry];
    desc->isr_addr_low = (uint32_t)isr & 0xFFFF;
    desc->kernel_cs = 0x08;
    desc->reserved = 0x0;
    desc->attr = flags;
    desc->isr_addr_high = ((uint32_t)isr >> 16) & 0xFFFF;
}



void init_idt32() {
    unsigned char a1,a2;
    a1 = inportb(0x21);             // Get master mask.
    a2 = inportb(0xA1);             // Get slave mask.

    outportb(0x20,0x10 | 0x01);     // Tell the PIC we want to initialize it
    outportb(0xA0,0x10 | 0x01);
    outportb(0x21, 0x20);         // Master PIC offset.
    outportb(0xA1, 0x28);         // Slave PIC offset.

    outportb(0x21,0x04);            // Tell master PIC there is a slave PIC at IRQ2.
    outportb(0xA1,0x02);            // Tell slave PIC its cascade identity.

    outportb(0x21,0x01);            // Put the master PIC into 8086 mode.
    outportb(0xA1,0x01);            // Put the slave PIC into 8086 mode.

    outportb(0x21, a1);              // Restore the masks.
    outportb(0xA1, a2);

    idtr32.lim = (uint16_t)(sizeof(idt32));
    idtr32.base = (uint32_t)&idt32;
    __asm__ __volatile__("lidt %0" : : "memory"(idtr32));
}
