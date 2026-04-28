/*
 * Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	entry/main.c
 *
 * Module description:
 * 	A kernel entry file
 *
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */

__asm(".code16gcc");

#include <biosvid.h>
#include <vqprint.h>

void 
Entry(
	void) 
{
	Print("Hi!\n");
	while (true);
}
