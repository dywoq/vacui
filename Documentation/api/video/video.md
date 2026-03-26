# Description
The `zero/video/video.h` header contains the functionality for managing the video screen.
It's tied to VGA Mode 320x200 0x13 mode.
# Symbols
## `video_width
**Signature**:
```c
usize_t video_width (void);
```
**Description**: Returns the maximum resolution width of video screen.
## `video_height`
**Signature**:
```c
usize_t video_height (void);
```
**Description**: Returns the maximum resolution height of video screen.
## `video_draw_pixel`
**Signature**:
```c
void video_draw_pixel (usize_t x, usize_t y, ubyte_t col);
```
**Description**: Draws a pixel to the video screen. 

This operation is considered slow for drawing rectangles, triangles etc., due to high intensity of function calls.

**Parameters**:
- `x`, `y`: The location where to draw pixel.
- `col`: A color to draw (notice this is VGA mode 320x200 0x13)
