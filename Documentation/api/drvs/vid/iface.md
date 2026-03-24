# Description 
The `zero/drvs/vid/iface.h` header contains a standard interface and methods to interact with the current implementation.
# Symbols
## `drvs_vid_iface`
**Signature**:
```c
struct drvs_vid_iface {
        void (*init) (void);
        void (*draw_pixel_rgb) (word_t x, word_t y,
                                struct drvs_vid_color_rgb *rgb);
        usize_t (*width) (void);
        usize_t (*height) (void);
        void (*exit) (void);
};
```
**Description**:
A standard interface, which is implemented by all video drivers.
**Fields**:
- `init`: Initializes video driver.
- `draw_pixel_rgb`: Draws a RGB pixel to the screen at `x` and `y` position.
- `width`: Returns the maximum resolution width.
- `height`: Returns the maximum resolution height.
- `exit`: Exits the video driver.
## `drvs_vid_get_impl`
**Signature**:
```c
struct drvs_vid_iface *drvs_vid_get_impl (void);
```
**Description**:
Returns the current implementation of video driver.
**Warning**: If no video driver was set, it returns the dummy implementation (methods are empty).
## `drvs_vid_set_impl`
**Signature**:
```c
void drvs_vid_set_impl (struct drvs_vid_iface *i);
```
**Description**:
Sets the new video driver implementation.
**Parameters**:
- `i`: New video driver implementation.