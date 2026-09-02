//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      The main function of the vqfs_fmt command utility
//

#include "vqfs.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <threads.h>

static void
err(const char *fmt,
    ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
}

static int print_usage() {
    err("usage: vqfs_fmt [dest_file] [boot_sector] [blocks_count]\n");
    return -1;
}

static bool init_header(
    FILE       *dest_image_stream,
    const char *boot_sector
) {
    //
    // Allocate a header instance
    //

    vqfs_header_t *header = malloc(sizeof(vqfs_header_t));
    if (!header) {
        goto failure;
    }

    //
    // Open and read the boot sector file.
    //

    FILE *boot_sector_stream = fopen(boot_sector, "r");
    if (!boot_sector_stream) {
        err("failed to open the boot sector file: %s\n", boot_sector);
        goto failure;
    }

    //
    // Validate the size before reading
    //

    struct stat boot_sector_stat;
    stat(boot_sector, &boot_sector_stat);
    if (boot_sector_stat.st_size != 512) {
        err("the boot sector size must be 512\n");
        goto failure;
    }

    //
    // Allocate a buffer and read the boot sector file.
    //

    uint8_t *boot_sector_content = malloc(512);
    if (!boot_sector_content) {
        err("failed to allocate a buffer for boot sector content\n");
        goto failure;
    }
    fread(boot_sector_content, sizeof(uint8_t), 512, boot_sector_stream);

    //
    // Initialize the header
    //

    memcpy(&header->boot_sector, boot_sector_content, 512);
    header->major_version = VQFS_MAJOR_VERSION;
    header->minor_version = VQFS_MINOR_VERSION;
    header->blocks_table_offset = sizeof(vqfs_header_t);
    header->root_dir_offset =
        sizeof(struct vqfs_header) + sizeof(struct vqfs_blocks_table);
    header->blocks_array_offset = sizeof(struct vqfs_header) +
                                  sizeof(struct vqfs_blocks_table) +
                                  sizeof(struct vqfs_root_dir);

    //
    // Write it to the destination file
    //

    fwrite(
        header, sizeof(uint8_t), sizeof(struct vqfs_header), dest_image_stream
    );

    goto success;

failure:
    if (header) {
        free(header);
    }
    if (boot_sector_stream) {
        fclose(boot_sector_stream);
    }
    if (boot_sector_content) {
        free(boot_sector_content);
    }
    return false;

success:
    if (header) {
        free(header);
    }
    if (boot_sector_stream) {
        fclose(boot_sector_stream);
    }
    if (boot_sector_content) {
        free(boot_sector_content);
    }
    return true;
}

static bool reserve_space(
    FILE *dest_image_stream,
    int   blocks_count
) {
    //
    // Routine checks
    //

    if (blocks_count < 0) {
        err("blocks count cannot be lower than zero\n");
        return false;
    }
    if (blocks_count == 0) {
        err("blocks count cannot be zero\n");
        return false;
    }

    //
    // We reserve space for the blocks table, root directory and
    // blocks array.
    //

    size_t   total_size = sizeof(struct vqfs_blocks_table) +
                          sizeof(struct vqfs_root_dir) +
                          (blocks_count * VQFS_BLOCK_SIZE);
    uint8_t *buffer = malloc(total_size);
    if (!buffer) {
        err("failed to allocate buffer\n");
        goto failure;
    }
    fwrite(buffer, sizeof(uint8_t), total_size, dest_image_stream);
    goto success;

failure:
    if (buffer) {
        free(buffer);
    }
    return false;

success:
    if (buffer) {
        free(buffer);
    }
    return true;
}

int main(
    int   argc,
    char *argv[]
) {
    //
    // Cause a compilation error if the current target is not
    // valid.
    //
#if !_TOOLCHAIN_LINUX && !_TOOLCHAIN_X86_64
    static_assert(false);
#endif

    //
    // Validate the argument count.
    // Retrieve the arguments.
    //

    if (argc < 4) {
        return print_usage();
    }
    const char *dest_image = argv[1];
    const char *boot_sector = argv[2];
    int         blocks_count = atoi(argv[3]);

    //
    // Open the destination file.
    //

    FILE *stream = fopen(dest_image, "rb+");
    if (!stream) {
        err("failed to open the destination image: %s\n", dest_image);
        goto failure;
    }

    //
    // Initialization routine
    //

    if (!init_header(stream, boot_sector)) {
        err("failed to initialize a header\n");
        goto failure;
    }

    if (!reserve_space(stream, blocks_count)) {
        err("failed to reserve space for the blocks table, root directory and "
            "blocks array\n");
        goto failure;
    }

    //
    // Print the final message
    //

    printf("Successfully formatted the destination image: %s\n", dest_image);

    goto success;

failure:
    if (stream) {
        fclose(stream);
    }
    return -1;

success:
    if (stream) {
        fclose(stream);
    }
    return 0;
}
