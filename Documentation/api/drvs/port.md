# Description
The `zero/drvs/port.h` header contains the functions for managing I/O ports.

# Symbols
## `drvs_port_outb`
**Signature**:
```c
void drvs_port_outb (ubyte_t value, uword_t port);
```
**Description**: The function writes a byte to given port.
**Parameters**:
- `value`: The byte to write.
- `port`: The given port.
## `drvs_port_inb`
**Signature**:
```c
ubyte_t drvs_port_inb (uword_t port);
```
**Description**: The function reads a port and returns its bytes.
**Parameters**:
- `port`: The port to read.