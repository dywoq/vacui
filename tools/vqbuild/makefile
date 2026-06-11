# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

CC := gcc
CFLAGS := --std=c99 -Iinc

BUILD := .build
TARGET := $(BUILD)/vqbuild

MODULES := init \
            err

SRCS := $(foreach m, $(MODULES), $(wildcard $(m)/*.c))
OBJS := $(SRCS:%.c=$(BUILD)/%.o)

.PHONY: all clean dirs

all: dirs $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ -c

dirs:
	mkdir -p $(BUILD)
	$(foreach m, $(MODULES), mkdir -p $(BUILD)/$(m))

clean:
	rm -fr $(BUILD)
