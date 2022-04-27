
# $@ = target file
# $< = first dependency
# $^ = all dependencies
ADDRESS :=0x1000
BOOT_DIR:=boot
KERNEL_DIR:=kernel
DRIVER_DIR	:=drivers
LIB_DIR	:=libc

OS_IMAGE:=os.bin
C_SRC:= $(wildcard $(KERNEL_DIR)/*.c $(DRIVER_DIR)/*.c)
C_HEADERS := $(wildcard $(KERNEL_DIR)/*.h $(DRIVER_DIR)/*.h)
SRC_ASM:=$(wildcard $(BOOT_DIR)/*.asm)
OBJ:= ${C_SRC:%.c=%.o}

# GLD and GCC indicate our cross compiler as we installed them with prefix i386-elf 
# to prevent conflict with system gcc and other softwares
ASSM:=nasm
DISASSM := ndisasm
GLD := i386-elf-ld
GCC := i386-elf-gcc
GDB := gdb
C_FLAGS:= -ffreestanding -g

debug: $(OS_IMAGE) kernel.elf
	qemu-system-i386 -s -fda $(OS_IMAGE) &
	$(GDB) -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"


all: run
$(OS_IMAGE): $(BOOT_DIR)/bootsect.bin kernel.bin
	cat $^ > $@

kernel.bin: $(BOOT_DIR)/kernel_entry.o $(OBJ)
	$(GLD) -o $@ -Ttext $(ADDRESS) $^ --oformat binary

kernel.elf:$(BOOT_DIR)/kernel_entry.o $(OBJ)
	$(GLD) -o $@ -Ttext $(ADDRESS) $^


%.o: %.c $(C_HEADERS)
	$(GCC) $(C_FLAGS) -c $< -o $@

%.o: %.asm 
	$(ASSM) $< -f elf -o $@

%.bin: %.asm
	$(ASSM) $< -f bin -o $@

run: $(OS_IMAGE)
	qemu-system-i386 -fda $(OS_IMAGE)

clean:
	rm -rf $(OS_IMAGE) *.bin *.dis *.o *.elf
	rm -rf $(KERNEL_DIR)/*.o $(BOOT_DIR)/*.bin $(DRIVER_DIR)/*.o $(BOOT_DIR)/*.o

# .PHONY: all

