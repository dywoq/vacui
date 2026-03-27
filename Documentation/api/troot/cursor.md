# Description
The `zero/troot/cursor.h` contains the symbols for managing cursor. This works only if VGA mode is `0x03`.
# Symbols
## `troot_cursor_set`
**Signature**:
```c
void troot_cursor_set (ubyte_t row, ubyte_t col);
```
**Description**:
Sets a cursor in the screen at `row` and `col`, directly writing to ports `0x3D4` and `0x3D5`.

**Parameters**:
- `row`, `col`: The new position of the cursor.

