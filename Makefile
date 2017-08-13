ROOT_DIR := $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
TARGET_ARCH ?= i386
TARGET_ARCHES = i386 x86_64
TARGET_ARCH_DIR = $(ROOT_DIR)/kernel/arch/$(TARGET_ARCH)/src
TARGET_ARCH_BUILD_DIR = $(ROOT_DIR)/build/kernel/arch/$(TARGET_ARCH)/src

include $(ROOT_DIR)/kernel/arch/$(TARGET_ARCH)/make.config

KERNEL_BUILD_DIR = $(ROOT_DIR)/build/kernel/src
KERNEL_SRC_DIR = $(ROOT_DIR)/kernel/src

TARGET_ARCH_A_FILES = $(shell find $(TARGET_ARCH_DIR) -iname '*.asm')
TARGET_ARCH_OBJ_A = $(subst $(TARGET_ARCH_DIR), $(TARGET_ARCH_BUILD_DIR), $(TARGET_ARCH_A_FILES:.asm=.asm.o))

TARGET_ARCH_A_EXPLICIT_FILES = $(shell find $(TARGET_ARCH_DIR) -iname '*.S')
TARGET_ARCH_OBJ_A_EXPLICIT = $(subst $(TARGET_ARCH_DIR), $(TARGET_ARCH_BUILD_DIR), $(TARGET_ARCH_A_EXPLICIT_FILES:.S=.S.o))

TARGET_ARCH_C_FILES = $(shell find $(TARGET_ARCH_DIR) -iname '*.c')
TARGET_ARCH_OBJ_C = $(subst $(TARGET_ARCH_DIR), $(TARGET_ARCH_BUILD_DIR), $(TARGET_ARCH_C_FILES:.c=.c.o))

A_FILES ?= $(shell find $(KERNEL_SRC_DIR) -iname '*.s')
OBJ_A ?= $(subst $(KERNEL_SRC_DIR), $(KERNEL_BUILD_DIR), $(A_FILES:.s=.s.o))

C_FILES ?= $(shell find $(KERNEL_SRC_DIR) -iname '*.c')
OBJ_C ?= $(subst $(KERNEL_SRC_DIR), $(KERNEL_BUILD_DIR), $(C_FILES:.c=.c.o))

KERNEL_INCLUDE_DIRS := -I$(ROOT_DIR)/kernel/include/
KERNEL_INCLUDE_DIRS += -I$(ROOT_DIR)/kernel/include/freestanding/
KERNEL_INCLUDE_DIRS += -I$(ROOT_DIR)/kernel/arch/$(TARGET_ARCH)/include/

KERNEL_MACROS := -D __SWARM_OS__

AA ?= $(ROOT_DIR)/freestanding/toolchain/clang/bin/clang
CC ?= $(ROOT_DIR)/freestanding/toolchain/clang/bin/clang
LL ?= $(ROOT_DIR)/freestanding/toolchain/clang/bin/clang

WARN := -W
WARN += -Wall
WARN += -Wextra
WARN += -Wpedantic
WARN += -Winline
WARN += -Werror
#too many false positives WARN  = -Wconversion
WARN += -Wdouble-promotion
WARN += -Wformat=2
WARN += -Wfloat-equal
WARN += -Wundef
WARN += -Wbad-function-cast
#overkill WARN += -Wcast-qual
WARN += -Wwrite-strings
WARN += -Wmissing-prototypes
WARN += -Wredundant-decls
WARN += -Wshadow
WARN += -Wtype-limits
WARN += -Wstrict-overflow=5 -fstrict-overflow
WARN += -Wsign-compare

#TARGET_OPT := -Oz -fomit-frame-pointer
TARGET_OPT := -Oz -ggdb -fomit-frame-pointer

COMMON_FEATURES := -std=c99 -integrated-as -fstack-protector-all -ffreestanding  -nostdinc -nostdlib \
		  -fno-builtin -fomit-frame-pointer -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow

ifeq ($(TARGET_ARCH), i386)
	ARCH_FLAGS := -m32
	ARCH_FLAGS_AA := $(ARCH_FLAGS) --target=i686-pc-none-elf -march=i686
	ARCH_FLAGS_CC := $(ARCH_FLAGS)
	ARCH_FLAGS_LL := $(ARCH_FLAGS) -Wl,-nostdlib -Wl,-melf_i386_fbsd -Wl,-T
endif
ifeq ($(TARGET_ARCH), x86_64)
	ARCH_FLAGS :=
	ARCH_FLAGS_AA := $(ARCH_FLAGS)
	ARCH_FLAGS_CC := $(ARCH_FLAGS)
	ARCH_FLAGS_LL := $(ARCH_FLAGS) -Wl,-nostdlib -Wl,-T
endif

