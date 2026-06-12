#include "heap.h"
#include "pmm.h"
#include "vga.h"

struct heap_segment_header {
    uint32_t size;
    bool is_free;
    struct heap_segment_header* next;
} __attribute__((packed));

static struct heap_segment_header* heap_start = 0;

void init_heap(void) {
    void* page = pmm_alloc_block();
    heap_start = (struct heap_segment_header*)page;
    
    heap_start->size = 4096 - sizeof(struct heap_segment_header);
    heap_start->is_free = true;
    heap_start->next = 0;

    kslog("Kernel Heap initialized successfully.");
}

void* kmalloc(uint32_t size) {
    struct heap_segment_header* current = heap_start;

    while (current != 0) {
        if (current->is_free && current->size >= size) {
            if (current->size > size + sizeof(struct heap_segment_header) + 4) {
                uint32_t next_addr = (uint32_t)current + sizeof(struct heap_segment_header) + size;
                struct heap_segment_header* next_seg = (struct heap_segment_header*)next_addr;
                
                next_seg->size = current->size - size - sizeof(struct heap_segment_header);
                next_seg->is_free = true;
                next_seg->next = current->next;

                current->size = size;
                current->next = next_seg;
            }

            current->is_free = false;
            return (void*)((uint32_t)current + sizeof(struct heap_segment_header));
        }
        current = current->next;
    }

    kerrln("kmalloc: OUT OF HEAP MEMORY!");
    return 0;
}

void kfree(void* ptr) {
    if (ptr == 0) return;

    struct heap_segment_header* header = (struct heap_segment_header*)((uint32_t)ptr - sizeof(struct heap_segment_header));
    header->is_free = true; // Просто объявляем кусок свободным!

    struct heap_segment_header* pointer_iterator = heap_start;
    while (pointer_iterator != 0 && pointer_iterator->next != 0) {
        if (pointer_iterator->is_free && pointer_iterator->next->is_free) {
            pointer_iterator->size += sizeof(struct heap_segment_header) + pointer_iterator->next->size;
            pointer_iterator->next = pointer_iterator->next->next;
        }
        pointer_iterator = pointer_iterator->next;
    }
}
