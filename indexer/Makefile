# Makefile for indexer
#
# Sixuan Han, April 29 2023

C = ../common
L = ../libcs50

CC = gcc
MAKE = make

# uncomment the following to turn on verbose memory logging
 TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$C -I$L
OBJS = indexer.o indexertest.o
LIB = -lm
LLIBS = $C/common.a $L/libcs50-given.a

.PHONY: all clean

all: indexer indextest

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

# building the executables
indexer: indexer.o $(LLIBS)
	$(CC) $(CFLAGS) indexer.o $(LLIBS) $(LIBS) -o $@

indexer.o: $L/webpage.h $C/pagedir.h $C/index.h $C/word.h $L/hashtable.h $L/counters.h $L/mem.h

indextest: indextest.o $(LLIBS)
	$(CC) $(CFLAGS) indextest.o $(LLIBS) $(LIBS) -o $@

indextest.o: $L/webpage.h $C/pagedir.h $L/hashtable.h $L/counters.h $L/mem.h


test: testing.sh
	./testing.sh

clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f indexer
	rm -f indextest
	rm -f core