AFLAGS ?= $(TARGET_OPT) $(ARCH_FLAGS_AA) $(COMMON_FEATURES) $(WARN)
CFLAGS ?= $(TARGET_OPT) $(ARCH_FLAGS_CC) $(COMMON_FEATURES) $(WARN) $(KERNEL_MACROS) $(KERNEL_INCLUDE_DIRS)
LFLAGS ?= $(TARGET_OPT) $(ARCH_FLAGS_LL) $(COMMON_FEATURES) $(WARN) $(KERNEL_MACROS) $(KERNEL_INCLUDE_DIRS)\
		  $(ROOT_DIR)/kernel/arch/$(TARGET_ARCH)/linker.ld

TARGET = swarm
TARGET_UNAME = $(TARGET)_$(TARGET_ARCH)_v$(VERSION)

define GRUB_CFG
set timeout=15
set default=0

menuentry "$(TARGET_UNAME)" {
	multiboot /boot/$(TARGET_UNAME).bin
	boot
}
endef
export GRUB_CFG

all: build/$(BINARIES) kernel

$(TARGET_ARCH_BUILD_DIR)/crtbegin.o $(TARGET_ARCH_BUILD_DIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(TARGET_ARCH_BUILD_DIR)/%.asm.o: $(TARGET_ARCH_DIR)/%.asm
	@mkdir -p $(@D)
	$(AA) $(AFLAGS) -c -o $@ $<

$(TARGET_ARCH_BUILD_DIR)/%.S.o: $(TARGET_ARCH_DIR)/%.S
	@mkdir -p $(@D)
	$(AA) $(AFLAGS) -c -o $@ $<

$(TARGET_ARCH_BUILD_DIR)/%.c.o: $(TARGET_ARCH_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(KERNEL_BUILD_DIR)/%.s.o: $(KERNEL_SRC_DIR)/%.s
	@mkdir -p $(@D)
	$(AA) $(AFLAGS) -c -o $@ $<

$(KERNEL_BUILD_DIR)/%.c.o: $(KERNEL_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

build/$(TARGET_UNAME).bin: $(OBJ_A) $(OBJ_C) $(TARGET_ARCH_OBJ_A_EXPLICIT) $(TARGET_ARCH_OBJ_A) $(TARGET_ARCH_OBJ_C) $(TARGET_ARCH_BUILD_DIR)/crtbegin.o $(TARGET_ARCH_BUILD_DIR)/crtend.o
	$(LL) $(LFLAGS) $(TARGET_ARCH_BUILD_DIR)/crti.S.o $(TARGET_ARCH_BUILD_DIR)/crtbegin.o $(TARGET_ARCH_BUILD_DIR)/boot.S.o $(TARGET_ARCH_OBJ_A) $(TARGET_ARCH_OBJ_C) $(OBJ_A) $(OBJ_C) $(TARGET_ARCH_BUILD_DIR)/crtend.o $(TARGET_ARCH_BUILD_DIR)/crtn.S.o -o $@

kernel: build/$(TARGET_UNAME).bin check_is_multiboot stripped disasm iso sym
	du -A -B 512 build/$(TARGET_UNAME).bin

check_is_multiboot: build/$(TARGET_UNAME).bin
	grub-file --is-x86-multiboot build/$(TARGET_UNAME).bin

disasm: build/$(TARGET_UNAME).bin
	objdump -dxtwl build/$(TARGET_UNAME).bin > build/$(TARGET_UNAME).disasm
	objdump -swl -j .rodata build/$(TARGET_UNAME).bin >> build/$(TARGET_UNAME).disasm

stripped: build/$(TARGET_UNAME).bin
	cp build/$(TARGET_UNAME).bin build/$(TARGET_UNAME).stripped.bin
	strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.comment --remove-section=.eh_frame --remove-section=.eh_frame_hdr build/$(TARGET_UNAME).stripped.bin
	sstrip -z build/$(TARGET_UNAME).stripped.bin

sym: build/$(TARGET_UNAME).bin
	objcopy --only-keep-debug build/$(TARGET_UNAME).bin build/$(TARGET_UNAME).sym

grub:
	echo "$$GRUB_CFG" > $(ROOT_DIR)/build/iso/boot/grub/grub.cfg

iso: grub build/$(TARGET_UNAME).bin
	cp build/$(TARGET_UNAME).bin build/iso/boot/$(TARGET_UNAME).bin
	grub-mkrescue -o $(ROOT_DIR)/build/iso/boot/$(TARGET_UNAME).iso build/iso

clean:
	rm -rf build
	mkdir -p build/kernel/src
	mkdir -p build/logs
	mkdir -p build/iso/boot/grub

qemu:
	E:\apps\qemu\qemu-system-i386 -cdrom $(ROOT_DIR)/build/iso/boot/$(TARGET_UNAME).iso -gdb tcp::1234

gdb:
	E:\mingw\bin\gdb -ex 'target remote localhost:1234' -ex 'symbol-file build/$(TARGET_UNAME).sym' -ex 'break _start' -ex 'set disassemble-next-line on' -ex 'c'

test: qemu gdb


install:
	echo true
