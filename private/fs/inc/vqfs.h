//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      The private VQFS filesystem type, macro and constant
//      definitions
//

#ifndef VQFS_H
#define VQFS_H

typedef unsigned int VQFS_DIR_ENTRY_FLAG;
#define VQFS_DIR_ENTRY_FILE     (VQFS_DIR_ENTRY_FLAG)(1 << 0)
#define VQFS_DIR_ENTRY_READONLY (VQFS_DIR_ENTRY_FLAG)(1 << 1)

//
// Routine Description
//
//      A filesystem directory entry.
//
typedef struct _VQFS_DIR_ENTRY
{
    char                Name[8];
    char                Extension[4];
    VQFS_DIR_ENTRY_FLAG Flags;
    char                Content[65520];
} VQFS_DIR_ENTRY;

#endif
