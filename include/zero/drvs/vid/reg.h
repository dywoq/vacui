// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_DRVS_VID_REG_H
#define _ZERO_DRVS_VID_REG_H

#include <zero/drvs/vid/iface.h>
#include <zero/types.h>

static constexpr usize_t DRVS_VID_REG_MAX_SIZE = 64;

void drvs_vid_reg_iface (struct drvs_vid_iface *i);
void drvs_vid_init (void);
void drvs_vid_exit (void);
bool drvs_vid_initialized (void);
bool drvs_vid_exited (void);
void drvs_vid_allreg (void);

#endif
