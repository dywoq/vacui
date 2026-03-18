// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _COMPILER_LD_H
#define _COMPILER_LD_H

extern char compiler_ld_start;
extern char compiler_ld_end;
static char compiler_ld_size = 0;

static void compiler_ld_size_init() {
    compiler_ld_size = compiler_ld_end - compiler_ld_start;
}

#endif
