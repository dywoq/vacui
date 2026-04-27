#!/usr/bin/bash

cd boot && make clean all && cd ../
xmake

objcopy -O binary .build/linux/x86_64/release/kernel .build/kernel.bin

dd if=/dev/zero of=vacui.img bs=1M count=10
dd if=boot/.build/sector.bin of=vacui.img conv=notrunc count=1
dd if=.build/kernel.bin of=vacui.img conv=notrunc seek=1
