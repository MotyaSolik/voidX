OS_NAME = voidx

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
VNL_DIR = vnl

NASM = nasm
CC = gcc
LD = ld
QEMU = qemu-system-i386

NASMFLAGS = -f elf32
CFLAGS = -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -mno-80387 -mno-mmx -mno-sse -mno-sse2 -fno-stack-protector -I$(VNL_DIR)/src 
LDFLAGS = -m elf_i386 -T $(VNL_DIR)/linker.ld

SRCS_C = $(shell find $(VNL_DIR) -name "*.c")
SRCS_ASM = $(shell find $(VNL_DIR) -name "*.asm")

OBJS = $(patsubst %, $(OBJ_DIR)/%, $(notdir $(SRCS_C:.c=.o))) \
       $(patsubst %, $(OBJ_DIR)/%, $(notdir $(SRCS_ASM:.asm=.o)))

TARGET = $(BUILD_DIR)/$(OS_NAME).bin

VPATH = $(sort $(dir $(SRCS_C) $(SRCS_ASM)))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
	@grub-file --is-x86-multiboot $(TARGET) && echo "=> [Multiboot OK!]" || echo "=> [Ошибка проверки Multiboot]"


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/%.o: %.asm
	@mkdir -p $(OBJ_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@


run: all
	$(QEMU) -kernel $(TARGET)
rund: all
	$(QEMU) -kernel $(TARGET) -d int,cpu_reset -D qemu.log
clean:
	rm -rf $(BUILD_DIR)
	@echo "=> succesfully clean!"
