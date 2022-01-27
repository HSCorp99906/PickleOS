#include "../IDT.h"


static idt_entry32_t idt32[IDT_MAX_ENTRIES];
static idtr32_t idtr32;



void set_idt_desc(unsigned char entry, void* isr, uint8_t flags) {
    idt_enty32_t* desc = &idt32[entry];
    desc->isr_addr_low = (uint32_t)isr & 0xFFFF;
    desc->kernel_cs = 0x08;
    desc->
}
