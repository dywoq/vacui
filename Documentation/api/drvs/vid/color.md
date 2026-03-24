# Description 
The `zero/drvs/vid/color.h` header contains color-associated declarations and helpers.
# Symbols
## `drvs_vid_color_rgb`
**Signature**:
```c
struct drvs_vid_color_rgb {
        ubyte_t red;
        ubyte_t green;
        ubyte_t blue;
};
```
**Description**: The RGB color struct definition.
## `DRVS_VID_COLOR_RGB_DEF`
**Signature**:
```c
#define DRVS_VID_COLOR_RGB_DEF(r, g, b)          \
        (struct drvs_vid_color_rgb)              \
        {                                        \
                .red = r, .green = g, .blue = b, \
        }
```
**Description**: A shortcut macro which constructs RGB color struct instance.