#include "../GDT.h"

static gdt_entry_t gdt[3];
gdt_pointer_t _gp;


void gdt_set_gate(int entry, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
    gdt[entry].base_low = base & 0xFFFF;
    gdt[entry].base_middle = (base >> 16) & 0xFF;
    gdt[entry].base_high = (base >> 24) & 0xFF;
    gdt[entry].limit_low = limit & 0xFFFF;
    gdt[entry].gran = (limit >> 16) & 0x0F;
    gdt[entry].gran |= gran & 0xF0;
    gdt[entry].access = access;
}



void gdt_install() {
    _gp.limit = sizeof(gdt_entry_t) * 3;
    _gp.base = (unsigned int)&gdt;
    gdt_set_gate(0, 0, 0, 0, 0);
    // Code segment descriptor.
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // Data segment descriptor.
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // Load GDT.
    __asm__ __volatile__("lgdt %0" : : "memory"(_gp));
    // Flush CPU pipeline and switch CS.
    _gdt_flush();
}
