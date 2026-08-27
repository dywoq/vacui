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

typedef enum _VQFS_CLUSTER_STATE : unsigned char
{
    VQFS_CLUSTER_FREE = 0,
    VQFS_CLUSTER_BUSY = 1,
    VQFS_CLUSTER_DELETED = 2,
} VQFS_CLUSTER_STATE;

//
// Routine Description
//
//      A cluster offset in the drive, which consists of an offset value
//      itself and its state (VQFS_CLUSTER_STATE). It must constructed
//      using the VQFS_MAKE_CLUSTER_OFFSET helper macro. To get the
//      packed information, use the following macros:
//
//           VQFS_CLUSTER_OFFSET_GET_OFFSET, VQFS_CLUSTER_OFFSET_GET_STATE
//
//      Below, you can see the cluster offset bit form:
//
//              0...28 bits: An offset value
//
//              29...31 bits: A state
//
//
typedef unsigned int VQFS_CLUSTER_OFFSET;
#define VQFS_MAKE_CLUSTER_OFFSET(Offset, State)                                \
    (VQFS_CLUSTER_OFFSET)(Offset | State << 29)
#define VQFS_CLUSTER_OFFSET_GET_OFFSET(Offset)                                 \
    (unsigned int)(Offset & 0x13FFFFFF)
#define VQFS_CLUSTER_OFFSET_GET_STATE(Offset)                                  \
    (VQFS_CLUSTER_STATE)((Offset & 0xE0000000) >> 29)

//
// Routine Description
//
//      The filesystem clusters table. It consists of cluster offsets.
//      The max length is defined by the header information.
//
typedef struct _VQFS_CLUSTERS_TABLE
{
    VQFS_CLUSTER_OFFSET *Offsets;
} VQFS_CLUSTERS_TABLE;

typedef unsigned int VQFS_DIR_ENTRY_FLAG;
#define VQFS_DIR_ENTRY_FILE      (VQFS_DIR_ENTRY_FLAG)(1 << 0)
#define VQFS_DIR_ENTRY_DIRECTORY (VQFS_DIR_ENTRY_FLAG)(1 << 1)

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

    //
    // If a directory entry has the VQFS_DIR_ENTRY_DIRECTORY flag,
    // then ClusterIndexes will point to clusters that hold a
    // linear array of sub-directory entries.
    //
    VQFS_CLUSTER_OFFSET ClusterIndexes[4];
} VQFS_DIR_ENTRY;

#define VQFS_DIR_ENTRIES_MAX_LENGTH 2047
#define VQFS_CLUSTER_SIZE           8192
#define VQFS_CLUSTERS_MAX_LENGTH    65536

#endif
