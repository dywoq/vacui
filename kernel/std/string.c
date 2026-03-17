// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <std/types.h>

word_t string_len(const char *str) {
    word_t len = 0;
    for (const char *p = str; *p != '\0'; ++p) {
        len++;
    }
    return len;
}
