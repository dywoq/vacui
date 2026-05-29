// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//
//      This module contains the bootloader hub functionality.

#ifndef _HUB_H
#define _HUB_H

#include <vqtypes.h>

#define HUBAPI [[gnu::section(".bub")]]

// Description:
//
//      Prints a string into the screen, using teletype output
//      macro wrapper from bios.h
//
// Parameters:
//
//      - str: A string to print. Must be null-terminated.
HUBAPI void hprint(const char *str);

// Description:
//
//      Causes the bootloader to panic, printing a panic message into the screen
//      (hprint).
//
// Parameters:
//
//      - str: The panic message. Must be null-terminated.
HUBAPI [[noreturn]] void hpanic(const char *msg);

#endif
