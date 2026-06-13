#pragma once
#include <stdint.h>
#include "keyboard.h"
#include "ports.h"

struct idt_entry {
    uint16_t offset_lowerbits;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type_attr;
    uint16_t offset_higherbits;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern struct idt_entry idt[256]; 
extern struct idt_ptr idtp;


void init_idt(void);
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

