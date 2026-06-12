#include "paging.h"
#include "pmm.h"
#include "vga.h"

__attribute__((aligned(4096))) static uint32_t page_directory[1024];

__attribute__((aligned(4096))) static uint32_t first_page_table[1024];

void init_paging(void) {
    for (int i = 0; i < 1024; i++) {
        page_directory[i] = 0x00000002;
    }

    for (int i = 0; i < 1024; i++) {
        first_page_table[i] = (i * 4096) | 0x03;
    }

    page_directory[0] = ((uint32_t)first_page_table) | 0x03;

    
    __asm__ volatile("mov %0, %%cr3" : : "r"(page_directory));
    uint32_t cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; // Включаем бит страничной адресации
    __asm__ volatile("mov %0, %%cr0" : : "r"(cr0));

    kslog("Virtual memory (Paging) is enabled and active!");
}
