//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      This header defines types and declares functionality for
//      managing the VQFS filesystem images
//

#ifndef VQFSLIB_H
#define VQFSLIB_H

#include "vqfs.h"

typedef enum vqfs_lib_status : vqfs_ushort_t {
    vqfs_lib_status_ok = 0,
    vqfs_lib_status_invalid_parameter,
} vqfs_lib_status_t;

//
// Routine Description
//
//      Initializes the provided header instance.
//
// Parameters
//
//      header_dest         OUT
//
//          A required pointer to the header instance full of zeros.
//
//      boot_sector         OUT
//
//          A required pointer to the boot sector buffer. It must have a
//          0xAA55 signature at the end.
//
//      boot_sector_size    IN
//
//          The boot_sector size that must equal to 512. 
//
// Returns
//
//      vqfs_lib_status_ok
//
//          The operation was successful.
//
//      vqfs_lib_status_invalid_parameter
//
//          The header_dest or boot_sector parameter is null, or 
//          boot_sector_size is not 512.
//
vqfs_lib_status_t vqfs_lib_init_header(
    vqfs_header_t *header_dest,
    vqfs_ubyte_t  *boot_sector,
    vqfs_ulong_t   boot_sector_size
);

#endif
