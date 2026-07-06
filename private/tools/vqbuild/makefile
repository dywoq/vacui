# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/voidmare-st

#
# Compiler
#
CXX := g++
CCFLAGS := -Iinc -std=c++23 -Werror \
	-static-libgcc \
	-static-libstdc++

#
# Target
#
BUILD_DIR := .build
OBJECTS_DIR := .objs
TARGET := $(BUILD_DIR)/vqbuild

#
# Modules
#
MODULES := hub

SOURCES := $(foreach m, $(MODULES), $(wildcard $(m)/*.cxx))
OBJECTS := $(foreach m, $(MODULES), \
    $(patsubst $(m)/%.cxx, $(OBJECTS_DIR)/$(m)/%.o, \
        $(filter $(m)/%.cxx, $(SOURCES))))
#
# Add include directories
#
CXXFLAGS += -Iinc/

#
# Compilation
#
all: print_info $(BUILD_DIR) $(OBJECTS_DIR) create_modules_dirs $(TARGET)

print_info:
	@echo "* Build directory	$(BUILD_DIR)"
	@echo "* Objects directory	$(OBJECTS_DIR)"
	@echo "* Target		$(TARGET)"
	@echo "* Modules		$(MODULES)"
	@echo "* Total source files: 	$(words $(SOURCES))"
	@echo ""

$(TARGET): $(OBJECTS)
	@echo "	Linking		$(TARGET)"
	@$(CXX) $(OBJECTS) -o $(TARGET) $(CXXFLAGS)

$(OBJECTS_DIR)/%.o: %.cxx
	@echo "	Compiling 	$<"
	@$(CXX) $(CXXFLAGS) -o $@ -c $< 

create_modules_dirs:
	@echo "	Creating module directories in objects directory"
	@$(foreach m, $(MODULES), mkdir -p $(OBJECTS_DIR)/$(m);)
$(BUILD_DIR):
	@echo "	Creating build directory"
	@mkdir -p $(BUILD_DIR)
$(OBJECTS_DIR):
	@echo "	Creating objects directory"
	@mkdir -p $(OBJECTS_DIR)
clean: 
	@echo "	Removing build and objects directory"
	@rm -fr $(BUILD_DIR)
	@rm -fr $(OBJECTS_DIR)

help:
	@echo "Commands:"
	@echo "	|	Name	|	  Description		|"
	@echo "	| all		| Build program			|"
	@echo "	| clean		| Delete build artifacts	|"
	@echo "	| print_info	| Print information		|"
	@echo ""

