#ifndef GDT_H
#define GDT_H

typedef struct {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char gran;
    unsigned char base_high;
} __attribute__((packed)) gdt_entry_t;


typedef struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) gdt_pointer_t;


void gdt_install();
void _gdt_flush();       // Will write this in assembly.
void gdt_set_gate(int entry, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);



#endif
