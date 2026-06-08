#include "drivers/vga.h"

void kernel_main(void) {
    vga_init();
    kprintln("VNL Kernel v0.0.1");
    kprintln("Initializating VNL...");
}
