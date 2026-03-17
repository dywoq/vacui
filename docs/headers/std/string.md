# Description
The `std/string.h` header includes a functionality for managing strings.
# Symbols
## string_len
**Signature**:
```c
[[nodiscard]] word_t string_len(const char *str);
```
**Description**: 
Returns the length of `str`, using for-loop. It's recommended to call `string_len` once, since for-loop can be slow for big strings.

**Parameters**:
- `str`: The string.
