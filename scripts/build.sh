#!/usr/bin/bash

dd if=/dev/zero of=vacui.img bs=1M count=10

# Build boot sector
cd boot/sector && make clean all && cd ../../
dd if=boot/sector/.build/vqboot_sector.bin of=vacui.img conv=notrunc count=1

# Build boot primary stage
xmake build vqboot_primary
objcopy -O binary .build/linux/x86_64/release/vqboot_primary .build/vqboot_primary.bin
dd if=.build/vqboot_primary.bin of=vacui.img conv=notrunc seek=1

# Build kernel
xmake build vqkrnl
objcopy -O binary .build/linux/x86_64/release/vqkrnl .build/vqkrnl.bin
dd if=.build/vqkrnl.bin of=vacui.img conv=notrunc seek=2
