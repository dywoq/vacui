# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

NASM := nasm
NASMFLAGS := -f bin

INIT := init.S
BUILD := .build
TARGET := $(BUILD)/vqke.bin

all: $(TARGET)

$(TARGET): $(BUILD)
	$(NASM) $(NASMFLAGS) $(INIT) -o $(TARGET)

$(BUILD):
	mkdir -p $(BUILD)
clean:
	rm -fr $(BUILD)
