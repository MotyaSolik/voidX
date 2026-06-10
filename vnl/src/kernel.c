#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "drivers/idt.h"
#include "drivers/gdt.h"

void kernel_main(void) {
    vga_init();
    kprintln("VNL Kernel v0.0.1");
    kprintln("Initializating VNL...");
    init_gdt();
    init_idt_kb(); 
    kprintln("VNL Ready!");

    char user_input[256];
    kprint("Write something:");
    input_line(user_input);
    kprint("You writed:");
    kprint(user_input);

    while(1) {
        __asm__ volatile("hlt"); 
    }
    
}
