# Makefile for common
#
# Sixuan Han, April 24 2023

OBJS = pagedir.o
LIB = common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50
CC = gcc
MAKE = make

# Build $(LIB) by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
pagedir.o: pagedir.h

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o