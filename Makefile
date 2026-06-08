# Имя вашей операционной системы
OS_NAME = voidx

# Директории
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
VNL_DIR = vnl

# Утилиты
NASM = nasm
CC = gcc
LD = ld
QEMU = qemu-system-i386

# Флаги
NASMFLAGS = -f elf32
CFLAGS = -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(VNL_DIR)/src
LDFLAGS = -m elf_i386 -T $(VNL_DIR)/linker.ld

# Поиск всех исходников в vnl и vnl/src (включая подпапки вроде drivers)
SRCS_C = $(shell find $(VNL_DIR) -name "*.c")
SRCS_ASM = $(shell find $(VNL_DIR) -name "*.asm")

# Формирование путей для .o файлов в build/obj
OBJS = $(patsubst %, $(OBJ_DIR)/%, $(notdir $(SRCS_C:.c=.o))) \
       $(patsubst %, $(OBJ_DIR)/%, $(notdir $(SRCS_ASM:.asm=.o)))

TARGET = $(BUILD_DIR)/$(OS_NAME).bin

# Пути поиска для make, чтобы он знал, где искать исходники по имени файла
VPATH = $(sort $(dir $(SRCS_C) $(SRCS_ASM)))

.PHONY: all clean run

all: $(TARGET)

# Линковка финального бинарника
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
	@grub-file --is-x86-multiboot $(TARGET) && echo "=> [Multiboot OK!]" || echo "=> [Ошибка проверки Multiboot]"

# Компиляция ВСЕХ Си-файлов (включая drivers/vga.c)
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция Ассемблер-файлов (boot.asm)
$(OBJ_DIR)/%.o: %.asm
	@mkdir -p $(OBJ_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@

# Запуск в QEMU
run: all
	$(QEMU) -kernel $(TARGET)

# Очистка
clean:
	rm -rf $(BUILD_DIR)
	@echo "=> Папка build успешно удалена!"
