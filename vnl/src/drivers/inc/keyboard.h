#pragma once
#include "ports.h"
#include "vga.h"

struct interrupt_frame;

char scode2char(uint8_t scancode);
void keyboard_handler(struct interrupt_frame* frame);
void input_line(char* dest_buffer);
void input(void);
void input_stop(void);