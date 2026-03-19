# Description
The `bios/restart.h` contains the functions for cold/warm restarting.
# Symbols
## `bios_restart_cold`
**Signature**:
```c
[[noreturn]] void bios_sys_cold_restart();
```
**Description**: Performs a cold restart, which forces a full hardware reset. Sets the reset flag at `0x40:0x72` to `0x0000` and far jumps to `0xFFFF:0x0000`. Does not return.
## `bios_restart_warm`
**Signature**:
```c
[[noreturn]] void bios_restart_warm();
```
**Description**: Performs a warm restart. It skips the Power-on Self-Test and memory checks. Sets the reset flag at `0x40:0x72` to `0x1234` and far jumps to `0xFFFF:0x0000`. Does not return.