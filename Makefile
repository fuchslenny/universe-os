EXEC = UniverseOS.bin
CC = gcc
SHELL = /bin/sh
SRCDIR = src
KERNELDIR = src/kernel
SOURCES = $(shell find src -type f -name '*.c')
OBJECTS = $(SOURCES:.c=.o)
ASMS = $(shell find src -type f -name '*.asm')
ASMO = $(ASMS:.asm=.o)

CFLAGS = -m32 -Wall -Wextra -ffreestanding -std=gnu99 -Isrc/include/UniverseOS
 
BUILDDIR = build
BUILDOBJ = $(addprefix build/, $(notdir $(OBJECTS)))
ASMBO = $(addprefix build/, $(notdir $(ASMO)))
ISODIR = build/iso
BOOTDIR = build/iso/boot
GRUBDIR = build/iso/boot/grub
TARGET_ISO=build/UniverseOS.iso

all: dir $(EXEC)

$(EXEC): $(OBJECTS) $(ASMO)
	echo $(ASMS)

	$(info $$ASMS is [${ASMS}])

	ld -nostdlib -m elf_i386 -T $(SRCDIR)/linker.ld $(ASMBO) $(BUILDOBJ) -o $(BUILDDIR)/$(EXEC)
	mkdir -p $(GRUBDIR)
	cp build/UniverseOS.bin $(BOOTDIR)/$(EXEC)
	cp $(SRCDIR)/grub.cfg $(GRUBDIR)/grub.cfg
	grub-mkrescue -o $(TARGET_ISO) $(ISODIR)



$(OBJECTS): %.o : %.c
	BASENAME="$(notdir $@)"
	$(CC) -c $(CFLAGS) $< -o $(BUILDDIR)/$(notdir $@)

$(ASMO): %.o : %.asm
	BASENAME="$(notdir $@)"
	nasm -felf32 $< -o $(BUILDDIR)/$(notdir $@)

clean:
	-rm -rf build/*

dir:
	@mkdir -p build
	@mkdir -p build/bin

run: all
	 qemu-system-x86_64 -serial file:serial.log -cdrom $(TARGET_ISO)
