// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/drvs/vid/iface.h>

static void dummy_init_ ()
{
}
static void dummy_exit_ ()
{
}
static void dummy_draw_pixel_rgb_ (word_t x, word_t y,
                                   struct drvs_vid_color_rgb *rgb)
{
}
static struct drvs_vid_iface dummy_iface_ = (struct drvs_vid_iface){
    .init = dummy_init_,
    .draw_pixel_rgb = dummy_draw_pixel_rgb_,
    .exit = dummy_exit_,
};
static struct drvs_vid_iface *current_impl_ = &dummy_iface_;

struct drvs_vid_iface *drvs_vid_get_impl ()
{
        return current_impl_;
}

void drvs_vid_set_impl (struct drvs_vid_iface *i)
{
        current_impl_ = i;
}
