#include <stdint.h>
#include <timer.h>

volatile uint32_t timer_ticks = 0;
volatile int need_check_crash = 0;

void init_timer(void) {
    uint16_t divisor = 1193;

    outb(0x43, 0x36);

    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}


void timer_handler_c(void) {
    timer_ticks++;

    if (timer_ticks % 5000 == 0) {
        need_check_crash = 1;
    }
    
    outb(0x20, 0x20);
}

void sleep(uint32_t ms) {
    uint32_t start_ticks = timer_ticks;

    while ((timer_ticks - start_ticks) < ms) {
        __asm__ volatile("hlt");
    }
}


void sleep_s(uint32_t sec) {
    uint32_t ms = sec * 1000;
    sleep(ms);
}