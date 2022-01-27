#include "../GDT.h"

gdtr_t gp;
gdt_entry_t gdt[6];


void gdt_set_gate(int num, unsigned long base, unsigned long limit, char access, unsigned char gran) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].gran = (limit >> 16) & 0x0F;
    gdt[num].gran |= (gran & 0xF0);
    gdt[num].access = access;
}


void gdt_install() {
	gp.limit = (sizeof(struct gdt_entry) * 6) - 1;
	gp.base = (unsigned int)&gdt;
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	write_tss(5, 0x10, 0x0);
	_gdt_flush();    
}
