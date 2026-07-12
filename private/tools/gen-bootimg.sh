#!/usr/bash
# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
#
# Description:
#
#       Responsible for building bootloader parts, and generation 
#       of bootloader image
#

#
# Create temp-build directory and a raw image  
#
rm .build -fr
mkdir .build -p
dd if=/dev/zero of=.build/vacboot.img bs=1M count=8 conv=notrunc

#
# Compile primary and sector, writing their raw data
# to the image
#
make clean all -C vqboot/sector/
dd of=.build/vacboot.img if=vqboot/sector/.build/vqbootsect.bin \
        conv=notrunc \
        bs=512 \
        count=1 \
        seek=0

make clean all -C vqboot/primary/
dd of=.build/vacboot.img if=vqboot/primary/.build/vqbootprim.bin \
        conv=notrunc \
        bs=512 \
        seek=64

