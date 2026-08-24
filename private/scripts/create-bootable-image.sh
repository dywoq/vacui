#
# Copyright 2026 dywoq - Apache License 2.0 
# https://github.com/dywoq/vacui
#
# Routine Description
#
#       Bash script for building bootable image.
#
# Environment variables:
#
#       KERNEL_DIR      -> The VQ Kernel directory
#       BOOT_DIR        -> The VQ Boot directory
#       OUTPUT          -> Output file
#

make -C $BOOT_DIR     clean sector
vacbuild build $KERNEL_DIR toolchains/x86_16-bare-metal.toml
dd if=/dev/zero of=$OUTPUT bs=1M count=1
dd if=$BOOT_DIR/.build/vqsector.bin of=$OUTPUT bs=512 conv=notrunc seek=0
dd if=$KERNEL_DIR/ke/vqke.bin of=$OUTPUT bs=512 conv=notrunc seek=64
