/* index.c - CS 50
implements a index_t type, which is a wrapper for hashtable,
and related functions to help the indexer.

Sixuan Han, April 28 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"


typedef struct index {
  hashtable_t* ht;
} index_t;

index_t* index_new() {
    index_t* index = mem_malloc(sizeof(index_t));
    index -> ht = hashtable_new(500);
}

void index_save();

void index_delete();
