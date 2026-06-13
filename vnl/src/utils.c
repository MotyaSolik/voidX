#include "utils.h"
#include "fs/ff.h"
#include <timer.h>

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) { s1++; s2++; }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

void* memset(void* bufptr, int value, size_t size) {
    unsigned char* buf = (unsigned char*) bufptr;
    for (size_t i = 0; i < size; i++) buf[i] = (unsigned char) value;
    return bufptr;
}

void* memcpy(void* dstptr, const void* srcptr, size_t size) {
    unsigned char* dst = (unsigned char*) dstptr;
    const unsigned char* src = (const unsigned char*) srcptr;
    for (size_t i = 0; i < size; i++) dst[i] = src[i];
    return dstptr;
}

int memcmp(const void* aptr, const void* bptr, size_t size) {
    const unsigned char* a = (const unsigned char*) aptr;
    const unsigned char* b = (const unsigned char*) bptr;
    for (size_t i = 0; i < size; i++) {
        if (a[i] < b[i]) return -1;
        else if (a[i] > b[i]) return 1;
    }
    return 0;
}

char* strchr(const char* str, int character) {
    while (*str != '\0') {
        if (*str == character) return (char*)str;
        str++;
    }
    return 0;
}

uint32_t get_fattime(void) {
    return ((uint32_t)(2026 - 1980) << 25) | ((uint32_t)6 << 21) | ((uint32_t)13 << 16);
}

void check_crash_trigger_file(void) {
    FATFS fs; FIL file; char buffer = 0; UINT bytes_read;
    if (f_mount(&fs, "", 1) == FR_OK) {
        if (f_open(&file, "DEV/CRASH.TXT", FA_READ) == FR_OK) {
            if (f_read(&file, &buffer, 1, &bytes_read) == FR_OK && bytes_read > 0) {
                if (buffer == '1') {
                    // Твой вызов паники: например, деление на ноль
                    volatile int a = 5; volatile int b = 0; volatile int c = a / b;
                }
            }
            f_close(&file);
        }
    }
}
