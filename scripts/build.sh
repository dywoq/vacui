#!/usr/bin/bash

rm vacui.img -fr

mkdir .build -p

cd boot/sector && make clean all && cd ../../
cd boot/primary && make clean all && cd ../../
xmake && objcopy -O binary .build/linux/x86_64/release/kernel .build/kernel.bin

dd if=/dev/zero of=vacui.img bs=1M count=10
dd if=boot/sector/.build/sector.bin of=vacui.img conv=notrunc count=1 bs=512
dd if=boot/primary/.build/primary.bin of=vacui.img conv=notrunc seek=1 bs=512 
dd if=.build/kernel.bin of=vacui.img conv=notrunc seek=2 bs=512
