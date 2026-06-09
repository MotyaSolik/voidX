#include "drivers/vga.h"
#include "drivers/scancodes.h"



void kernel_main(void) {
    vga_init();
    uint8_t last_scancode = 0;
    kprintln("VNL Kernel v0.0.1");
    kprintln("Initializating VNL...");
    while(1) {
        uint8_t scancode = inb(0x60);

        if (scancode != last_scancode) {
            last_scancode = scancode;

            if ((scancode & 0x80) == 0) {
                char ascii = kbd_us_set1[scancode];
                
                if (ascii != 0) {
                    kprint_char(ascii); 
                }
            }
        }
    }
}
