//#include <vga.h">
#include <keyboard.h>
#include <idt.h>
#include <gdt.h>
#include <timer.h>
#include <pmm.h>
#include <paging.h>
#include <heap.h>
#include <ata.h>
#include "utils.h"
#include "fs/ff.h"
#include <timer.h>

struct registers;
extern void exception_handler_c(struct registers regs); 

void cmd_ls() {
    FATFS fs;
    DIR dir;
    FILINFO fno;
    FRESULT res;

    kprint("\n--- DISK DIRECTORY ROOT ---\n");
    
    res = f_mount(&fs, "", 1);
    if (res != FR_OK) {
        kprint("f_mount failed with code: "); kprint_hex(res); kprint("\n");
        return;
    }

    res = f_opendir(&dir, "/");
    if (res != FR_OK) {
        // ЕСЛИ ЗДЕСЬ ВЫВЕДЕТСЯ КОД 13 (FR_NO_FILESYSTEM) — значит, формат диска не подошел!
        kprint("f_opendir failed with code: "); kprint_hex(res); kprint("\n");
    } else {
        int count = 0;
        while (f_readdir(&dir, &fno) == FR_OK && fno.fname[0] != 0) {
            count++;
            if (fno.fattrib & AM_DIR) {
                kprint("  [DIR] ");
            } else {
                kprint("  [FIL] ");
            }
            kprint(fno.fname);
            kprint("\n");
        }
        if (count == 0) {
            kprint("  (Directory is empty)\n");
        }
        f_closedir(&dir);
    }
    kprint("---------------------------\n\n");
}
void cmd_cat() {
    FATFS fs;
    FIL file;
    char buf[64];
    UINT br;

    if (f_mount(&fs, "", 1) == FR_OK) {
        if (f_open(&file, "README.TXT", FA_READ) == FR_OK) {
            kprint("\n");
            while (f_read(&file, buf, sizeof(buf) - 1, &br) == FR_OK && br > 0) {
                buf[br] = '\0';
                kprint(buf);
            }
            kprint("\n\n");
            f_close(&file);
        } else {
            kerrln("File README.TXT not found!");
        }
    }
}


void kernel_main(void) {
    vga_init();
    kprintln("VNL Kernel v0.1.0");
    kprintln("Initializating VNL...");
    init_gdt();
    init_idt(); 
    init_timer();
    pmm_init(128 * 1024 * 1024);
    init_paging();
    init_heap();
    vga_set_color(0x0B);
    kprintln("VNL Ready!");
    vga_set_color(0x0F);
    char cmd_buffer[256];
    kprintln("vxsh v0.1.0");
    vga_set_color(0x07);
    kprintln("Type 'help' for list of commands");
    vga_set_color(0x0F);
    while(1) {
        kprint("voidx> ");
        input_line(cmd_buffer);

        if (strcmp(cmd_buffer, "help") == 0) {
            kprint("Available commands:\n");
            kprint("  help  - Show this list\n");
            kprint("  clear - Clear the screen\n");
            kprint("  hello - Say hello to the creator\n");
        } else if (strcmp(cmd_buffer, "clear") == 0) {
            kclear_screen();
        } else if (strcmp(cmd_buffer, "hello") == 0) {
            kprintln("Hello, VoidDuck! VoidX is working!");
        } else if (strcmp(cmd_buffer, "ls") == 0) { cmd_ls(); }
        else if (strcmp(cmd_buffer, "cat readme") == 0) {cmd_cat();}

    
        else if (cmd_buffer[0] != '\0') {
            kerr("unknown: ");
            kerrln(cmd_buffer);
        } 
    }
    
}

