#include "keyboard.h"

const char kbd_us_set1[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',    
  '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',  
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',    0,  
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',    
 '\'', '`',   0, '\\', 'z', 'x', 'c', 'v', 'b', 'n',   
  'm', ',', '.', '/',   0, '*',   0, ' ',   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,
    0,   0,   0,   0,   0,   0,   0,   0
};


const char kbd_us_set1_shift[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',    
  '(', ')', '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R',  
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',    0,  
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',    
  '"', '~',   0, '|', 'Z', 'X', 'C', 'V', 'B', 'N',    
  'M', '<', '>', '?',   0, '*',   0, ' ',   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   
    0,   0,   0,   0,   0,   0,   0,   0                 
};

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
void keyboard_handler_c(void) {
    uint8_t scancode = inb(0x60);
    char charc = scode2char(scancode);
    

    if (charc != 0) {
        kprint_char(charc);
    }

    outb(0x20, 0x20); 
    
}
