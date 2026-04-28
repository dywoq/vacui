/*
 * Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	hub/panic.c
 *
 * Module description:
 * 	An implementation of vqpanic.h header
 *
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */

__asm(".code16gcc");

#include <vqdef.h>
#include <vqtypes.h>
#include <vqprint.h>
#include <biosvid.h>

_Noreturn
VOID
Panic(
	C_STR string)
{
	/* Switch to text mode (to make sure game is not stuck in video mode) */
	BiosSetVidMode(BIOS_VID_X80_25);

	C_STR title = "VacuiMini panic";
	BYTE titleLength = 15;
	/* We need alignment to center title */
	BYTE titleAlignment = 11;

	for (INT i = 0; i <= 80; i++) {
		if (i == (80 / 2) - titleAlignment) {
			Print(title);
			i += titleLength;
			continue;
		}
		Put('-');
	}

	/* Print message */
	Put('\n');
	Print(string ? string : "<null message>");
	Put('\n');

	/* Print line */
	Put('\n');
	Put('\r');
	for (INT i = 0; i < 80; i++) {
		Put('-');
	}

	/*
	 * TODO: When the kernel serivces appear, they must be properly cleaned
	 * before exiting. Currently, we just halt.
	 * - dywoq
	 */
	Print("System services exited.\n");
	Print("You can safely shutdown or reboot your hardware.\n");

	/* Halt */
	__asm volatile("cli");
	while (true)
		__asm volatile("hlt\n");
}

