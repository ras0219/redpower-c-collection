CCDIR=
#~/opt/share/rpc8ecc/bin/
LIBDIR=./lib/

LD = $(CCDIR)ld65
AS = $(CCDIR)ca65
CC = $(CCDIR)cl65
AL = $(CCDIR)align

KEEP_ASS = True

CINCLUDE = -Iinclude
CPU = 65c02 # 65816
CFLAGS = -t none --cpu $(CPU)
LFLAGS = -C $(LIBDIR)rpc8e.cfg
LLIBS  = $(LIBDIR)rpc8e.lib

#gonna leave this here for now


IMAGES = myprog.img memtest.img malloc-test.img elevator.img

.PHONY: all

all: lib $(IMAGES)

%.s: %.c
	$(CC) -S $(CFLAGS) $(CINCLUDE) $<
ifdef KEEP_ASS
	cp $@ s.$@
endif

%.o: %.c
	$(CC) -c $(CFLAGS) $(CINCLUDE) $<


%.img: %.o core.o buddy.o
	$(LD) $(LFLAGS) $< core.o buddy.o $(LLIBS) -o $@
	$(AL) $@


clean:
	rm  *.o *.s

depends:
	makedepend -Yinclude/ *.c

.PHONY: lib

lib:
	make -C lib

.SUFFIXES:
# DO NOT DELETE

buddy.o: include/stdint.h buddy.h include/stdlib.h
core.o: core.h include/redbus.h include/console.h include/string.h
core.o: include/stddef.h include/stdint.h buddy.h include/stdlib.h
elevator.o: elevator.h include/redbus.h core.h include/console.h
elevator.o: include/string.h include/stddef.h include/stdint.h buddy.h
elevator.o: include/stdlib.h include/iox.h include/cpu.h
malloc-test.o: core.h include/redbus.h include/console.h include/string.h
malloc-test.o: include/stddef.h include/stdint.h buddy.h include/stdlib.h
memtest.o: core.h include/redbus.h include/console.h include/string.h
memtest.o: include/stddef.h include/stdint.h buddy.h include/stdlib.h
myprog.o: core.h include/redbus.h include/console.h include/string.h
myprog.o: include/stddef.h include/stdint.h buddy.h include/stdlib.h
