#ifndef IDT_H
#define IDT_H

#define TRAP_GATE_FLAGS 0x8F
#define INT_GATE_FLAGS 0x8E

#define IDT_MAX_ENTRIES 256

#include <stddef.h>
#include <stdint.h>


typedef struct {
    uint16_t isr_addr_low;
    uint16_t kernel_cs;
    uint8_t reserved;
    uint8_t attr;
    uint16_t isr_addr_high;
} __attribute__((packed)) idt_entry32_t;


typedef struct {
    uint16_t lim;
    uint32_t base;
} __attribute__((packed)) idtr32_t;


// Int frame that gets pushed to stack.
typedef struct {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t sp;
    uint32_t ss;
} __attribute__((packed)) int_frame32_t;


void set_idt_desc(unsigned char entry, void* isr, uint8_t flags);
void init_idt32();

#endif
