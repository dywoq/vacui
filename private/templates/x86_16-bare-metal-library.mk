#
# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
#
# Routine Description
# 
# 		Makefile template for bare-metal libraries, which works with the 
# 		"private/toolchains/x86_16-bare-metal.toml" toolchain. It 
# 		supports compilation of source files at root of the module.
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
# 		FLAGS_ASSEMBLY
# 		
# 			Additional Assembly flags.
# 
# 		LIBRARY_TYPE
# 			
# 			A library type. Supported options: static
#

#
# Static library
# 

ifeq ($(LIBRARY_TYPE), static)

OBJECTS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(filter %.c,$(SOURCES))) \
		$(patsubst %.cxx,$(OBJS_DIR)/%.o,$(filter %.cxx,$(SOURCES))) \
		$(patsubst %.S,$(OBJS_DIR)/%.o,$(filter %.S,$(SOURCES)))

all: $(TARGET_PATH)

$(TARGET_PATH): $(OBJS_DIR) $(OBJECTS)
	@echo " AR  $(TARGET_PATH)"
	@ar rcs $(TARGET_PATH) $(OBJECTS)
	
$(OBJS_DIR)/%.o: %.S
	@echo " $(TOOLCHAIN_ASSEMBLY)   $< ... $@"
	@$(TOOLCHAIN_ASSEMBLY) $(TOOLCHAIN_ADDITIONAL_FLAGS_ASSEMBLY) $(FLAGS_ASSEMBLY) $< -o $@
$(OBJS_DIR)/%.o: %.c
	@echo " $(TOOLCHAIN_COMPILER_C)   $< ... $@"
	$(TOOLCHAIN_COMPILER_C) $(TOOLCHAIN_ADDITIONAL_FLAGS_C) $(FLAGS_C) -c $< -o $@
$(OBJS_DIR)/%.o: %.cxx
	@echo " $(TOOLCHAIN_COMPILER_CXX)   $< ... $@"
	$(TOOLCHAIN_COMPILER_CXX) $(TOOLCHAIN_ADDITIONAL_FLAGS_CXX) $(FLAGS_CXX) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

endif
