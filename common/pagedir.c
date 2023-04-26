/* 
 * pagedir.c - CS50
 *
 * contains two functions that help initialize the pageDirectory and save webpage info to files in the pageDirectory
 * 
 * Sixuan Han, April 15 2023
 */


#include "webpage.h"
#include "mem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


bool pagedir_init(const char* pageDirectory)
{
    char* append = "/.crawler";
    char* fullPath = mem_malloc(strlen(pageDirectory) + strlen(append) + 1);
    mem_assert(fullPath, "myError: pagedir_init failed.\n");

    strcpy(fullPath, pageDirectory);
    strcat(fullPath, append);
    
    FILE* fp;

    fp = fopen(fullPath, "w");
    if (fp == NULL) {
        return false;
    } else {
        fclose(fp);
    }

    free(fullPath);
    return true;   
}


void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID)
{
    size_t length = strlen(pageDirectory) + sizeof(int) + 2;
    char* fullPath = mem_malloc(length);
    mem_assert(fullPath, "myError: pagedir_save failed.\n");

    snprintf(fullPath, length, "%s/%d", pageDirectory, docID);
    
    FILE* fp;

    fp = fopen(fullPath, "w");
    fprintf(fp, "%d\n", webpage_getDepth(page));
    fprintf(fp, "%s\n", webpage_getURL(page));
    fprintf(fp, "%s\n", webpage_getHTML(page));
    
    fclose(fp);

    free(fullPath);   
}