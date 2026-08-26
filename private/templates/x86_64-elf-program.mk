#
# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
#
# Routine Description
# 
# 		Makefile template for user ELF programs, which works with the 
# 		"private/toolchains/x86_64-elf.toml" toolchain. It 
# 		supports compilation of source files at root of the module only.
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

# 
# Adjust the C flags to the build type
# 

ifeq ($(BUILD_TYPE), RELEASE)
	FLAGS_C += -DRELEASE
endif

ifeq ($(BUILD_TYPE), DEBUG)
	FLAGS_C += -DDEBUG
endif


OBJECTS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(filter %.c,$(SOURCES))) \
		$(patsubst %.cxx,$(OBJS_DIR)/%.o,$(filter %.cxx,$(SOURCES))) \
		$(patsubst %.S,$(OBJS_DIR)/%.o,$(filter %.S,$(SOURCES)))

all: $(TARGET_PATH)

$(TARGET_PATH): $(OBJS_DIR) $(OBJECTS)
	@echo " $(TOOLCHAIN_LINKER)		$(TARGET_PATH)"
	$(TOOLCHAIN_LINKER) $(TOOLCHAIN_ADDITIONAL_FLAGS_LINKER) $(OBJECTS) $(FLAGS_LINKER) -o $(TARGET_PATH)
	
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
