
#CROSSCOMPILE=/opt/gcc-linaro-2013.03/bin/arm-linux-gnueabihf-
#CROSSCOMPILE=/opt/arm-2014.05/bin/arm-none-linux-gnueabi-
CC=$(CROSSCOMPILE)gcc
CXX=$(CROSSCOMPILE)g++
STRIP=$(CROSSCOMPILE)strip
AR=$(CROSSCOMPILE)ar

OBJS=main.o 
LIBOBJS=linklist_text.o
LIBCANPROTO=liblinklist_text.a
EXEC=ctest
CFLAGS += -g -Wall -O2 -D_GNU_SOURCE

.PHONY:tags
all:$(EXEC)
	$(STRIP) -s $(EXEC) -o $(EXEC).strip
#	cp $(EXEC) /tftpboot/filesys-firecbox/home/. -f

$(EXEC):$(OBJS) $(LIBCANPROTO)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS) -lpthread 

$(LIBCANPROTO):$(LIBOBJS)
	$(AR) rc $@ $^

clean:
	rm $(OBJS) $(EXEC) $(EXEC).strip $(LIBOBJS)  $(LIBCANPROTO) -f

tags:
	ctags *.[ch] *.cpp
