CC = i686-elf-gcc
LD = i686-elf-ld

CFLAGS = -ffreestanding -m32 -O2 -Wall -Wextra
LDFLAGS = -T linker.ld

BUILD = build
SRC = src
ISO = iso

# recursively find all .c files
SRCS := $(shell find $(SRC) -name "*.c")

# map src/xxx.c -> build/xxx.o
OBJS := $(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(SRCS))

KERNEL = $(BUILD)/kernel.elf


all: os.iso


# compile rule (mirrors directory structure)
$(BUILD)/%.o: $(SRC)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


# link everything
$(KERNEL): $(OBJS)
	mkdir -p $(BUILD)
	$(LD) $(LDFLAGS) $^ -o $@


# build ISO
os.iso: $(KERNEL)
	mkdir -p $(ISO)/boot/grub
	cp $(KERNEL) $(ISO)/boot/kernel.elf
	grub-mkrescue -o os.iso $(ISO)


run: os.iso
	qemu-system-i386 -cdrom os.iso -serial stdio


clean:
	rm -rf $(BUILD) os.iso $(ISO)/boot/kernel.elf