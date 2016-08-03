
#CROSS_COMPILE = arm-linux-gnu-

CC = $(CROSS_COMPILE)gcc


DEBUG = -g -O0 -Wall

CFLAGS += $(DEBUG)

PROGS = ${patsubst %.c, %, ${wildcard *.c}} 

all : $(PROGS)

% : %.c
	$(CC)  $(CFLAGS)  $< -o $@

.PHONY: clean 

clean : 
		- rm -f $(PROGS) core *.gz

