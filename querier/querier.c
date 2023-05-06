/* 
 * indexer.c - CS50
 *
 * user interface: ./querier pageDirectory indexFilename
 * function: reads the document files produced by the TSE crawler and the index file produced by the TSE indexer and prints query result
 * 
 * Sixuan Han, May 6 2023
 */

#include "webpage.h"
#include "pagedir.h"
#include "index.h"
#include "word.h"
#include "hashtable.h"
#include "counters.h"
#include "mem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**************** prototypes ****************/
static void countersAndMerge(counters_t* countersA, counters_t* countersB);
static void countersAndMergeHelper(void* arg, const int key, const int count);
static void countersOrMerge(counters_t* countersA, counters_t* countersB);
static void countersOrMergeHelper(void* arg, const int key, const int count);




/**************** main ****************/
int main(const int argc, char* argv[])
{
    char* pageDirectory;
    char* indexFilename;

    // validate number of arguments
    if (argc != 3) {
        fprintf(stderr, "myError: wrong number of arguments.\n");
        exit(1);
    }

    pageDirectory = argv[1];
    // validate that pageDirectory is the pathname for a directory produced by the Crawler
    if (!pagedir_validate(pageDirectory)) {
        fprintf(stderr, "myError: invalid pageDirectory.\n");
        exit(2);
    }

    indexFilename = argv[2];
    // validate that indexFilename is the pathname of a file that can be written
    FILE* fp = fopen(indexFilename, "w");
    if (fp == NULL) {
        fprintf(stderr, "myError: invalid indexFilename.\n");
        exit(3);
    } else {
        fclose(fp);
    }

    counters_t* ctrs1 = counters_new();
    counters_set(ctrs1, 1, 1);
    counters_set(ctrs1, 2, 2);
    counters_set(ctrs1, 3, 3);

    counters_t* ctrs2 = counters_new();
    counters_set(ctrs2, 1, 3);
    counters_set(ctrs2, 2, 1);
    counters_set(ctrs2, 4, 1);

    counters_t* res = counters_new();
    countersOrMerge(res, ctrs1);
    countersOrMerge(res, ctrs2);
    counters_print(res, stdout);
    free(res);

    counters_t* res = counters_new();
    countersOrMerge(res, ctrs1);
    countersAndMerge(res, ctrs2);
    counters_print(res, stdout);
    free(res);    

    return 0;
}




/**************** functions ****************/

/* perform an AND merge between two counters
 * countersA will be modified
 */
static void countersAndMerge(counters_t* countersA, counters_t* countersB)
{
    counters_iterate(countersB, countHelper);
}

static void countersAndMergeHelper(void* arg, const int key, const int count)
{
    counters_t* countersA = arg;

    // find the same key in countersA
    int countA = counters_get(countersA, key);
    if (countA != 0) {
        // use the minimum of the count in countersA and countersB
        if (countA >= count) {
            counters_set(countersA, key, count);
        } else {
            counters_set(countersA, key, countA);
        }     
    }
}


/* perform an OR merge between two counters
 * countersA will be modified
 */
static void countersOrMerge(counters_t* countersA, counters_t* countersB)
{
    counters_iterate(countersB, countersOrMergeHelper);
}

static void countersOrMergeHelper(void* arg, const int key, const int count)
{
    counters_t* countersA = arg;

    // find the same key in countersA
    int countA = counters_get(countersA, key);
    counters_set(countersA, key, countA+count);
}