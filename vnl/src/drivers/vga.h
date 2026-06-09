#ifndef VGA_H
#define VGA_H

#include "ports.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_COLOR_WHITE_ON_BLACK 0x0F

void vga_init(void);
void vga_disable_cursor(void);
void kclear_screen(void);
void kprint_char(char c);
void kprint(const char* str);
void kprintln(const char* str);

#endif