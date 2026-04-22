# m1n1 M4 Support Makefile
ARCH = aarch64-linux-gnu-
CC = $(ARCH)gcc
LD = $(ARCH)ld
OBJCOPY = $(ARCH)objcopy

# Flags for Apple Silicon (16K pages + XNU offset)
CFLAGS = -Wall -O2 -nostdlib -ffreestanding -Iinclude
LDFLAGS = -T src/m1n1.ld

# The "Cohort" of files
AS_SOURCES = src/soc/m3_chipset.S
C_SOURCES = src/main.c
RS_SOURCES = src/soc/m4_uart.rs
OBJS = $(AS_SOURCES:.S=.o) $(C_SOURCES:.c=.o)

# The Final Product
all: boot.bin

# Link everything using your 8.2% Linker Script
boot.elf: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o boot.elf

# Turn the ELF into a raw binary for the Mac
boot.bin: boot.elf
	$(OBJCOPY) -O binary boot.elf boot.bin
	@echo "--- Laser Penguin Bootloader Ready: boot.bin ---"

# Compile Assembly
%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) boot.elf boot.bin
