# Description
The `mem/far.h` header contains functionality for managing far pointers, using segmented memory model in 16 bit.

Far pointers are 32 bit `segment:offset` pointers, used to access more than `64kiB`.
# Symbols
## mem_far_readb
**Signature**:
```c
#define mem_far_readb(b, segment, offset)
```
**Description**: 
Reads from  `segment:offset` memory and writes it into `b`, using `DS:BX` registers, because It's the standard combination for reading data from memory.

It's bytes version.

**Parameters**:
- `b`:  Destination.
- `segment`: Segment (for `segment:offset`).
- `offset`: Offset (for `segment:offset`)
## mem_far_writeb
**Signature**:
```c
#define mem_far_writeb(val, segment, offset)
```
**Description**: 
Writes `val` to  `segment:offset` memory, using `ES:DI` registers, because it's the standard combination for writing data to memory.

It's bytes version.

**Parameters**:
- `val`:  A value to write.
- `segment`: Segment (for `segment:offset`).
- `offset`: Offset (for `segment:offset`)
 