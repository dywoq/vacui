# Description
The `compiler/ld.h` contains declarations that are associated with GNU linker.

# Symbols
## `compiler_ld_start`
**Signature**:
```c
extern char compiler_ld_start;
```
**Description**: A start of binary file. Automatically filled by linker script.
## `compiler_ld_end`
**Signature**:
```c
extern char compiler_ld_end;
```
**Description**: A end of binary file. Automatically filled by linker script.
## `compiler_ld_size`
**Signature**:
```c
static char compiler_ld_size = 0;
```
**Description**: A total size of binary file. Not initialized manually. To initialize it, you need to call `compiler_ld_size_init` function.
## `compiler_ld_size_init`
**Signature**:
```c
static void compiler_ld_size_init();
```
**Description**: Initializes `compiler_ld_size` static variable. Must be started in the start of kernel.
