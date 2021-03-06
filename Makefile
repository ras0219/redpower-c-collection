CCDIR=~/opt/share/rpc8ecc/bin/
LIBDIR=./lib/

LD = $(CCDIR)ld65
AS = $(CCDIR)ca65
CC = $(CCDIR)cc65
AL = $(CCDIR)align

KEEP_ASS = True

CPU = 65816 
CINCLUDE = -Iinclude
CFLAGS = -t none --cpu $(CPU)
LFLAGS = -C $(LIBDIR)rpc8e.cfg
LLIBS  = $(LIBDIR)rpc8e.lib

#gonna leave this here for now

IMAGES = myprog.img memtest.img malloc-test.img elevator.img forloop-fail.img uu-matter.img

.PHONY: all

all: $(IMAGES)

%.s: %.c
	$(CC) $(CFLAGS) $(CINCLUDE) $<
ifdef KEEP_ASS
	cp $@ s.$@
endif

%.o: %.s
	$(AS) $(CFLAGS) $<


%.img: %.o core.o buddy.o
	$(LD) $(LFLAGS) $< core.o buddy.o $(LLIBS) -o $@
	$(AL) $@


clean:
	rm  *.o *.s

depends:
	makedepend -Yinclude/ *.c

.SUFFIXES:
# DO NOT DELETE

elevator.o: elevator.h include/redbus.h include/iox.h
elevator.o: include/stddef.h include/stdint.h
core.o: core.h include/redbus.h include/console.h include/string.h
core.o: include/stddef.h include/stdint.h
malloc-test.o: core.h include/redbus.h include/console.h include/string.h
malloc-test.o: include/stddef.h include/stdint.h
memtest.o: core.h include/redbus.h include/console.h include/string.h
memtest.o: include/stddef.h include/stdint.h
myprog.o: core.h include/redbus.h include/console.h include/string.h
myprog.o: include/stddef.h include/stdint.h
