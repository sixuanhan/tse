/* 
 * indexer.c - CS50
 *
 * user interface: ./querier pageDirectory indexFilename
 * function: reads the document files produced by the TSE crawler and the index file produced by the TSE indexer and prints query result
 * 
 * Sixuan Han, May 6 2023
 */

#define  _GNU_SOURCE
#include "webpage.h"
#include "pagedir.h"
#include "index.h"
#include "word.h"
#include "hashtable.h"
#include "counters.h"
#include "mem.h"
#include "file.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


/**************** prototypes ****************/
static int parseQuery(char* rawQuery, int bufferSize, char** cleanQuery);
static int validateQuery(char** cleanQuery, char** final, int numTokens);
static void countersAndMerge(counters_t* countersA, counters_t* countersB);
static void countersAndMergeHelper(void* arg, const int key, const int count);
static void countersOrMerge(counters_t* countersA, counters_t* countersB);
static void countersOrMergeHelper(void* arg, const int key, const int count);
static counters_t* searchIndex(index_t* myIndex, char** query, int querySize);
static counters_t* process_and_sequence(index_t* myIndex, char** query, int start, int end);
static void printRank(counters_t* res, char* pageDirectory);
static void printRankHelper(void* arg, const int key, const int count);



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
    // validate that indexFilename can be opened
    FILE* fp = fopen(indexFilename, "r");
    if (fp == NULL) {
        fprintf(stderr, "myError: invalid indexFilename.\n");
        exit(3);
    } else {
        fclose(fp);
    }


    printf("Query: ");
    char* rawQuery;
    while ((rawQuery = file_readLine(stdin)) != NULL) {
        // we limit the length of query to 100
        int bufferSize = 100;

        char** cleanQuery = mem_malloc_assert(sizeof(char*) * bufferSize, "myError: mem alloc for cleanQuery failed.");
        int numTokens = parseQuery(rawQuery, bufferSize, cleanQuery);

        if (numTokens == -1 || numTokens == 0) {
            continue;
        }

        char** finalQuery = mem_malloc_assert(sizeof(char*) * bufferSize, "myError: mem alloc for finalQuery failed.");

        int querySize = validateQuery(cleanQuery, finalQuery, numTokens);
        // query is invalid
        if (querySize == -1) {
            continue;
        }

        index_t* myIndex = index_new();
        fp = fopen(indexFilename, "r");
        index_load(myIndex, fp);
        fclose(fp);

        counters_t* res = searchIndex(myIndex, finalQuery, querySize);

        printRank(res, pageDirectory);
        printf("\n");

        // clean-ups
        for (int i = 0; i < numTokens; i++) {
            mem_free(cleanQuery[i]);
        }
        mem_free(cleanQuery);
        mem_free(finalQuery);

        counters_delete(res);
        index_delete(myIndex);
    }
 

    return 0;
}








/**************** functions ****************/

/* read line from stdin; validate that the raw query only consists of letters and spaces; tokenize and normalize the raw query;
 * store tokens into an array; print the clean query.
 * user needs to free the clean query afterwards.
 * returns -1 if something went wrong; otherwise return the number of tokens.
 */
static int parseQuery(char* rawQuery, int bufferSize, char** cleanQuery)
{
    // Check that query contains only letters and spaces
    for (int i = 0; i < strlen(rawQuery); i++) {
        if (!isalpha(rawQuery[i]) && !isspace(rawQuery[i])) {
            fprintf(stderr, "myError: Query contains non-letter/non-space character\n");
            return -1;
        }
    }

    // loop over the characters in rawQuery and tokenize it
    int numTokens = 0;
    char* wordStart = rawQuery;
    char* normalized;

    for (int i = 0; rawQuery[i] != '\0'; i++) {
        if (isspace(rawQuery[i])) { // found a space, end of word
            rawQuery[i] = '\0'; // replace space with null terminator
            if (wordStart != &rawQuery[i]) { // check if not consecutive spaces
                normalized = word_normalize(wordStart);
                cleanQuery[numTokens] = normalized;
                numTokens++;
            }
            wordStart = &rawQuery[i + 1]; // set wordStart to beginning of next word
        }
    }
    // add the last word to the array (if not consecutive spaces)
    if (strlen(wordStart) != 0) {
        normalized = word_normalize(wordStart);
        cleanQuery[numTokens] = normalized;
        numTokens++;
    }

    mem_free(rawQuery);

    printf("Clean query: ");
    for (int i = 0; i < numTokens; i++) {
        printf("%s ", cleanQuery[i]);
    }
    printf("\n");

    return numTokens;
}


/* takes the clean query and checks if it has syntax errors.
 * return -1 if anything goes wrong. return the size of the final query if everything is right.
 */
