/* 
 * indexer.c - CS50
 *
 * user interface: ./indexer pageDirectory indexFilename
 * function: reads the document files produced by the TSE crawler, builds an index, and writes that index to a file
 * 
 * Sixuan Han, April 25 2023
 */

#include "webpage.h"
#include "pagedir.h"
#include "hashtable.h"
#include "bag.h"
#include "mem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**************** prototypes ****************/


int main(const int argc, char* argv[])
{
    char* pageDirectory;
    char* indexFilename;

    // validate number of arguments
    if (argc != 3) {
        fprintf(stderr, "myError: wrong number of arguments.\n");
        exit(1);
    }

    *pageDirectory = argv[1];
    // validate that pageDirectory is the pathname for a directory produced by the Crawler
    if (!pagedir_validate(pageDirectory)) {
        fprintf(stderr, "myError: invalid pageDirectory.\n");
        exit(2);
    }

    *indexFilename = argv[2];
    // validate that indexFilename is the pathname of a file that can be written
    FILE* fp = fopen(indexFilename, "w");
    if (fp == NULL) {
        fprintf(stderr, "myError: invalid indexFilename.\n");
        exit(3);
    } else {
        fclose(fp);
    }



    return 0;
}

