# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

CC := cc
CFLAGS := -std=c90

SOURCES := main.c

BUILD := .build
TARGET := $(BUILD)/vqbuild

all: $(TARGET)

$(TARGET): $(SOURCES) | $(BUILD)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -fr $(BUILD)