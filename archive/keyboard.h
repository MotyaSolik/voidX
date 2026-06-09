#include "ports.h"
#include "vga.h"
#include "scancodes.h"

struct interrupt_frame;

char scode2char(uint8_t scancode);
__attribute__((interrupt)) void keyboard_handler(struct interrupt_frame* frame);