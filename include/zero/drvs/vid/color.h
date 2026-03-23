// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_DRVS_VID_COLOR_H
#define _ZERO_DRVS_VID_COLOR_H

#include <zero/types.h>

struct drvs_vid_color_rgb {
        ubyte_t red;
        ubyte_t green;
        ubyte_t blue;
};
#define DRVS_VID_COLOR_RGB_DEF(r, g, b)          \
        (struct drvs_vid_color_rgb)              \
        {                                        \
                .red = r, .green = g, .blue = b, \
        }

#endif
