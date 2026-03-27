# Description
The `zero/troot/print.h` contains the symbols for printing the text into the screen in `TerminalRoot`.
# Symbols
## `troot_putc`
**Signature**:
```c
struct vid_text_pos troot_putc (char ch, ubyte_t row, ubyte_t col);
```
**Description**:
Prints a character into the screen with default foreground color (white) and background (black).

Returns the position where the function stopped.

**Parameters**:
- `ch`: The character to print.
- `row`, `col`: The position of the character (row and column).
## `troot_print`
**Signature**:
```c
struct vid_text_pos troot_print (const char *str, ubyte_t row, ubyte_t col);
```
**Description**:
Prints a string into the screen with default foreground color (white) and background (black).
Returns the position where the function stopped.

**Parameters**:
- `str`: The string to print.
- `row`, `col`: The position of the string (row and column).