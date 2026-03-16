# Description

The `bios/vid.h` header contains functionality, that wraps around BIOS video services.

# Symbols

## `bios_vid_mode`

**Signature:**

```c
enum bios_vid_mode : word_t {
    BIOS_VID_TEXT_X80_25 = 0x03,
};
```

**Description:** An enumeration of video modes. 
**Values**:
- `BIOS_VID_TEXT_X80_25`: The 80x25 video mode, allows only ASCII characters (range 0-127).

## `bios_vid_tt_output`

**Signature:**

```c
void bios_vid_tt_output(char ch);
```

**Description:** A wrapper around BIOS interruption 0x10.
**BIOS interruption interface**: 
- `al`: `ch`
- `ah`: `0x0E`
- `bh`: 0 
**Parameters:**
- `ch`: A character to print.  

## `bios_vid_mode_set`
**Signature:**
```c
void bios_vid_mode_set(enum bios_vid_mode mode);
```
**Description**: A wrapper around BIOS interruption 0x10.
**BIOS interruption interface**: 
- `ax`: `mode`
**Parameters**:
- `mode`: A video mode to choose.
