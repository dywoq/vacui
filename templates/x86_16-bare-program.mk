#
# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
#
# Module Description
#
# 		Template for building bare-metal flat programs for x86_16 (Real Mode)
# 		architecture. It works with the toolchain "toolchains/x86_16-bare.toml".
# 		It supports compilation of source files at root of the module only.
#
# Available custom variables
#
# 		FLAGS_C
#
# 			Your own flags for the C compiler.
#
# 		FLAGS_CXX
#
# 			Your own flags for the C++ compiler.
#
# 		FLAGS_LINKER
#
# 			Your own flags for the linker.
#
# 		FLAGS_ASSEMBLY
#
# 			Your own flags for the Assembly.
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

    /DISCARD/ : {
        *(.comment)
        *(.note*)
        *(.eh_frame*)
        *(.eh_frame_hdr)
        *(.gnu*)
        *(.debug*)
        *(.symtab)
        *(.strtab)
        *(.shstrtab)
    }
}
endef


TEMPORARY_LINKER_SCRIPT := __tmpscript.ld
OBJECTS := $(patsubst %.c,$(OBJECTS_DIR)/%.o,$(filter %.c,$(SOURCES))) \
		$(patsubst %.cxx,$(OBJECTS_DIR)/%.o,$(filter %.cxx,$(SOURCES))) \
		$(patsubst %.S,$(OBJECTS_DIR)/%.o,$(filter %.S,$(SOURCES)))

# 
# Adjust the C/C++ flags to the build type
# 

ifeq ($(BUILD_TYPE), RELEASE)
	FLAGS_C += -DRELEASE
	FLAGS_CXX += -DRELEASE
endif

ifeq ($(BUILD_TYPE), DEBUG)
	FLAGS_C += -DDEBUG
	FLAGS_CXX += -DDEBUG
endif

all: $(TARGET_PATH)

$(TARGET_PATH): $(OBJECTS_DIR) $(OBJECTS) $(TEMPORARY_LINKER_SCRIPT)
	@echo " $(TOOLCHAIN_LINKER)		$(TARGET_PATH)"
	$(TOOLCHAIN_LINKER) $(TOOLCHAIN_ADDITIONAL_FLAGS_LINKER) $(OBJECTS) $(FLAGS_LINKER) -T $(TEMPORARY_LINKER_SCRIPT) -o $(TARGET_PATH).elf
	@rm -fr $(TEMPORARY_LINKER_SCRIPT)
	@objcopy -O binary $(TARGET_PATH).elf $(TARGET_PATH)
	@rm -fr $(TARGET_PATH).elf

$(OBJECTS_DIR)/%.o: %.S
	@echo " $(TOOLCHAIN_ASSEMBLY)   $< ... $@"
	@$(TOOLCHAIN_ASSEMBLY) $(TOOLCHAIN_ADDITIONAL_FLAGS_ASSEMBLY) $(FLAGS_ASSEMBLY) -o $@ $<
$(OBJECTS_DIR)/%.o: %.c
	@echo " $(TOOLCHAIN_COMPILER_C)   $< ... $@"
	@$(TOOLCHAIN_COMPILER_C) $(TOOLCHAIN_ADDITIONAL_FLAGS_C) $(FLAGS_C) -o $@ -c $<
$(OBJECTS_DIR)/%.o: %.cxx
	@echo " $(TOOLCHAIN_COMPILER_CXX)   $< ... $@"
	@$(TOOLCHAIN_COMPILER_CXX) $(TOOLCHAIN_ADDITIONAL_FLAGS_CXX) $(FLAGS_CXX) -o $@ -c $<

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)

clean:
	@rm -fr $(OBJECTS_DIR)
	@rm -fr $(TARGET_PATH)
	@rm -fr $(TEMPORARY_LINKER_SCRIPT)

$(TEMPORARY_LINKER_SCRIPT):
	@$(file >$@,$(LINKER_SCRIPT_CONTENT))
