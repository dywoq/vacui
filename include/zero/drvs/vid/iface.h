// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_DRVS_VID_IFACE_H
#define _ZERO_DRVS_VID_IFACE_H

#include <zero/drvs/vid/color.h>
#include <zero/types.h>

struct drvs_vid_iface {
        void (*init) ();
        void (*draw_pixel_rgb) (word_t x, word_t y,
                                struct drvs_vid_color_rgb *rgb);
        usize_t (*width) ();
        usize_t (*height) ();
        void (*exit) ();
};

struct drvs_vid_iface *drvs_vid_get_impl ();
void drvs_vid_set_impl (struct drvs_vid_iface *i);

#endif
