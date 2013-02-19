CCDIR=~/opt/share/rpc8ecc/bin/
LIBDIR=~/opt/share/rpc8ecc/lib/
LD = $(CCDIR)ld65
AS = $(CCDIR)ca65
CC = $(CCDIR)cc65
AL = $(CCDIR)align

CINCLUDE = -Iinclude
CFLAGS = -t none --cpu $(CPU)
LFLAGS = -C $(LIBDIR)rpc8e.cfg
LLIBS  = $(LIBDIR)rpc8e.lib

#gonna leave this here for now
CPU = 65c02 


IMAGES = myprog.img memtest.img malloc-test.img elevator.img

.PHONY: all

all: $(IMAGES)

%.s: %.c
	$(CC) $(CFLAGS) $(CINCLUDE) $<

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
