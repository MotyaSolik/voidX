#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "drivers/idt.h"
#include "drivers/gdt.h"

void kernel_main(void) {
    vga_init();
    uint8_t last_scancode = 0;
    kprintln("VNL Kernel v0.0.1");
    kprintln("Initializating VNL...");
    init_gdt();
    init_idt_kb();
    __asm__ volatile("int $33"); 
    kprintln("VNL Ready!");
    kprint("Write something:");

    while(1) {
        __asm__ volatile("hlt"); 
    }
    
}
