# Makefile for crawler
#
# Sixuan Han, April 24 2023

C = ../common
L = ../libcs50

CC = gcc
MAKE = make

# uncomment the following to turn on verbose memory logging
# TESTINGM=-DMEMTEST

# uncomment the following to turn on verbose crawler logging
# TESTINGC=-DCRAWLERTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTINGM) $(TESTINGC) -I$C -I$L
OBJS = crawler.o
LIB = -lm
LLIBS = $C/common.a $L/libcs50-given.a

.PHONY: all clean

all: crawler

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

# building the executable
crawler: $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) $(LIBS) -o $@


crawler.o: $L/webpage.h $C/pagedir.h $L/hashtable.h $L/bag.h $L/mem.h



test: testing.sh
	./testing.sh

clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f crawler
	rm -f core
