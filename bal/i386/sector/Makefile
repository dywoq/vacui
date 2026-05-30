# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

ASFLAGS := -f bin

BUILD := .build
SECTOR := sector.S
TARGET := $(BUILD)/sector.bin

all: $(TARGET)

$(TARGET): $(BUILD)
	$(AS) $(ASFLAGS) $(SECTOR) -o $(TARGET)
$(BUILD):
	mkdir $(BUILD) -p
clean:
	rm $(BUILD) -fr
