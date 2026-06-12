#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "drivers/idt.h"
#include "drivers/gdt.h"
#include "drivers/timer.h"
#include "drivers/pmm.h"
#include "drivers/paging.h"
#include "drivers/heap.h"
#include "utils.h"

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
        } else if (strcmp(user_input, "test") == 0) {
            kprintln("Waiting 3 secs...");
            sleep_s(3);
            kprintln("Done!");
        }
    
        else if (user_input[0] != '\0') {
            kerr("unknown: ");
            kerrln(user_input);
        } 
    }
    
}
