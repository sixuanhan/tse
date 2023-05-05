# Makefile for common
#
# Sixuan Han, April 29 2023

OBJS = pagedir.o index.o word.o
LIB = common.a
L = ../libcs50

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L
CC = gcc
MAKE = make

# Build $(LIB) by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
pagedir.o: pagedir.h
index.o: index.h $L/hashtable.h $L/counters.h $L/mem.h $L/file.h
word.o: word.h $L/mem.h

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o