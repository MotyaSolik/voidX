#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "drivers/idt.h"
#include "drivers/gdt.h"
#include "drivers/timer.h"
#include "utils.h"

void kernel_main(void) {
    vga_init();
    kprintln("VNL Kernel v0.1.0");
    kprintln("Initializating VNL...");
    init_gdt();
    init_idt(); 
    init_timer();
    kprintln("VNL Ready!");

    char user_input[256];
    kprintln("vxsh v0.1.0");
    kprintln("Type 'help' for list of commands");
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
        } else if (strcmp(user_input, "crash") == 0) {
            kprint("Triggering division by zero...\n");
            volatile int a = 5;
            volatile int b = 0;
            volatile int c = a / b;
        }

        else if (user_input[0] != '\0') {
            kerr("unknown: ");
            kerrln(user_input);
        } 
    }
    
}
