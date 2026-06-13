//#include <vga.h">
#include <keyboard.h>
#include <idt.h>
#include <gdt.h>
#include <timer.h>
#include <pmm.h>
#include <paging.h>
#include <heap.h>
#include <ata.h>
#include "utils.h"
#include "fs/ff.h"
#include <timer.h>

struct registers;
extern void exception_handler_c(struct registers regs); 


void kernel_main(void) {
    vga_init();
    kprintln("VNL Kernel v0.1.0");
    kprintln("Initializating VNL...");
    init_gdt();
    init_idt(); 
    init_timer();
    pmm_init(128 * 1024 * 1024);
    init_paging();
    init_heap();
    vga_set_color(0x0B);
    kprintln("VNL Ready!");
    vga_set_color(0x0F);
    char user_input[256];
    kprintln("vxsh v0.1.0");
    vga_set_color(0x07);
    kprintln("Type 'help' for list of commands");
    vga_set_color(0x0F);
    while(1) {
        kprint("voidx> ");
        input_line(user_input);

        if (strcmp(user_input, "help") == 0) {
            kprint("Available commands:\n");
            kprint("  help  - Show this list\n");
            kprint("  clear - Clear the screen\n");
            kprint("  hello - Say hello to the creator\n");
        } else if (strcmp(user_input, "clear") == 0) {
            kclear_screen();
        } else if (strcmp(user_input, "hello") == 0) {
            kprintln("Hello, VoidDuck! VoidX is working!");
        }
    
        else if (user_input[0] != '\0') {
            kerr("unknown: ");
            kerrln(user_input);
        } 
    }
    
}
