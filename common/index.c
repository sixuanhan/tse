/* index.c - CS 50
implements a index_t type, which is a wrapper for hashtable,
and related functions to help the indexer.

Sixuan Han, April 28 2023

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "counters.h"
#include "mem.h"
#include "file.h"


/**************** global types ****************/
typedef struct index {
  hashtable_t* ht;
} index_t;


/**************** prototypes ****************/
index_t* index_new();
void index_save(index_t* index, const char* word, int docID);
void index_direct_save(index_t* index, const char* word, int docID, int count);
void index_write(index_t* index, const char* indexFilename);
void index_iter_ctrs(void* arg, const char* word, void* item);
void index_write_ctrs(void* arg, const int docID, const int count);
void index_delete(index_t* index);
void index_helper_counters_delete(void* item);
void index_load(index_t* index, FILE* fp);


/**************** functions ****************/

index_t* index_new()
{
  index_t* index = mem_malloc_assert(sizeof(index_t), "myError: index initialization failed.\n");
  index -> ht = hashtable_new(200);
  return index;
}


void index_save(index_t* index, const char* word, int docID)
{
  // insert to the hashtable if we have not seen the word, or else
  counters_t* ctrs = hashtable_find(index -> ht, word);
  if (ctrs == NULL) {
    ctrs = counters_new();
    counters_add(ctrs, docID);
    hashtable_insert(index -> ht, word, ctrs);
  }

  else {
    counters_add(ctrs, docID);
  }
}


void index_direct_save(index_t* index, const char* word, int docID, int count)
{
  // insert to the hashtable if we have not seen the word, or else
  counters_t* ctrs = hashtable_find(index -> ht, word);
  if (ctrs == NULL) {
    ctrs = counters_new();
    counters_add(ctrs, docID);
    counters_set(ctrs, docID, count);
    hashtable_insert(index -> ht, word, ctrs);
  }

  else {
    counters_add(ctrs, docID);
    counters_set(ctrs, docID, count);
  }
}



void index_write(index_t* index, const char* indexFilename)
{
  FILE* fp = fopen(indexFilename, "w");
  hashtable_iterate(index -> ht, fp, index_iter_ctrs);
  fclose(fp);
}


void index_iter_ctrs(void* arg, const char* word, void* item)
{
  FILE* fp = arg;
  fprintf(fp, "%s ", word);

  counters_t* ctrs = item;
  counters_iterate(ctrs, fp, index_write_ctrs);
  fprintf(fp, "\n");
}


void index_write_ctrs(void* arg, const int docID, const int count)
{
  FILE* fp = arg;
  fprintf(fp, "%d %d ", docID, count);
}


void index_delete(index_t* index)
{
  hashtable_delete(index -> ht, index_helper_counters_delete);
  mem_free(index);
}


void index_helper_counters_delete(void* item)
{
  counters_t* ctrs = item;
  counters_delete(ctrs);
}


void index_load(index_t* index, FILE* fp)
{
  // reads the word and the pairs
  char* word;
  while ((word = file_readWord(fp)) != NULL) {
    int docID;
    int count;

    while (fscanf(fp, "%d %d", &docID, &count) == 2) {
      // store them into the index
      index_direct_save(index, word, docID, count);
    }
    free(word);
  }
}