#!/usr/bin/bash

mkdir .build -p

cd boot/sector && make clean all && cd ../../
cd boot/primary && make all && cd ../../

dd if=/dev/zero of=vacui.img bs=1M count=10
dd if=boot/sector/.build/sector.bin of=vacui.img conv=notrunc count=1
dd if=boot/primary/.build/primary.bin of=vacui.img conv=notrunc seek=1
