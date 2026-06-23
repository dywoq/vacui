# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq

CXX := clang++
CXXFLAGS := -Iinc -std=c++98 -Werror -Wall

BUILD_DIR := .build
OBJECTS_DIR := .objs
TARGET := $(BUILD_DIR)/vqbuild

MODULES := startup
SOURCES := $(foreach m, $(MODULES), $(wildcard $(m)/*.cxx))
OBJECTS := $(foreach m, $(MODULES), $(SOURCES:$(m)/%.cxx=$(OBJECTS_DIR)/$(m)/%.o))

all: $(BUILD_DIR) $(OBJECTS_DIR) create_modules_dirs $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJECTS_DIR)/%.o: %.cxx
	$(CXX) $(CXXFLAGS) -o $@ -c $< 

create_modules_dirs:
	$(foreach m, $(MODULES), mkdir -p $(OBJECTS_DIR)/$(m))
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)
clean:
	rm -fr $(BUILD_DIR)
	rm -fr $(OBJECTS_DIR)

help:
	@echo "	all	Build vqbuild"
	@echo "	clean	Delete build artifacts"

