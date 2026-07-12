# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

#
# Tools
#
ASM := nasm
ASMFLAGS := -f bin

#
# Target, source file and directory
#
BUILD_DIR := .build
SOURCE := sector.S
TARGET := $(BUILD_DIR)/vqbootsect.bin

#
# Rules
#
all: $(TARGET)

$(TARGET): $(SOURCE) $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm -fr $(BUILD_DIR)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

