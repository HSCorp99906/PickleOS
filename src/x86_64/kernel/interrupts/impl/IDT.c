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
    idtr32.lim = (uint16_t)(sizeof(idt32));
    idtr32.base = (uint32_t)&idt32;
    __asm__ __volatile__("lidt %0" : : "memory"(idtr32));
}
