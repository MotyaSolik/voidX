#pragma once
#include <stdint.h>
#include <stdbool.h>

void init_heap(void);
void* kmalloc(uint32_t size);
void kfree(void* ptr);
