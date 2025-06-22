TARGET   := kernel.elf 
ISO_DIR  := build/iso
BUILD    := build
SRC      := src
CC       := x86_64-elf-gcc
LD       := x86_64-elf-ld
AS       := nasm 
CFLAGS   := -ffreestanding -O2 -Wall -Wextra -nostdlib -m64 -Iinclude -mcmodel=kernel -fno-stack-protector
LDFLAGS  := -T linker.ld -nostdlib -z max-page-size=0x1000 -no-pie

BOOT_OBJS    := $(BUILD)/boot.o
KERNEL_OBJS  := $(BUILD)/kernel.o 
LIBC_SRCS    := $(wildcard $(SRC)/libc/*.c)
LIBC_OBJS    := $(patsubst $(SRC)/libc/%.c, $(BUILD)/libc_%.o, $(LIBC_SRCS))



LIMINE_FILES := limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin

all: iso 

$(BUILD):
	mkdir -p $(BUILD)

$(ISO_DIR):
	mkdir -p $(ISO_DIR)

$(BOOT_OBJS): $(SRC)/boot/boot.s | $(BUILD)
	$(AS) -f elf64 $< -o $@ 

$(KERNEL_OBJS): $(SRC)/kernel/kernel.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/libc_%.o: $(SRC)/libc/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@


$(BUILD)/$(TARGET): $(BOOT_OBJS) $(KERNEL_OBJS) $(LIBC_OBJS)
	$(LD) $(LDFLAGS) $^ -o $@ 



iso: $(BUILD)/$(TARGET) $(ISO_DIR)
	cp $(BUILD)/$(TARGET) $(ISO_DIR)/kernel.elf
	cp src/boot/limine.conf $(ISO_DIR)/limine.conf
	cp $(LIMINE_FILES) $(ISO_DIR)
	xorriso -as mkisofs \
	-b limine-bios-cd.bin \
	-no-emul-boot -boot-load-size 4 -boot-info-table \
	--efi-boot limine-uefi-cd.bin \
	-efi-boot-part --efi-boot-image --protective-msdos-label \
	$(ISO_DIR) -o $(BUILD)/kernel.iso 


clean: 
	rm -rf $(BUILD)

run: iso 
	qemu-system-x86_64 -cdrom $(BUILD)/kernel.iso -serial file:serial.log -m 10G -cpu max -machine q35 -serial stdio  -drive file=limine/limine-9.3.3-binary/limine-bios-hdd.h,format=raw -no-reboot -no-shutdown 
 
	
