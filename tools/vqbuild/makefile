# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

CXX := g++
CXXFLAGS := --std=c++98 -Iinc

BUILD := .build
TARGET := $(BUILD)/vqbuild

MODULES := init 

SRCS := $(foreach m, $(MODULES), $(wildcard $(m)/*.cxx))
OBJS := $(SRCS:%.cxx=$(BUILD)/%.o)

.PHONY: all clean dirs

all: dirs $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(BUILD)/%.o: %.cxx
	$(CXX) $(CXXFLAGS) $< -o $@ -c

dirs:
	mkdir -p $(BUILD)
	$(foreach m, $(MODULES), mkdir -p $(BUILD)/$(m);)

clean:
	rm -fr $(BUILD)
