
#CROSS_COMPILE = arm-linux-gnu-

CC = $(CROSS_COMPILE)gcc

ifdef CROSS_COMPILE
	TARGET = /opt/filesystem
endif

DEBUG = -g -O0 -Wall

CFLAGS += $(DEBUG)

PROGS = ${patsubst %.c, %, ${wildcard *.c}} 

all : $(PROGS)

% : %.c
	$(CC)  $(CFLAGS)  $< -o $@

.PHONY: clean 

clean : 
		- rm -f $(PROGS) core *.gz

