/* index.c - CS 50
implements a index_t type, which is a wrapper for hashtable,
and related functions to help the indexer.

Sixuan Han, April 28 2023



NOTE FOR MYSELF:
completed, need to debug.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "counters.h"


typedef struct index {
  hashtable_t* ht;
} index_t;


// to create a new index
index_t* index_new() {
  index_t* index = mem_malloc(sizeof(index_t));
  index -> ht = hashtable_new(200);
}


// to save a word occurrence in doc with docID to the index
void index_save(index_t* index, const char* word, int docID)
{
  // insert to the hashtable if we have not seen the word, or else
  counters_t* newctrs = counters_new();
  if (!hashtable_insert(index -> ht, word, newctrs)) {
    mem_free(newctrs);
    // add to counters
    counters_t* ctrs = hashtable_find(index -> ht, word);
    counters_add(ctrs, docID);
  }
}


// to write the info stored in the index to the output file
void index_write(index_t* index, const char* indexFilename)
{
  FILE* fp = fopen(indexFilename);
  hashtable_iterate(index -> ht, fp, index_iterCtrs);
  fclose(indexFilename);
}


// the helper function for hashtable_iterate in index_write
void index_iterCtrs(FILE* fp, const char* word, counters_t* ctrs)
{
  fprintf(fp, "%s ", word);
  counters_iterate(ctrs, indexFilename, index_writeCtrs);
  fprintf(fp, "\n");
}

// the helper function for counters_iterate in index_iterCtrs

void index_writeCtrs(FILE* fp, const int docID, const int count)
{
  fprintf(fp, "%d %d ", word, count);
}


// to delete everything in the index and the index itself
void index_delete(index_t* index)
{
  hashtable_delete(index -> ht, counters_delete);
  mem_free(index);
}
