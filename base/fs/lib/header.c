#include "vqfs.h"
#include "vqfslib.h"

vqfs_lib_status_t vqfs_lib_init_header(
    vqfs_header_t *header_dest,
    vqfs_ubyte_t  *boot_sector,
    vqfs_ulong_t   boot_sector_size
) {
    if (!header_dest || !boot_sector) {
        return vqfs_lib_status_invalid_parameter;
    }
    
    return vqfs_lib_status_ok;
}
