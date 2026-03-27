# Description
The `zero/boot/info.h` header contains declarations, associated with boot loader.

The boot information is stored in `EBX` register as pointer after the boot loader jumps to protected mode and gives control to the kernel. The structures share the same memory layout as the given pointer.
# Symbols
## `boot_vid_info`
**Signature**:
```c
struct [[gnu::packed]] boot_vid_info {
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
## `boot_mem_entry_type`
**Signature**:
```c
enum boot_mem_entry_type : udword_t {
        BOOT_MEM_ENTRY_RAM = 1,
        BOOT_MEM_ENTRY_RESERVED,
        BOOT_MEM_ENTRY_ACPI,
        BOOT_MEM_ENTRY_NVS,
        BOOT_MEM_ENTRY_UNUSABLE,
        BOOT_MEM_ENTRY_DISABLED = 7,
};
```
**Description**: A memory entry type.
**Options**:
- `BOOT_MEM_ENTRY_RAM`: Free usable memory.
- `BOOT_MEM_ENTRY_RESERVED`: Reserved memory by hardware.
- `BOOT_MEM_ENTRY_ACPI`: ACPI tables. Usable after reading them.
- `BOOT_MEM_ENTRY_NVS`: ACPI Non-Volatile Sleep. Must be preserved across sleep/wake.
- `BOOT_MEM_ENTRY_UNUSABLE`: Unusable memory.
- `BOOT_MEM_ENTRY_DISABLED`: Disallowed memory.
## `boot_mem_entry`
**Signature**:
```c
struct [[gnu::packed]] boot_mem_entry {
        udword_t base_address_low;
        udword_t base_address_high;
        udword_t length_low;
        udword_t length_high;
        enum boot_mem_entry_type type;
};
```
**Description**: A memory map entry.
**Fields**:
- `base_address_low`, `base_address_high`: Starting 64-bit physical address.
- `length_low`, `length_high`: Size of the memory entry in bytes.
- `type`: Memory entry type.
## `boot_mem_map`
**Signature**:
```c
struct [[gnu::packed]] boot_mem_map {
        udword_t entries_count;
        struct boot_mem_entry *entries[];
};
```
**Description**: A memory map information.
**Fields**:
- `entries_count`: How much memory map entries. 
- `entries`: A flexible fixed array of memory map entries. The limit of the fixed array is `entries_count` field. 
## `boot_info`
**Signature**:
```c
struct [[gnu::packed]] boot_info {
        struct boot_vid_info *vid;
        struct boot_mem_map *mem_map;
};
```
**Description**: A boot loader information declaration.
**Fields**:
- `vid`: Video information.
- `mem_map`: Memory map information.