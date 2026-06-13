#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include "ports.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_COLOR_WHITE_ON_BLACK 0x0F

void vga_set_color(uint8_t color);
void vga_init(void);
void vga_disable_cursor(void);
void kclear_screen(void);
void kprint_char(char c);
void kprint_char_c(char c, uint8_t col);
void kprint(const char* str);
void kerr(const char* str);
void kprintln(const char* str);
void kerrln(const char* str);
void kprint_hex(uint32_t n);
void kslog(const char* str);
#endif