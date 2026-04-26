/* Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	hub/panic.c
 *
 * Module description:
 * 	An implementation of vacpanic.h header
 *
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */

__asm(".code16gcc");

#include <vacdef.h>
#include <vactypes.h>
#include <biosvid.h>

VAC_VOID
Vac_Panic(
	IN OPT const VAC_CHAR *str
	)
{
	BiosTeletypePrint("\n\r! PANIC !");
	BiosTeletypePrint("\n\r");
	BiosTeletypePrint(str ? str : "<unknown>");
	BiosTeletypePrint("\n\r! PANIC END !");
	BiosTeletypePrint("\n\r\n\rExiting services...");
	BiosTeletypePrint("\n\rIt's safe to reboot/shutdown PC.");
	while (true)
		__asm volatile("hlt\n");
}
