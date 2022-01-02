TARGET = kernel.elf
OBJS = main.o graphics.o font.o hankaku.o newlib_support.o
DEPENDS = $(join $(dir $(OBJS)),$(addprefix .,$(notdir $(OBJS:.o=.d))))

CGLAGS += -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone
CXXFLAGS += -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone \
			-fno-exceptions -fno-rtti -std=c++17
CPPFLAGS = -I$(HOME)/osbook/devenv/x86_64-elf/include/c++/v1 \
		   -I$(HOME)/osbook/devenv/x86_64-elf/include \
		   -I$(HOME)/osbook/devenv/x86_64-elf/include/freetype2 \
		   -I$(HOME)/edk2/MdePkg/Include \
		   -I$(HOME)/edk2/MdePkg/Include/X64 -nostdlibinc \
		   -D__ELF__ -D_LDBL_EQ_DBL -D_GNU_SOURCE -D_POSIX_TIMERS \
		   -DEFIAPI='__attribute__((ms_abi))'
LDFLAGS  += --entry KernelMain -z norelro --image-base 0x100000 --static \
		    -L$(HOME)/osbook/devenv/x86_64-elf/lib

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -rf *.o

kernel.elf: $(OBJS) Makefile
	ld.lld $(LDFLAGS) -o kernel.elf $(OBJS) -lc

%.o: %.cpp Makefile
	clang++ $(CPPFLAGS) $(CXXFLAGS) -c $<

%.d: %.cpp
	clang++ $(CPPFLAGS) $(CXXFLAGS) -MM $< > $@
	$(eval OBJ = $(<:.cpp=.o))
	sed --in-place 's|$(notdir $(OBJ))|$(OBJ)|' $@

%.o: %.c Makefile
	clang $(CPPFLAGS) $(CGLAGS) -c $<

%.d: %.c
	clang $(CPPFLAGS) $(CFLAGS) -MM $< > $@
	$(eval OBJ = $(<:.c=.o))
	sed --in-place 's|$(notdir $(OBJ))|$(OBJ)|' $@

hankaku.bin: hankaku.txt
	../tools/makefont.py -o $@ $<

hankaku.o: hankaku.bin
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 $< $@

.%.d: %.bin
	touch $@

.PHONY: depends
depends:
	$(MAKE) $(DEPENDS)

-include $(DEPENDS)
