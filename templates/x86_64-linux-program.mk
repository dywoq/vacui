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

$(TARGET_PATH): $(OBJECTS_DIR) $(OBJECTS)
	@echo " $(TOOLCHAIN_LINKER)		$(TARGET_PATH)"
	@$(TOOLCHAIN_LINKER) $(TOOLCHAIN_ADDITIONAL_FLAGS_LINKER) $(OBJECTS) -o $(TARGET_PATH)

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
