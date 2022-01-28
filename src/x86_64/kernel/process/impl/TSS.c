#include "../TSS.h"


// static uint32_t tssEntryBegin[25] = {0};        // Sets all to zero.
// static uint16_t tssEntryEnd[3] = {0};           // Sets all to zero.

tss_entry_t kernel_tss;

void tss_init(uint32_t idx, uint32_t kss, uint32_t kesp) {
    uint32_t base = (uint32_t)&kernel_tss;
}
