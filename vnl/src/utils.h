#pragma once
#include <stdint.h>
#include <stddef.h>
int strcmp(const char *s1, const char *s2);
void* memset(void* bufptr, int value, size_t size);
void* memcpy(void* dstptr, const void* srcptr, size_t size);
int memcmp(const void* aptr, const void* bptr, size_t size);
char* strchr(const char* str, int character);
uint32_t get_fattime(void);
void check_crash_trigger_file(void);
