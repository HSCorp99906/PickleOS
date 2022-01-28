#include "../TSS.h"


// static uint32_t tssEntryBegin[25] = {0};        // Sets all to zero.
// static uint16_t tssEntryEnd[3] = {0};           // Sets all to zero.

tss_entry_t kernel_tss = {0};

void tss_init(uint32_t idx, uint32_t kss, uint32_t kesp) {
    uint32_t base = (uint32_t)&kernel_tss;
    gdt_set_gate(idx, base, base + sizeof(tss_entry_t), 0xE9, 0);
    kernel_tss.esp0 = kesp;
    kernel_tss.cs = 0x0B;
    kernel_tss.ds = 0x13;
    kernel_tss.es = 0x13;
    kernel_tss.fs = 0x13;
    kernel_tss.gs = 0x13;
    kernel_tss.ss = 0x13;
    __asm__ __volatile__("mov $0x28, %ax; ltr %ax");
}


void tss_set_stack(unsigned int kss, unsigned int kesp) {
    kernel_tss.ss0 = kss;
    kernel_tss.esp0 = kesp;
}
