OS_NAME = voidx

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
VNL_DIR = vnl

# Настройки диска
IMG_DIR = img
DISK_IMG = disk.img

NASM = nasm
CC = gcc
LD = ld
QEMU = qemu-system-i386

NASMFLAGS = -f elf32
CFLAGS = -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -mno-80387 -mno-mmx -mno-sse -mno-sse2 -fno-stack-protector -Ivnl/src/drivers/inc
LDFLAGS = -m elf_i386 -T $(VNL_DIR)/linker.ld

SRCS_C = $(shell find $(VNL_DIR) -name "*.c")
SRCS_ASM = $(shell find $(VNL_DIR) -name "*.asm")

OBJS = $(patsubst %, $(OBJ_DIR)/%, $(notdir $(SRCS_C:.c=.o))) \
       $(patsubst %, $(OBJ_DIR)/%, $(notdir $(SRCS_ASM:.asm=.o)))

# Теперь целевой файл сразу называется kernel.elf для красоты внутри твоей UNIX-структуры
TARGET = $(BUILD_DIR)/kernel.elf

VPATH = $(sort $(dir $(SRCS_C) $(SRCS_ASM)))

.PHONY: all clean run rund disk

all: disk

# 1. Сборка самого бинарника ядра
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

# 2. Создание единого системного жесткого диска
disk: $(TARGET)
	@echo "=== Building Unified System Disk via Grub-MKRescue ==="
	# 1. Создаем изолированную временную папку в /tmp/ твоего компьютера
	# Это гарантирует, что в твоем проекте больше никогда не зависнут права root!
	$(eval TMP_DIR := $(shell mktemp -d))
	
	# 2. Создаем UNIX-структуру папок внутри временной директории
	mkdir -p $(TMP_DIR)/sys
	mkdir -p $(TMP_DIR)/bin
	mkdir -p $(IMG_DIR)/usr # Локальную пустую папку можешь оставить для себя
	mkdir -p $(TMP_DIR)/dev
	mkdir -p $(TMP_DIR)/boot/grub
	
	# 3. Копируем твое ядро в /sys/kernel.elf
	cp $(TARGET) $(TMP_DIR)/sys/kernel.elf
	
	# 4. Генерируем конфиг GRUB
	@mkdir -p grub_config
	@echo 'set timeout=0\nset default=0\nmenuentry "VoidX OS" {\n    multiboot /sys/kernel.elf\n    boot\n}' > grub_config/grub.cfg
	cp grub_config/grub.cfg $(TMP_DIR)/boot/grub/grub.cfg
	
	# 5. Записываем триггер краша
	echo -n "0" > $(TMP_DIR)/dev/crash.txt
	
	# 6. Магия: grub-mkrescue собирает гибридный образ.
	# Флаг --modules заставляет его вшить драйверы fat и multiboot
	grub-mkrescue --modules="fat multiboot normal" -o $(DISK_IMG) $(TMP_DIR)
	
	# 7. Удаляем временный мусор с твоего ПК
	rm -rf $(TMP_DIR)
	
	@echo "=== Unified Disk Built! Target: $(DISK_IMG) ==="



# Запуск системы как полноценного ПК с жестким диском (Основной режим)
run: disk
	$(QEMU) -cdrom $(DISK_IMG) -d int,cpu_reset -D qemu.log



# Твой старый отладочный режим прямой загрузки ядра (минуя диск)
rund: $(TARGET)
	$(QEMU) -kernel $(TARGET) -d int,cpu_reset -D qemu.log

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(IMG_DIR)
	rm -f $(DISK_IMG)
	@echo "=> successfully clean!"
