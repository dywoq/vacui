// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/drvs/vid/iface.h>
#include <zero/drvs/vid/reg.h>

static usize_t registered_top_ = 0;
static struct drvs_vid_iface *registered_[DRVS_VID_REG_MAX_SIZE] = {};
static bool init_ = false;
static bool exit_ = false;

void drvs_vid_reg_iface (struct drvs_vid_iface *i)
{
        if (registered_top_ >= DRVS_VID_REG_MAX_SIZE)
                return;
        registered_[registered_top_] = i;
        registered_top_++;
}

void drvs_vid_init (void)
{
        if (registered_top_ == 0)
                return;
        for (usize_t i = 0; i < registered_top_; i++)
                registered_[i]->init ();
        init_ = true;
}

void drvs_vid_exit (void)
{
        if (registered_top_ == 0)
                return;
        for (usize_t i = 0; i < registered_top_; i++)
                registered_[i]->init ();
        exit_ = true;
}

bool drvs_vid_initialized (void)
{
        return init_;
}

bool drvs_vid_exited (void)
{
        return exit_;
}

void drvs_vid_allreg (void)
{
        
}
