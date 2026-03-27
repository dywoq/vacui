# Description
The `zero/vid/text.h` header contains the functionality for printing the character and text in VGA mode 0x03 (`0xB8000`).
# Symbols
## `vid_text_pos`
**Signature**:
```c
struct vid_text_pos {
        ubyte_t row;
        ubyte_t col;
};
```
**Description**: Contains the position in the text mode.
## `vid_text_width`
**Signature**:
```c
static constexpr usize_t vid_text_width = 80;
```
**Description**: A maximum resolution width.

## `vid_text_height`
**Signature**:
```c
static constexpr usize_t vid_text_height = 25;
```
**Description**: A maximum resolution height.

## `vid_text_putc`
**Signature**:
```c
struct vid_text_pos vid_text_putc (char ch, ubyte_t fg_color, ubyte_t bg_color,
                                   ubyte_t row, ubyte_t col);
```
**Description**:
Draws character to the VGA memory.

It doesn't know whether the current position (`row` and `col`) is already taken, which means it can redraw your character at the same position.

Returns the position where the function stopped.

**Parameters**:
- `ch`: A character to draw.
- `fg_color`: Foreground color of the character.
- `bg_color`: Background color of the character.
- `row`: Row, where the character is placed.
- `col`: Column, where the character is placed.
## `vid_text_put`
**Signature**:
```c
struct vid_text_pos vid_text_put (const char *str, ubyte_t fg_color,
                                  ubyte_t bg_color, ubyte_t row, ubyte_t col);
```
**Description**:
Draws an immutable string to the VGA memory.

The function doesn't check if string is null; The function doesn't know whether the current position are already taken by other characters.

If it encounters newline character (`\n`) during the loop, it increases row and sets the current column to `col`. 

Returns the position where the function stopped.

**Parameters**:
- `str`: A string to draw.
- `fg_color`: Foreground color. Applies to the whole string.
- `bg_color`: Background color. Applies to the whole string.
- `row`: Row where the string is placed.
- `col`: Column where the string is placed.