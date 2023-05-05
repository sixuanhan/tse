/* 
 * indextest.c - CS50
 *
 * user interface: ./indextest oldIndexFilename newIndexFilename
 * function: reads the file produced by the TSE indexer, builds an index, and writes that index to a file again
 * 
 * Sixuan Han, April 25 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "counters.h"
#include "index.h"
#include "file.h"


int main(const int argc, char* argv[])
{
    // validate number of arguments
    if (argc != 3) {
        fprintf(stderr, "myError: wrong number of arguments.\n");
        exit(1);
    }

    char* oldIndexFilename = argv[1];
    char* newIndexFilename = argv[2];

    FILE* fp1 = fopen(oldIndexFilename, "r");
    if (fp1 == NULL) {
        fprintf(stderr, "myError: unable to open %s.\n", oldIndexFilename);
        exit(1);
    }

    index_t* myIndex = index_new();
    
    index_load(myIndex, fp1);

    fclose(fp1);

    index_write(myIndex, newIndexFilename);
    index_delete(myIndex);

    return 0;
}