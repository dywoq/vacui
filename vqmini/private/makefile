# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
# 
# Description:
# 
# 	Building process management

BUILD := .build
IMAGE := .build/vacui.img

make_image: $(BUILD)
	make clean all -C bootsect
	make clean all -C ke
	dd if=/dev/zero of=$(IMAGE) bs=1M count=10
	dd if=bootsect/.build/vqbootsect.bin of=$(IMAGE) bs=512 count=1 conv=notrunc
	dd if=ke/.build/vqke.bin of=$(IMAGE) bs=512 seek=128 conv=notrunc
	
clean:
	rm -fr $(BUILD)
	
help:
	@echo "Commands:"
	@echo ""
	@echo "     image      Builds boot sector and kernel, resulting in image"

$(BUILD):
	mkdir -p $(BUILD)