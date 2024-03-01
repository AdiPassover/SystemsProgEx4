CC = gcc
AR = ar
CFL = -Wall -g
LFL = rcs
.PHONY: all clean

all: digitcompress

digitcompress: encodemain.o libCompress.a
    $(CC) $(CFL) $^ -o $@

encodemain.o: encodemain.c compress.h
    $(CC) $(CFL) -c $<

libCompress.a: compress.o
    $(AR) $(LFL) $@ $<

compress.o: compress.c compress.h
    $(CC) $(CFL) -c $<

clean:
    rm -f *.o *.a digitcompress