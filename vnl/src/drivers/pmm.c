#include "pmm.h"
#include "vga.h"

#define MAX_MEM_SIZE (128 * 1024 * 1024)

#define TOTAL_BLOCKS (MAX_MEM_SIZE / PMM_BLOCK_SIZE)

#define BITMAP_SIZE  (TOTAL_BLOCKS / 8)

static uint8_t pmm_bitmap[BITMAP_SIZE];
static uint32_t memory_size_bytes = 0;

#define SET_BIT(block)    (pmm_bitmap[(block) / 8] |=  (1 << ((block) % 8)))
#define CLEAR_BIT(block)  (pmm_bitmap[(block) / 8] &= ~(1 << ((block) % 8)))
#define TEST_BIT(block)   (pmm_bitmap[(block) / 8] &   (1 << ((block) % 8)))

void pmm_init(uint32_t mem_size) {
    memory_size_bytes = mem_size;
    
    
    for (int i = 0; i < BITMAP_SIZE; i++) {
        pmm_bitmap[i] = 0xFF;
    }

    
    uint32_t blocks = memory_size_bytes / PMM_BLOCK_SIZE;

    uint32_t start_block = (1024 * 1024) / PMM_BLOCK_SIZE;
    
    for (uint32_t i = start_block; i < blocks; i++) {
        CLEAR_BIT(i);
    }
    
    kslog("PMM initialized. Memory mapped safely.");
}

void* pmm_alloc_block(void) {
    uint32_t total_blocks = memory_size_bytes / PMM_BLOCK_SIZE;

    for (uint32_t i = 0; i < total_blocks; i++) {
        if (!TEST_BIT(i)) {
            SET_BIT(i);
            uint32_t addr = i * PMM_BLOCK_SIZE;
            return (void*)addr;
        }
    }

    kerrln("PMM: OUT OF MEMORY!");
    return 0; 
}

void pmm_free_block(void* p) {
    uint32_t addr = (uint32_t)p;
    uint32_t block = addr / PMM_BLOCK_SIZE;

    CLEAR_BIT(block);
}
