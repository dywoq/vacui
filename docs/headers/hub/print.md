# Description
The `hub/print.h` header includes printing functionality.

Since printing relies on BIOS video services, the printing works only if BIOS video mode is `0x03`.

# Symbols
## `hub_printnf`
**Signature**:
```c
void hub_printnf(const char *str);
```

**Description**: 
Prints a string into the screen with no formatting.
Automatically moves cursor if it meets newline character in the string.

**Parameters**:
- `str`: A string to print.