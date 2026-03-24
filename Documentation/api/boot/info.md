# Description
The `zero/boot/info.h` header contains declarations, associated with boot loader.

The boot information is stored in `EBX` register as pointer after the boot loader jumps to protected mode and gives control to the kernel. The structures share the same memory layout as the given pointer.
# Symbols
## `boot_vid_info`
**Signature**:
```c
struct boot_vid_info {
        uword_t mode;
        uword_t width;
        uword_t height;
};
```
**Description**: A boot video information, which was provided by boot loader.
**Fields**:
- `mode`: The VGA mode.
- `width`: A maximum resolution width.
- `height`: A maximum resolution height.
## `boot_info`
**Signature**:
```c
struct boot_info {
        struct boot_vid_info *vid;
};
```
**Description**: A boot loader information declaration.
**Fields**:
- `vid`: Video information.