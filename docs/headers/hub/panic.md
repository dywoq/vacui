# Description
The `hub/panic.h` header includes a functionality for causing kernel hub panic.

# Symbols
## hub_panic
**Signature**:
```c
[[noreturn]] void hub_panic(const char *msg);
```
**Description**: 
Causes a kernel hub panic, switching the video mode to 0x03  and never returning. 
Must be used in situations where fatal error cannot be recovered.
Cleans up resources.
**Parameters**:
- `msg`: Panic message to print.