static int validateQuery(char** cleanQuery,  char** final, int numTokens)
{
    // j is the pointer to the position in finalQuery
    int j = 0;

    // use this bool to keep track of whether the previous token is a word (rather than an and/or)
    bool prevIsWord;

    // i is the pointer to the position in cleanQuery
    for (int i = 0; i < numTokens; i++) {
        // check first token
        if (i == 0) {
            if (strcmp(cleanQuery[i], "and") == 0 || strcmp(cleanQuery[i], "or") == 0) {
                fprintf(stderr, "myError: literals should not be first.\n");
                return -1;
            }
            else {
                prevIsWord = true;
            }
        } 

        else {
            // check last token
            if (i == numTokens-1 && (strcmp(cleanQuery[i], "and") == 0 || strcmp(cleanQuery[i], "or") == 0)) {
                fprintf(stderr, "myError: literals should not be last.\n");
                return -1;
            }

            bool thisIsWord = (strcmp(cleanQuery[i], "and") != 0 && strcmp(cleanQuery[i], "or") != 0);
            // this is a literal and prev is also a literal
            if (!thisIsWord && !prevIsWord) {
                fprintf(stderr, "myError: literals should not be adjacent.\n");
                return -1;
            }
            
            // this is a word and prev is also a word
            else if (thisIsWord && prevIsWord) {
                final[j++] = "and";
            }
            prevIsWord = thisIsWord;
        }

        final[j] = cleanQuery[i];
        j++;
    }

    // make up for the extra step we take at the end of the loop
    if (j > 0) {
        j--;
    }

    // uncomment this to see the final query (which adds the implicit "and"s)
    // printf("Final query: ");
    // for (int k = 0; k <= j; k++) {
    //     printf("%s ", final[k]);
    // }
    // printf("\n");

    // now j also stands for the length of the final query
    return j;
}


/* perform an AND merge between two counters
 * countersA will be modified
 */
static void countersAndMerge(counters_t* countersA, counters_t* countersB)
{
    counters_t* arr[2] = {countersA, countersB};
    counters_iterate(countersA, arr, countersAndMergeHelper);
}

static void countersAndMergeHelper(void* arg, const int key, const int count)
{
    counters_t** arr = (counters_t**) arg;
    counters_t* countersA = arr[0];
    counters_t* countersB = arr[1];

    // find the same key in countersB
    int countB = counters_get(countersB, key);
    counters_set(countersA, key, (count < countB) ? count : countB);
}


/* perform an OR merge between two counters
 * countersA will be modified
 */
static void countersOrMerge(counters_t* countersA, counters_t* countersB)
{
    counters_iterate(countersB, countersA, countersOrMergeHelper);
}

static void countersOrMergeHelper(void* arg, const int key, const int count)
{
    counters_t* countersA = arg;

    // find the same key in countersA
    int countA = counters_get(countersA, key);
    counters_set(countersA, key, countA+count);
}


/* calculate the result of a query
 * needs to delete the return afterwards

 * I use the double-pointer method.
 * Pointer i always point towards an "or" operator, and we have processed the query before the pointer;
 * Pointer j is always ahead of i, looking for the next "or" operator.
 * At the end of each loop, pointer i takes the position of j.
 */
static counters_t* searchIndex(index_t* myIndex, char** query, int querySize)
{
    counters_t* res = counters_new();
    // we pretend to add "NULL or" at the start of the query
    int i = -1;
    while (i < querySize) {
        int j = i+2;
        if ((j < querySize && strcmp(query[j], "or") == 0) || j >= querySize) {
            countersOrMerge(res, index_find(myIndex, query[i+1]));
        } else {
            // find the end of the and-sequence
            while (j < querySize && strcmp(query[j], "and") == 0) {
                j += 2;
            }
            counters_t* andResult = process_and_sequence(myIndex, query, i+1, j);
            countersOrMerge(res, andResult);
            counters_delete(andResult);
        }
        i = j;
    }

    return res;
}


/* calculate the result of and and-sequence from [start, end)
 * needs to delete the return afterwards
 */
static counters_t* process_and_sequence(index_t* myIndex, char** query, int start, int end)
{
    counters_t* andResult = counters_new();

    for (int i = start; i < end-2; i += 2) {
        // initialize andResult to the first counters
        if (i == start) {
            countersOrMerge(andResult, index_find(myIndex, query[i]));
        }
       countersAndMerge(andResult, index_find(myIndex, query[i+2]));
    }
    return andResult;
}



/* rank the result counters according to the score in descending order and print feedback to stdout
 */
static void printRank(counters_t* res, char* pageDirectory) {
        // currMax   currKey
    int arr[2] = {0, 0};

    // go through the counters at least once to see if there is at least one non-zero node
    counters_iterate(res, arr, printRankHelper);
    if (arr[1] == 0) {
        printf("No match found.\n");
    }

    // keep looping until all nodes have 0 count
    while (true) {
        counters_iterate(res, arr, printRankHelper);
        if (arr[1] == 0) {
            break;
        }

        // print the info of the current highest doc
        int docID = arr[1];
        int score = counters_get(res, arr[1]);
        char* path = pagedir_createPagePath(pageDirectory, docID);
        FILE* fp = fopen(path, "r");
        mem_free(path);
        char* url = file_readLine(fp);
        printf("score=%d, docID=%d, url=%s\n", score, docID, url);
        mem_free(url);
        fclose(fp);

        // ignore this doc from now on
        counters_set(res, arr[1], 0);

        arr[0] = 0;
        arr[1] = 0;
    }
    
}

static void printRankHelper(void* arg, const int key, const int count) {
    int* arr = arg;
    if (count > arr[0]) {
        arr[0] = count;
        arr[1] = key;
    }
}