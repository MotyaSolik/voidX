#include <stdint.h>
#include "drivers/vga.h"

struct registers {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

const char *exception_messages[] = {
    "Division By Zero", "Debug", "Non Maskable Interrupt", "Breakpoint",
    "Into Detected Overflow", "Out of Bounds", "Invalid Opcode", "No Coprocessor",
    "Double Fault", "Coprocessor Segment Overrun", "Bad TSS", "Segment Not Present",
    "Stack Fault", "General Protection Fault", "Page Fault", "Unknown Interrupt",
    "Coprocessor Fault", "Alignment Check", "Machine Check", "SIMD Floating-Point",
    "Virtualization Exception", "Control Protection Exception", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved"
};

void exception_handler_c(struct registers regs) {
    kclear_screen();

    kerrln("!!!!!!!!!!!!!!!!!!");
    kerrln("!! KERNEL PANIC !!");
    kerrln("!!!!!!!!!!!!!!!!!!\n");

    kprintln(exception_messages[regs.int_no]);

    kprintln("\nThe system has been halted to prevent damage.\n");
    // Выведем критические регистры (для отладки)
    kprint("REGISTERS:\n");
    kprint("EIP: "); kprint_hex(regs.eip);      kprint("  CS:  "); kprint_hex(regs.cs);  kprint("\n");
    kprint("EAX: "); kprint_hex(regs.eax);      kprint("  EBX: "); kprint_hex(regs.ebx); kprint("\n");
    kprint("ECX: "); kprint_hex(regs.ecx);      kprint("  EDX: "); kprint_hex(regs.edx); kprint("\n");
    kprint("ERR: "); kprint_hex(regs.err_code); kprint("\n\n");

    // Замораживаем процессор навсегда
    while(1) {
        __asm__ volatile("cli; hlt"); // Отключаем прерывания и спим
    }
}
