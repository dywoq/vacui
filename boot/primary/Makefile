# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

NASM := nasm
NASMFLAGS := -f bin

BUILD := .build
SECTOR := primary.S
TARGET := $(BUILD)/primary.bin

all: $(TARGET)

$(TARGET): $(BUILD)
	$(NASM) $(NASMFLAGS) $(SECTOR) -o $(TARGET)
$(BUILD):
	mkdir $(BUILD) -p
clean:
	rm $(BUILD) -fr
