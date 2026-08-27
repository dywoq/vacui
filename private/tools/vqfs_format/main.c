//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      The vqfs_format main function
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vqfs.h>

int
main(
    int   ArgumentCount,
    char *ArgumentVector[]
)
{
    if (ArgumentCount < 3)
    {
        fprintf(
            stderr, "usage: %s [DestinationFile] [DirectoryEntriesCount]\n",
            ArgumentVector[0]
        );
        return -1;
    }

    //
    // Arguments
    //

    const char *DestinationFile = ArgumentVector[1];
    int         DirectoryEntriesCount = atoi(ArgumentVector[2]);
    if (DirectoryEntriesCount > VQFS_DIR_ENTRIES_MAX_LENGTH)
    {
        fprintf(
            stderr, "[DirectoryEntriesCount] cannot be higher than %d\n",
            VQFS_DIR_ENTRIES_MAX_LENGTH
        );
        return -1;
    }

    //
    // Open a file and write the allocated memory to it.
    //

    FILE *DestinationFileStream = fopen(DestinationFile, "rb+");
    if (!DestinationFileStream)
    {
        fprintf(stderr, "Failed to open the destination file\n");
        goto Failure;
    }

    size_t DirectoryEntriesSize =
        sizeof(VQFS_DIR_ENTRY) * DirectoryEntriesCount;
    VQFS_DIR_ENTRY *DirectoryEntries = malloc(DirectoryEntriesSize);
    if (!DirectoryEntries)
    {
        fprintf(stderr, "Failed to allocate directory entries");
        goto Failure;
    }

    fwrite(
        DirectoryEntries, sizeof(uint8_t), DirectoryEntriesSize,
        DestinationFileStream
    );

    goto Success;

Success:
    if (DirectoryEntries)
    {
        free(DirectoryEntries);
    }
    if (DestinationFileStream)
    {
        fclose(DestinationFileStream);
    }
    return 0;

Failure:
    if (DirectoryEntries)
    {
        free(DirectoryEntries);
    }
    if (DestinationFileStream)
    {
        fclose(DestinationFileStream);
    }
    return -1;
}
