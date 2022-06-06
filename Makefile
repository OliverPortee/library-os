# -----------------------------------------------------------------------------
# 
#                              M A K E F I L E
# 
# for building OOStuBS, the teaching OS for "Operating-System Construction"
# -----------------------------------------------------------------------------
#
# By entering 'make', the system's source codes get compiled and linked.
# 'make bootdisk' writes the system image to an USB stick that allows to boot
# the system on a real machine.
# 'make clean' cleans up the directory.
# The targets 'qemu', 'qemu-smp' and 'qemu-gdb' start the QEMU emulator in
# single-core mode, multi-core mode (2 CPUs), respectively in single-core mode
# waiting for a debugger to attach before starting the system.
# The targets 'gdb', 'ddd' and 'cgdb' each run one of these three debuggers
# that automatically connect to the GDB stub of an already started 'qemu-gdb'
# (see above).
#
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# source-code files

STARTUP_SOURCE = ./startup.asm
CC_SOURCES = $(shell find . -name "*.cc")
C_SOURCES = $(shell find . -name "*.c")
ASM_SOURCES = $(shell find ./machine -name "*.asm")

# build settings
#
#    ASMOBJFORMAT: assembler output format (must match the format of the used
#                  C++ compiler to make linking possible)
#    OBJDIR:       directory for storing object files
#    DEPDIR:       directory for storing dependency files
#    DRIVE_HD:     HDD/USB device the system image gets written to
#                  with 'make bootdisk'
#    DELETE:       file-deletion command
#    ASM:          assembler command
#    CC/CXX:       C/C++ compiler command
#    CFLAGS:       C-compiler flags
#    CXXFLAGS:     C++-compiler flags
#    QEMU:         architecture-specific name of the QEMU command
#    MKRESCUE:     name of the GRUB mkrescue program

VERBOSE = @
ASMOBJFORMAT = elf64
OBJDIR = ./build
DEPDIR = ./dep
# ATTENTION: using the wrong device name here will destroy data on the specified
# device! Do not run with root privileges!
DRIVE_HD = /dev/sdz
DELETE = rm
ASM = nasm
QEMU ?= qemu-system-x86_64
CC ?= gcc
CXX ?= g++
CFLAGS := $(CFLAGS) -m64 -mno-red-zone -Wall -Wno-write-strings -fno-stack-protector -nostdlib -mno-sse -I. -g #-DDEBUG
CXXFLAGS := $(CFLAGS) -Wno-non-virtual-dtor -fno-threadsafe-statics -fno-use-cxa-atexit -fno-rtti -fno-exceptions

# enforce i386-pc grub variant also on EFI systems
ifneq ($(wildcard /usr/lib/grub/i386-pc/.),)
        MKRESCUE_OPTION ?= /usr/lib/grub/i386-pc
else ifneq ($(wildcard /usr/share/grub2/i386-pc/.),)
        MKRESCUE_OPTION ?= /usr/share/grub2/i386-pc
else
        MKRESCUE_OPTION ?=
endif

ifneq ($(shell which grub-mkrescue 2> /dev/null),)
MKRESCUE = grub-mkrescue $(MKRESCUE_OPTION)
endif
ifneq ($(shell which grub2-mkrescue 2> /dev/null),)
MKRESCUE = grub2-mkrescue $(MKRESCUE_OPTION)
endif

# -------------------------------------------------------------------------
# names of sub-directories with source-code files

VPATH = $(sort $(dir $(STARTUP_SOURCE) $(CC_SOURCES) $(C_SOURCES) $(ASM_SOURCES)))

# -------------------------------------------------------------------------
# lists of object files that are generated during compilation

FIRST_OBJECT = $(addprefix $(OBJDIR)/,$(patsubst %.asm,_%.o, $(notdir $(STARTUP_SOURCE))))
C_OBJECTS = $(notdir $(C_SOURCES:.c=.o))
CC_OBJECTS = $(notdir $(CC_SOURCES:.cc=.o))

DEP_FILES = $(patsubst %.o,$(DEPDIR)/%.d,$(C_OBJECTS))
DEP_FILES += $(patsubst %.o,$(DEPDIR)/%.d,$(CC_OBJECTS))

ASM_OBJECTS = $(patsubst %.asm,_%.o, $(notdir $(ASM_SOURCES)))
OBJPRE = $(addprefix $(OBJDIR)/,$(ASM_OBJECTS) $(C_OBJECTS) $(CC_OBJECTS))

# --------------------------------------------------------------------------
# Default target: the image file for USB sticks and QEMU

all: $(OBJDIR)/bootdisk.iso

