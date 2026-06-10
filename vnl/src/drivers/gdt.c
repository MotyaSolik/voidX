#include "gdt.h"

struct gdt_entry gdt[3];
struct gdt_ptr gdtp;

// Функция для заполнения дескрипторов
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access      = access;
}

void init_gdt() {
    gdtp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdtp.base  = (uint32_t)&gdt;

    // 1. Нулевой дескриптор (Null segment)
    gdt_set_gate(0, 0, 0, 0, 0);
    // 2. Сегмент кода ядра (Kernel Code) -> станет селектором 0x08
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // 3. Сегмент данных ядра (Kernel Data) -> станет селектором 0x10
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Загружаем GDT в регистр GDTR
    __asm__ volatile("lgdt %0" : : "m"(gdtp));

    // Перезагружаем сегментные регистры процессора на нашу новую GDT
    __asm__ volatile(
        "ljmp $0x08, $.1\n\t"
        ".1:\n\t"
        "mov $0x10, %ax\n\t"
        "mov %ax, %ds\n\t"
        "mov %ax, %es\n\t"
        "mov %ax, %fs\n\t"
        "mov %ax, %gs\n\t"
        "mov %ax, %ss\n\t"
    );
}
