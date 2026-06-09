#include "keyboard.h"

volatile int is_shift_pressed = 0;

char scode2char(uint8_t scancode) {
    if (scancode & 0x80) {
        uint8_t released_code = scancode & ~0x80;
        if (released_code == 0x2A || released_code == 0x36) {
            is_shift_pressed = 0;
            return 0;
        }
    } 
    else {
        if (scancode == 0x2A || scancode == 0x36) {
            is_shift_pressed = 1;
        } 
        else if (scancode < 128) {
            char ascii = is_shift_pressed ? kbd_us_set1_shift[scancode] : kbd_us_set1[scancode];
            
            if (ascii != 0) {
                return ascii;
            }
        }
    }
    return 0;
}
__attribute__((interrupt)) void keyboard_handler(struct interrupt_frame* frame) {
    uint8_t scancode = inb(0x60);
    char charc = scode2char(scancode);
    

    if (charc != 0) {
        kprint_char(charc);
    }

    outb(0x20, 0x20); 
    
}
