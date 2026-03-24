This document shows how to build operating system, and which tools are needed.
# Required tools/environment
**Environment:** WSL2 or Linux (Unix-like environment).
**Core build tools**: `make`, `gcc`, `nasm`, `ld`, `objcopy`
**Build scripts**: `python3`, `kconfig-mconf`
**Image creation**: `dd`

**Notice**: The OS targets 32-bit (`-m32` flag), so a 32-bit toolchain is required.
# Steps
1. **Generate `.config` file**: This is needed for kernel. You can do this by running:
```
make menuconfig
```
2. **Run Python script to build `.img` file**:
```
python3 scripts/build_image.py
```
After these steps, your `.img` file must be successfully built.
