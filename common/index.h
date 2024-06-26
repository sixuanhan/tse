/* 
 * index.h - header file for CS50 'index' module
 * 
 * An 'index' is a wrapper for a hashtable that records the indices of word occurrences.
 *
 * Sixuan Han, April 29 2023
 */

#include "counters.h"


/**************** global types ****************/
typedef struct index index_t;


/**************** functions ****************/
// to create a new index
index_t* index_new();

// to save a word occurrence in doc with docID to the index
void index_save(index_t* index, const char* word, int docID);

// to directly save a word: (docID, count) to the index
void index_direct_save(index_t* index, const char* word, int docID, int count);

// to write the info stored in the index to the output file
void index_write(index_t* index, const char* indexFilename);

// the helper function for hashtable_iterate in index_write
void index_iter_ctrs(void* arg, const char* word, void* item);

// the helper function for counters_iterate in index_iterCtrs
void index_write_ctrs(void* arg, const int docID, const int count);

// to delete everything in the index and the index itself
void index_delete(index_t* index);

// the helper function for hashtable_delete in index_delete
void index_helper_counters_delete(void* item);

// loads file input to an index
void index_load(index_t* index, FILE* fp);

// to get the counters that matches to a word (for querier)
counters_t* index_find(index_t* index, const char* word);
