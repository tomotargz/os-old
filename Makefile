TARGET = kernel.elf
OBJS = main.o

CXXFLAGS += -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone \
			-fno-exceptions -fno-rtti -std=c++17
CPPFLAGS = -I$(HOME)/osbook/devenv/x86_64-elf/include/c++/v1 \
		   -I$(HOME)/osbook/devenv/x86_64-elf/include \
		   -I$(HOME)/osbook/devenv/x86_64-elf/include/freetype2 \
		   -I$(HOME)/edk2/MdePkg/Include \
		   -I$(HOME)/edk2/MdePkg/Include/X64 -nostdlibinc \
		   -D__ELF__ -D_LDBL_EQ_DBL -D_GNU_SOURCE -D_POSIX_TIMERS \
		   -DEFIAPI='__attribute__((ms_abi))'
LDFLAGS  += --entry KernelMain -z norelro --image-base 0x100000 --static

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -rf *.o

kernel.elf: $(OBJS) Makefile
	ld.lld $(LDFLAGS) -o kernel.elf $(OBJS)

%.o: %.cpp Makefile
	clang++ $(CPPFLAGS) $(CXXFLAGS) -c $<
