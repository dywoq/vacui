# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
#
# Description:
#
# 	Vacui public SDk headers
#

#
# Compiler
#
CC := gcc
CFLAGS := -Iinc -std=c23 -Werror -nostdlib -ffreestanding
AR := ar
ARFLAGS := rcs

#
# Target
#
BUILD_DIR := .build
OBJECTS_DIR := .objs/
TARGET := $(BUILD_DIR)/libvacuisdk.a

#
# Modules
#
MODULES := foo

SOURCES := $(foreach m, $(MODULES), $(wildcard $(m)/*.c))
OBJECTS := $(foreach m, $(MODULES), \
    $(patsubst $(m)/%.c, $(OBJECTS_DIR)/$(m)/%.o, \
        $(filter $(m)/%.c, $(SOURCES))))

#
# Add include directories
#
CFLAGS += -Iinc/

#
# Handle build type
#
BUILD_TYPE ?= debug
ifeq ($(BUILD_TYPE), debug)
	CFLAGS += -D_DEBUG -g
endif

ifeq ($(BUILD_TYPE), release)
	CFLAGS += -D_RELEASE
endif

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
	@echo "	Archiving	$(TARGET)"
	@$(AR) $(ARFLAGS) $(TARGET) $(OBJECTS)

$(OBJECTS_DIR)/%.o: %.c
	@echo "	Compiling 	$<"
	@$(CC) $(CFLAGS) -o $@ -c $< 

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
	@echo "	| all		| Build SDK			|"
	@echo "	| clean		| Delete build artifacts	|"
	@echo "	| print_info	| Print information		|"
	@echo ""

