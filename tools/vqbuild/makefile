# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

CXX := g++
CXXFLAGS := --std=gnu++98 -c -Wall -Werror -Iinc

BUILD_DIR := .build
OBJS_DIR := .objs
TARGET := $(BUILD_DIR)/vqbuild

MODULES := hub

SRCS := $(foreach module, $(MODULES), $(wildcard $(module)/*.cxx))
OBJS := $(SRCS:%.cxx=$(OBJS_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$(OBJS_DIR)/%.o: %.cxx | make_modules_dir
	$(CXX) $(CXXFLAGS) $< -o $@

make_modules_dir: $(OBJS_DIR)
	$(foreach module, $(MODULES), mkdir -p $(OBJS_DIR)/$(module))

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -fr $(BUILD_DIR)
	rm -fr $(OBJS_DIR)
