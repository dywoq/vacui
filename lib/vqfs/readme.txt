            VQ Filesystem

The VQ filesystem is a custom filesystem that is
used in Vacui.

            Features

- Filename and extension character limit:
You can use only 8 characters for filename and 3 characters
for extension.

- Each file has a fixed-array of offsets
that refer to data blocks.
If file has the offset 1056768, you need to increment by 1056768 bytes
to access its first data block:

    Data block = Disk + 1056768 bytes

If it's a directory, then the array will contain indexes of its files
and sub-directories present in entries_offsets.

            Memory layout

| ----------------------------------------- |
|            Header (4096 bytes)            |
| ----------------------------------------- |
| ----------------------------------------- |
|       Entry offsets table (4096 bytes)    |
| ----------------------------------------- |
| ----------------------------------------- |
|    Entries[N ... 1024] (1024 bytes each)  |
| ----------------------------------------- |
| ----------------------------------------- |
|       Data[N ... 1024] (4096 bytes each)  |
| ----------------------------------------- |
