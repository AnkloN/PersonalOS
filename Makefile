
# $@ = target file
# $< = first dependency
# $^ = all dependencies
ADDRESS :=0x1000
BOOT_DIR:=boot
SRC_DIR:=src
OBJ_DIR:=obj
BIN_DIR := bin

OS_IMAGE=$(BOOT_DIR)/os-image.bin
SRC := $(wildcard $(SRC_DIR)/*.c)
BIN := $(wildcard $(BIN_DIR)/*.bin)
SRC_ASM :=$(wildcard $(SRC_DIR)/*.asm)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o,$(SRC))

GLD := i386-elf-ld
GCC := i386-elf-gcc
CCFLAGS:= -ffreestanding
ASSM:=nasm
DISASSM := ndisasm

all: run

$(BIN_DIR)/kernel.bin: $(OBJ_DIR)/kernel_entry.o $(OBJ_DIR)/kernel.o
	$(GLD) -o $@ -Ttext $(ADDRESS) $^ --oformat binary


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(GCC) $(CCFLAGS) -c $< -o $@

$(OBJ_DIR)/kernel_entry.o: $(SRC_DIR)/kernel_entry.asm
	$(ASSM) $< -f elf -o $@

$(BIN_DIR)/kernel.dis: $(BIN_DIR)/kernel.bin
	$(DISASSM) -b 32 $< > $@

$(BIN_DIR)/bootsect.bin: $(SRC_DIR)/bootsect.asm
	$(ASSM) $< -f bin -i $(SRC_DIR) -o $@


$(OS_IMAGE): $(BIN_DIR)/bootsect.bin $(BIN_DIR)/kernel.bin
	cat $^ > $@

run: $(OS_IMAGE)
	qemu-system-i386 -fda $(OS_IMAGE)

clean:
	rm $(OS_IMAGE) $(BIN_DIR)/* $(OBJ_DIR)/*

# .PHONY: all

