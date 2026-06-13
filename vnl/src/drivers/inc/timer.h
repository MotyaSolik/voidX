#pragma once
#include "ports.h"

extern volatile int need_check_crash;

void init_timer(void);
void timer_handler_c(void);
void sleep(uint32_t ms);
void sleep_s(uint32_t sec);