#pragma once
#include <stdint.h>

// хахахаха посудомойка смехуятина

#define PMM_BLOCK_SIZE 4096

void pmm_init(uint32_t mem_size);
void* pmm_alloc_block(void);
void pmm_free_block(void* p);
