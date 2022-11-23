OSNAME = Silicon

GNUEFI = ../gnu-efi
OVMFDIR = ../OVMFbin
LDS = kernel.ld
CC = clang
LD = ld

CFLAGS = -fno-stack-protector -ffreestanding -fshort-wchar -Isrc -Isrc/kernellib -include src/kernellib/std.h
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib 

SRCDIR := src
OBJDIR := build
BUILDDIR = bin
BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)         
ASMSRC = $(call rwildcard,$(SRCDIR),*.S)         
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
OBJS += $(patsubst $(SRCDIR)/%.S, $(OBJDIR)/%_S.o, $(ASMSRC))
DIRS = $(wildcard $(SRCDIR)/*)

.PHONY: all

all: kernel buildimg

kernel: $(OBJS) link
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo !==== COMPILING $^
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%_S.o: $(SRCDIR)/%.S
	@mkdir -p $(@D)
	$(CC) -c $^ -o $@

link:
	@echo !==== LINKING
	rm -rf $(BUILDDIR)/kernel.elf
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS) 

setup:
	@mkdir $(BUILDDIR)
	@mkdir $(SRCDIR)
	@mkdir $(OBJDIR)

buildimg:
	rm -rf $(BUILDIR)/$(OSNAME).img
	dd if=/dev/zero of=$(BUILDDIR)/$(OSNAME).img bs=512 count=93750
	mkfs.fat -F 32 $(BUILDDIR)/$(OSNAME).img
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/zap-light16.psf ::

run:
	qemu-system-x86_64 -drive file=$(BUILDDIR)/$(OSNAME).img -D log.txt -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$(OVMFDIR)/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="$(OVMFDIR)/OVMF_VARS-pure-efi.fd" -net none -d int

debug:
	qemu-system-x86_64 -drive file=$(BUILDDIR)/$(OSNAME).img -s -S -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$(OVMFDIR)/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="$(OVMFDIR)/OVMF_VARS-pure-efi.fd" -net none -d cpu_reset

clean:
	rm -rf build