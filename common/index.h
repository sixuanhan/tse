/* 
 * index.h - header file for CS50 'index' module
 * 
 * An 'index' is a wrapper for a hashtable that records the indices of word occurrences.
 *
 * Sixuan Han, April 29 2023
 */


#include <stdio.h>

/**************** global types ****************/
typedef struct index index_t;


/**************** functions ****************/
index_t* index_new();
void index_save(index_t* index, const char* word, int docID);
void index_write(index_t* index, const char* indexFilename);
void index_iterCtrs(void* arg, const char* word, void* item);
void index_writeCtrs(void* arg, const int docID, const int count);
void index_delete(index_t* index);
void index_helper_counters_delete(void* item);