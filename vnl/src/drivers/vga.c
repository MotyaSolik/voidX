#include "vga.h"

static volatile char* video_memory = (volatile char*)0xB8000;

static int cursor_x = 0;
static int cursor_y = 0;

void vga_init(void) { vga_disable_cursor(); kclear_screen(); }

void vga_disable_cursor(void) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}


void kclear_screen(void) {
    cursor_x = 0;
    cursor_y = 0;
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i += 2) {
        video_memory[i] = ' ';
        video_memory[i+1] = VGA_COLOR_WHITE_ON_BLACK;
    }
}


void kslog(const  char* str) {
    kprint("[LOG]");
    kprintln(str);
}

void kprint_char(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } 
    // скип \r
    else if (c == '\r') {
        return;
    }
    else {
        int index = (cursor_y * VGA_WIDTH + cursor_x) * 2;
        video_memory[index] = c;
        video_memory[index + 1] = VGA_COLOR_WHITE_ON_BLACK;
        cursor_x++;
    }

    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= VGA_HEIGHT) {
        cursor_y = 0; 
    }
}

void kprint(const char* str) {
    while (*str != '\0') {
        kprint_char(*str++);
    }
}

void kprintln(const char* str) {
    kprint(str);
    kprint_char('\n');
}