# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

CXX := g++
CXXFLAGS := -std=c++98

SOURCES := main.cxx vqbconf.cxx vqbrun.cxx vqbcross.cxx \
		vqbarg.cxx

BUILD := .build
TARGET := $(BUILD)/vqbuild

all: $(TARGET)

$(TARGET): $(SOURCES) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -fr $(BUILD)
