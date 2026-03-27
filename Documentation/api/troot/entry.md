# Description
The `zero/troot/entry.h` contains the symbols that are associated with TerminalRoot entry.
# Symbols
## `troot_entry`
**Signature**:
```c
[[noreturn]] void troot_entry ();
```
**Description**: A TerminalRoot entry function. It does not return due to starting infinity loop.
This function is called inside `hub` if boot mode is TerminalRoot.