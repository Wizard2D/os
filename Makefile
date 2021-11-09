KERNEL := kernel.elf

CC ?= cc
LD ?= ld

CFLAGS  ?= -Wall -Wextra -O2 -pipe
LDFLAGS ?=

INTERNALLDFLAGS :=         \
	-Tlinker.ld            \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static                \
	-pie                   \
	--no-dynamic-linker    \
	-ztext

INTERNALCFLAGS :=        \
	-I.                  \
	-std=gnu11           \
	-ffreestanding       \
	-fno-stack-protector \
	-fpie                \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-ggdb				 \
	-mno-sse             \
	-mno-sse2            \
	-mno-red-zone        \
	-MMD

CFILES      := $(shell find ./ -type f -name '*.c')
ASMOBJS := $(wildcard *.asm)
OBJ         := $(CFILES:.c=.o) $(ASMOBJS:.asm=.o)
HEADER_DEPS := $(CFILES:.c=.d)

.PHONY: all
all: $(KERNEL)

stivale2.h:
	curl https://raw.githubusercontent.com/stivale/stivale/master/stivale2.h -o $@

$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@

-include $(HEADER_DEPS)

%.o: %.c stivale2.h
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.asm
	nasm -felf64 $< -o $@

.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)

.PHONY: distclean
distclean: clean
	rm -f stivale2.h
