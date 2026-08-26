#
# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
#
# Routine Description
# 
# 		Makefile template for bare-metal programs, which works with the 
# 		"private/toolchains/x86_16-bare-metal.toml" toolchain. It 
# 		supports compilation of source files at root of the module only.
# 		Outputs a flat binary file.
#
# Available Options
# 
# 		FLAGS_C
# 		
# 			Additional C compiler flags.
#
# 		FLAGS_CXX
# 		
# 			Additional C++ compiler flags.
# 
# 		FLAGS_LINKER 
# 
# 			Additional linker flags.
# 
# 		FLAGS_ASSEMBLY
# 		
# 			Additional Assembly flags.
# 
# 		LINKER_ENTRY_FUNCTION
# 
# 			Your program entry function. It must be put into the .entry section 
# 			to ensure it is at the start of the flat binary.
# 
# 		LINKER_ADDRESS
# 
# 			Linker address.
#

define LINKER_SCRIPT_CONTENT
OUTPUT_ARCH(i386)
ENTRY($(LINKER_ENTRY_FUNCTION)) 

SECTIONS
{
    . = $(LINKER_ADDRESS);

    .entry	        : { KEEP(*(.entry)) }
    .text           : { *(.text) }
    .rodata         : { *(.rodata) }
    .data           : { *(.data) }
    .bss            : { *(.bss) }

    /DISCARD/ :
    {
        *(.note*)
        *(.eh_frame*)
    }
}
endef

# 
# Adjust the C flags to the build type
# 

ifeq ($(BUILD_TYPE), RELEASE)
	FLAGS_C += -DRELEASE
endif

ifeq ($(BUILD_TYPE), DEBUG)
	FLAGS_C += -DDEBUG
endif


TEMPORARY_LINKER_SCRIPT := __tmpscript.ld
OBJECTS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(filter %.c,$(SOURCES))) \
		$(patsubst %.cxx,$(OBJS_DIR)/%.o,$(filter %.cxx,$(SOURCES))) \
		$(patsubst %.S,$(OBJS_DIR)/%.o,$(filter %.S,$(SOURCES)))

all: $(TARGET_PATH)

$(TARGET_PATH): $(OBJS_DIR) $(OBJECTS) $(TEMPORARY_LINKER_SCRIPT)
	@echo " $(TOOLCHAIN_LINKER)		$(TARGET_PATH)"
	$(TOOLCHAIN_LINKER) $(TOOLCHAIN_ADDITIONAL_FLAGS_LINKER) $(OBJECTS) $(FLAGS_LINKER) -T $(TEMPORARY_LINKER_SCRIPT) -o $(TARGET_PATH).elf
	@rm -fr $(TEMPORARY_LINKER_SCRIPT)
	@objcopy -O binary $(TARGET_PATH).elf $(TARGET_PATH)
	@rm -fr $(TARGET_PATH).elf
	
$(OBJS_DIR)/%.o: %.S
	@echo " $(TOOLCHAIN_ASSEMBLY)   $< ... $@"
	@$(TOOLCHAIN_ASSEMBLY) $(TOOLCHAIN_ADDITIONAL_FLAGS_ASSEMBLY) $(FLAGS_ASSEMBLY) -o $@ $<
$(OBJS_DIR)/%.o: %.c
	@echo " $(TOOLCHAIN_COMPILER_C)   $< ... $@"
	@$(TOOLCHAIN_COMPILER_C) $(TOOLCHAIN_ADDITIONAL_FLAGS_C) $(FLAGS_C) -o $@ -c $<
$(OBJS_DIR)/%.o: %.cxx
	@echo " $(TOOLCHAIN_COMPILER_CXX)   $< ... $@"
	@$(TOOLCHAIN_COMPILER_CXX) $(TOOLCHAIN_ADDITIONAL_FLAGS_CXX) $(FLAGS_CXX) -o $@ -c $<

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@rm -fr $(OBJS_DIR)
	@rm -fr $(TARGET_PATH)
	
$(TEMPORARY_LINKER_SCRIPT):
	@$(file >$@,$(LINKER_SCRIPT_CONTENT))