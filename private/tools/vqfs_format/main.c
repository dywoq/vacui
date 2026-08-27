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
            stderr, "usage: %s [DestinationFile] [ClustersCount]\n",
            ArgumentVector[0]
        );
        return -1;
    }

    //
    // Arguments
    //

    const char *DestinationFile = ArgumentVector[1];
    int         ClustersCount = atoi(ArgumentVector[2]);

    //
    // Allocate a cluster offsets array
    //

    size_t ClusterOffsetsSize =
        sizeof(VQFS_CLUSTER_OFFSET) * VQFS_CLUSTER_OFFSETS_MAX_LENGTH;
    VQFS_CLUSTER_OFFSET *ClusterOffsets = malloc(ClusterOffsetsSize);
    if (!ClusterOffsets)
    {
        fprintf(stderr, "Failed to allocate a cluster offsets array\n");
        return -1;
    }
    ClusterOffsets[VQFS_CLUSTER_OFFSETS_MAX_LENGTH - 1] =
        VQFS_MAKE_CLUSTER_OFFSET(0xFFFFFFF, VQFS_CLUSTER_END);

    //
    // Allocate a linear array of directory entries
    //

    size_t DirectoryEntriesSize =
        sizeof(VQFS_DIR_ENTRY) * VQFS_DIR_ENTRIES_MAX_LENGTH;
    VQFS_DIR_ENTRY *DirectoryEntries = malloc(DirectoryEntriesSize);
    if (!DirectoryEntries)
    {
        fprintf(stderr, "Failed to allocate a directory entries array\n");
        goto Failure;
    }
    DirectoryEntries[VQFS_DIR_ENTRIES_MAX_LENGTH - 1] =
        (VQFS_DIR_ENTRY){.Name = "RESERVED", .Extension = "READ", .Flags = 0x7};

    //
    // Allocate an array of clusters
    //

    size_t ClustersSize = VQFS_CLUSTER_SIZE * ClustersCount;
    void  *Clusters = malloc(ClustersSize);
    if (!Clusters)
    {
        fprintf(stderr, "Failed to allocate a clusters array\n");
        goto Failure;
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

    size_t Count = fwrite(
        ClusterOffsets, sizeof(uint8_t), ClusterOffsetsSize,
        DestinationFileStream
    );
    if (Count < ClusterOffsetsSize)
    {
        printf("Failed to write the cluster offsets to the file\n");
        goto Failure;
    }

    //    fseek(DestinationFileStream, ClusterOffsetsSize, SEEK_SET);

    Count = fwrite(
        DirectoryEntries, sizeof(uint8_t), DirectoryEntriesSize,
        DestinationFileStream
    );
    if (Count < DirectoryEntriesSize)
    {
        printf("Failed to write the directory entries to the file\n");
        goto Failure;
    }

    // fseek(DestinationFileStream, DirectoryEntriesSize, SEEK_SET);

    Count =
        fwrite(Clusters, sizeof(uint8_t), ClustersSize, DestinationFileStream);
    if (Count < ClustersSize)
    {
        printf("Failed to write the clusters to the file\n");
        goto Failure;
    }

    goto Success;

Success:

    if (ClusterOffsets)
    {
        free(ClusterOffsets);
    }

    if (DirectoryEntries)
    {
        free(DirectoryEntries);
    }

    if (Clusters)
    {
        free(Clusters);
    }

    if (DestinationFileStream)
    {
        fclose(DestinationFileStream);
    }

    return 0;

Failure:

    if (ClusterOffsets)
    {
        free(ClusterOffsets);
    }

    if (DirectoryEntries)
    {
        free(DirectoryEntries);
    }

    if (Clusters)
    {
        free(Clusters);
    }

    if (DestinationFileStream)
    {
        fclose(DestinationFileStream);
    }

    return -1;
}
