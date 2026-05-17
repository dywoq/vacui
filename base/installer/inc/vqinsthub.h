/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * This header contains the functions that manage the hub (core)
 * of the Vacui VQ installer.
 */

#ifndef _VQINSTHUB_H
#define _VQINSTHUB_H

/*
 * Causes the installer to panic, printing the given message
 * and additional information. After that, CPU halts.
 *
 * It's used only when the installer encounters fatal errors.
 *
 * If the given message is null, it prints <unknown> string.
 */
[[noreturn]]
void
HubPanic(const char *message);

#endif
