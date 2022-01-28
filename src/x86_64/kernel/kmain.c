#include "drivers/VGA.h"
#include "drivers/IO.h"
#include "interrupts/IDT.h"
#include "drivers/PIC.h"
#include "drivers/keyboard.h"
#include "drivers/graphics.h"
#include "memory/GDT.h"
#include "process/TSS.h"
#include "interrupts/exceptions.h"

char* vga_main = (char*)0xB8000;


void panic(const char* const PANIC_MESSAGE) {
    outportb(0x3d4, 0x0a);
    outportb(0x3d5, 0x20);
    fillScreen(&vga_main, 0x4, 0xf);
    kputs("*** kernel panic! ***", &vga_main, 2);
    kputs(PANIC_MESSAGE, &vga_main, 0);
    __asm__ __volatile__("cli; hlt");
}

void panicNoMsg() {
    outportb(0x3d4, 0x0a);
    outportb(0x3d5, 0x20);
    fillScreen(&vga_main, 0x4, 0xf);
    kputs("*** kernel panic! ***", &vga_main, 2);
    __asm__ __volatile__("cli; hlt");
}

__attribute__((interrupt)) static void pic_isr_stub(int_frame32_t* frame) { 
    inportb(0x60);
    send_eoi();
}


int _start() {
    init_idt32();
    set_idt_desc(0x21, pic_isr_stub, INT_GATE_FLAGS);

    // Exceptions.
    set_idt_desc(0x0, div_0_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0x4, overflow_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0x5, bre_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0x6, invld_opcode_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0x7, dev_na_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0x8, double_fault_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0x9, cso_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0xA, invld_tss_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0xB, seg_np_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0xC, ss_fault_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0xD, gp_fault_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0xE, page_fault_ex, TRAP_GATE_FLAGS);
    set_idt_desc(0xF, float_ex, TRAP_GATE_FLAGS);
    __asm__ __volatile__("sti");
    unmask_kb_irq();

    fillScreen(&vga_main, 0x1, 0xE); 
    draw_top_menu(MENU_ENTRY_1, 
            "UNUSED", "UNUSED", "UNUSED", "UNUSED");

    unsigned int esp;
    gdt_install();
    return 0;
}