# --------------------------------------------------------------------------
# rules for generating dependency files

$(DEPDIR)/%.d : %.c
	@echo "DEP		$@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(CC) $(CFLAGS) -MM -MT $(OBJDIR)/$*.o -MF $@ $<

$(DEPDIR)/%.d : %.cc
	@echo "DEP		$@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(CXX) $(CXXFLAGS) -MM -MT $(OBJDIR)/$*.o -MF $@ $<

# --------------------------------------------------------------------------
# rules for generating object files

$(OBJDIR)/%.o : %.c
	@echo "CC		$@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o : %.cc
	@echo "CXX		$@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(CXX) -c $(CXXFLAGS) -o $@ $<

$(OBJDIR)/_%.o : %.asm
	@echo "ASM		$@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(ASM) -f $(ASMOBJFORMAT) -o $@ $<

# --------------------------------------------------------------------------
# linked system

$(OBJDIR)/system: $(FIRST_OBJECT) $(OBJPRE)
	@echo "LD		$@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(CXX) $(CXXFLAGS) -static -z max-page-size=0x1000 -e startup -T sections -o $(OBJDIR)/system $(FIRST_OBJECT) $(OBJPRE)

# --------------------------------------------------------------------------
# 'bootdisk.iso' consists of the system and a boot loader (GRUB) with boot
# block and setup code. The system gets started via Multiboot, so we don't
# have to care about switching to protected mode or how to deal with the BIOS.

$(OBJDIR)/bootdisk.iso : $(OBJDIR)/system
	@echo "BUILD		$@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) cp $< isofiles/boot/system
	$(VERBOSE) $(MKRESCUE) -o $@ isofiles

# --------------------------------------------------------------------------
# 'clean' deletes the generated system, the object files, and the dependency
# files.

clean:	
	@echo "RM		$(OBJDIR)"
	$(VERBOSE) rm -rf $(OBJDIR)
	@echo "RM		$(DEPDIR)"
	$(VERBOSE) rm -rf $(DEPDIR)

# --------------------------------------------------------------------------
# 'bootdisk' depends on bootdisk.iso, which in turn depends on the system. The
# ISO image gets written to the specified drive, which can be a HDD/SSD or an
# USB stick.
# ATTENTION: using the wrong device name here will destroy data on the specified
# device! Do not run with root privileges!

bootdisk: $(OBJDIR)/bootdisk.iso
	@echo "CP		$<"
	$(VERBOSE) cp $< $(DRIVE_HD)

# --------------------------------------------------------------------------
# 'qemu' runs the QEMU emulator with the system

qemu: $(OBJDIR)/bootdisk.iso
	$(QEMU) -drive file=build/bootdisk.iso,format=raw -k en-us

# --------------------------------------------------------------------------
# 'qemu-smp' runs QEMU in SMP (symmetric multi-processing) mode with 2 CPUs

qemu-smp: $(OBJDIR)/bootdisk.iso
	$(QEMU) -drive file=build/bootdisk.iso,format=raw -k en-us -smp 2

# --------------------------------------------------------------------------
# 'qemu-gdb' runs QEMU with an activated GDB stub, which waits for a debugger
# (GDB, DDD, CGDB, etc.) to connect before starting the system.

qemu-gdb: $(OBJDIR)/bootdisk.iso
	$(VERBOSE) echo "target remote localhost:$(shell echo $$(( $$(id -u) % (65536 - 1024) + 1024 )))" > /tmp/gdbcommands.$(shell id -u)
	$(QEMU) -drive file=build/bootdisk.iso,format=raw -k en-us -S -gdb tcp::$(shell echo $$(( $$(id -u) % (65536 - 1024) + 1024 )))

# --------------------------------------------------------------------------
# 'gdb' starts the GDB debugger and makes it connect to an already started
# 'qemu-gdb'.

gdb:
	gdb -x /tmp/gdbcommands.$(shell id -u) $(OBJDIR)/system

# --------------------------------------------------------------------------
# 'ddd': same as 'gdb' but uses the 'ddd' debugger

ddd:
	ddd --gdb -x /tmp/gdbcommands.$(shell id -u) $(OBJDIR)/system

# --------------------------------------------------------------------------
# 'cgdb': same as 'gdb' but uses the 'cgdb' debugger

cgdb:
	cgdb -x /tmp/gdbcommands.$(shell id -u) $(OBJDIR)/system

# --------------------------------------------------------------------------
# include dependency files

ifneq ($(MAKECMDGOALS),clean)
-include $(DEP_FILES)
endif

.PHONY: clean bootdisk gdb ddd qemu qemu-smp qemu-gdb qemu-ddd qemu-cgdb
