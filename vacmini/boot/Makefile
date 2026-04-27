ASM := nasm
ASMFLAGS := -f bin

SECTOR := sector.S

BUILD ?= .build
TARGET := $(BUILD)/sector.bin

all: $(TARGET)

$(TARGET): $(BUILD)
	@echo " ASM 	$(SECTOR)"
	@$(ASM) $(ASMFLAGS) $(SECTOR) -o $(TARGET)
	@echo "Build is completed."
	@echo "Output: $(TARGET)"
$(BUILD):
	@mkdir -p $(BUILD)

clean:
	@echo " RM	$(BUILD)"
	@rm $(BUILD) -fr

help:
	@echo "Env variables:"
	@echo "	BUILD	Build directory (default is .build)"
	@echo ""
	@echo "Commands:"
	@echo " all 	Build boot sector"
	@echo " help	Output this text"
	@echo " clean	Clean build artifacts"
