/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * This defines the standard symbol definitions of Boot Abstraction Layer.
 * They're filled by an implementation of BAL and provided to the generic kernel
 * code.
 */

#ifndef _VQBAL_H
#define _VQBAL_H

#include <vqdef.h>

typedef enum _BAL_MM_REGION_TYPE : USHORT
{
    BAL_MM_REGION_FREE = 0,
    BAL_MM_REGION_UNAVAILABLE = 1,
} BAL_MM_REGION_TYPE;

typedef struct _BAL_MM_REGION
{
    ULONG address;
    ULONG length;
    BAL_MM_REGION_TYPE type;
} BAL_MM_REGION;

typedef struct _BAL_MM_INFO
{
    UINT regionsCount;
    BAL_MM_REGION *regions[];
} BAL_MM_INFO;

typedef struct _BAL_METADATA
{
    const char *title;
} BAL_METADATA;

typedef struct _BAL_INFO
{
    BAL_METADATA *metadata;
    BAL_MM_INFO *mmInfo;
} BAL_INFO;

#endif
