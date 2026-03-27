// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_DRVS_PORTS_H
#define _ZERO_DRVS_PORTS_H

#include <zero/types.h>

void drvs_port_outb (ubyte_t value, uword_t port);
ubyte_t drvs_port_inb (uword_t port);

#endif
