/* 
 * indexer.c - CS50
 *
 * user interface: ./indexer pageDirectory indexFilename
 * function: reads the document files produced by the TSE crawler, builds an index, and writes that index to a file
 * 
 * Sixuan Han, April 25 2023
 * 
 * 
 * NOTE FOR MYSELF:
 * no compilation error.
 * 
 * 
 * 
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
static index_t* indexBuild(const char* pageDirectory);
static void indexPage(index_t* myIndex, webpage_t* page, int docID);


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

    index_t* myIndex = indexBuild(pageDirectory);
    index_write(myIndex, indexFilename);

    exit(0);
}


/**************** functions ****************/
//  builds an in-memory index from webpage files it finds in the pageDirectory
static index_t* indexBuild(const char* pageDirectory)
{
    index_t* myIndex = index_new();
    webpage_t* page;
    int docID = 1;
    while ((page = pagedir_load(pageDirectory, docID)) != NULL) {
        indexPage(myIndex, page, docID);
        docID++;
    }
    
    return myIndex;
}


// scans a webpage document to add its words to the index
static void indexPage(index_t* myIndex, webpage_t* page, int docID)
{
    int pos = 0;
    char* word;
    // loop through all words in the webpage
    while ((word = webpage_getNextWord(page, &pos)) != NULL){
        // skips trivial words (less than length 3)
        if (strlen(word) < 3) {
            mem_free(word);
            continue;
        }

        char* normalized = word_normalize(word);

        index_save(myIndex, normalized, docID);
    }
}