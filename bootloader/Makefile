all: build

build: clean
	@echo "Building..."
	@mkdir build -p
	@nasm -f bin bootloader.asm -o ./build/bootloader.bin
	@echo "Built :>"
	
clean:
	@rm build -fr

qemu: clean build
	@qemu-system-x86_64 build/bootloader.bin
