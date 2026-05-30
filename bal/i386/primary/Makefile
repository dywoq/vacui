# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

ASFLAGS := -f bin

BUILD := .build
PRIMARY := primary.S
TARGET := $(BUILD)/primary.bin

all: $(TARGET)

$(TARGET): $(BUILD)
	$(AS) $(ASFLAGS) $(PRIMARY) -o $(TARGET)
$(BUILD):
	mkdir $(BUILD) -p
clean:
	rm $(BUILD) -fr
