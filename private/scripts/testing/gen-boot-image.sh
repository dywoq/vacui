#
# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
# 
# Module Description
# 
#       Generates a raw image, containing VQBoot sector and primary stages. 
#       It builds the boot loader first before generating the raw image.
#       
#       The script must be ran from the private/ directory.
# 
# Required variables
# 
#       BOOT_DIR
# 
#           A directory with the boot loader.
# 
#       OUTPUT
#           
#           Where to write the image.  
# 
# Purpose
# 
#       Testing 
# 

vacbuild build $BOOT_DIR toolchains/x86_16-bare-metal.toml debug
dd if=/dev/zero of=$OUTPUT bs=1M count=10
dd if=$BOOT_DIR/sector/vqbootsector.bin of=$OUTPUT bs=512 seek=0 conv=notrunc
dd if=$BOOT_DIR/primary/vqbootprimary.bin of=$OUTPUT bs=512 seek=64 conv=notrunc
