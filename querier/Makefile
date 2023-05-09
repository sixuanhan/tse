# Makefile for indexer
#
# Sixuan Han, April 29 2023

C = ../common
L = ../libcs50

CC = gcc
MAKE = make

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$C -I$L
OBJS = querier.o
LIB = -lm
LLIBS = $C/common.a $L/libcs50-given.a

.PHONY: all clean

all: querier fuzzquery

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

# building the executables
querier: querier.o $(LLIBS)
	$(CC) $(CFLAGS) querier.o $(LLIBS) $(LIBS) -o $@

fuzzquery: fuzzquery.o $(LLIBS)
	$(CC) $(CFLAGS) fuzzquery.o $(LLIBS) $(LIBS) -o $@
	
querier.o: $L/webpage.h $C/pagedir.h $C/index.h $C/word.h $L/hashtable.h $L/counters.h $L/file.h $L/mem.h
fuzzquery.o: $L/mem.h $L/file.h

test: testing.sh
	bash -v testing.sh >& testing.out

clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f querier
	rm -f fuzzquery
	rm -f core
