// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_DRVS_VID_IFACE_H
#define _ZERO_DRVS_VID_IFACE_H

#include <zero/types.h>

struct drvs_vid_iface {
        // Metadata
        const char *name;
        usize_t id;
        // Resolution
        usize_t width;
        usize_t height;
        // Initialization/exiting
        void (*init) (void);
        void (*exit) (void);
        // Manipulation
        void (*put_pixel) (usize_t x, usize_t y, usize_t color);
};

#define DRVS_VID_EXTERN(decl_name) \
        extern struct drvs_vid_iface drvs_vid_##decl_name

#define DRVS_VID_MAKE(decl_name, metadata_name, metadata_id, ...)            \
        struct drvs_vid_iface drvs_vid_##decl_name = (struct drvs_vid_iface) \
        {                                                                    \
                .name = metadata_name,                                       \
                .id = metadata_id __VA_OPT__ (, ) __VA_ARGS__                \
        }

#endif
