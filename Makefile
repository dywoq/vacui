NASM := nasm
NASM_FLAGS := -f bin
BUILD := build
ENTRY := src/bootloader.s
TARGET := $(BUILD)/vacuios.bin

all: $(TARGET)

$(TARGET): $(BUILD)
	$(NASM) $(NASM_FLAGS) $(ENTRY) -o $(TARGET)
	
$(BUILD):
	mkdir $(BUILD) -p

clean:
	rm build -fr
	
qemu: clean $(TARGET)
	qemu-system-i386 $(TARGET)

raw_view: clean $(TARGET)
	ndisasm -b 16 $(TARGET)
