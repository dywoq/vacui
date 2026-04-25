#!/usr/bin/bash

cd boot/load && make all && cd ../../
cd boot/sector && make clean all && cd ../../

dd if=/dev/zero of=vacui.img bs=1M count=10
dd if=boot/sector/.build/sector.bin of=vacui.img conv=notrunc count=1
dd if=boot/load/.build/load.bin of=vacui.img conv=notrunc seek=1
