# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

CFLAGS := -m32 -nostdlib -c

BUILD := .build
TARGET := $(BUILD)/sector.bin

SECTOR := sector.S

all: $(TARGET)

$(TARGET): $(BUILD)
	$(CC) $(CFLAGS) $(SECTOR) -o $(TARGET).o
	$(LD) --gc-sections -nostdlib -s -T sector.ld $(TARGET).o -o $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET)

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm $(BUILD) -fr
