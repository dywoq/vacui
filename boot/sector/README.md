This directory contains the boot sector, a critical part of the bootloader.

The boot sector is the first thing the hardware starts. However, it strictly cannot weight higher than 512 bytes (one sector = 512 bytes) and must be written in NASM fully.

Because of the size constraints, It cannot perform following operations:
- Collect the boot information and store it;
- Jump to protected mode; 
- and etc.

To solve this issue, we load **Load Stage** from disk and run the stage, providing control to it.
