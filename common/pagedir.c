/* 
 * pagedir.c - CS50
 *
 * contains two functions that help initialize the pageDirectory and save webpage info to files in the pageDirectory
 * 
 * Sixuan Han, April 25 2023
 * 
 * 


NOTE FOR MYSELF:
no compilation errors.


 */


#include "webpage.h"
#include "mem.h"
#include "file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


/**************** prototypes ****************/
char* pagedir_createDotCrawlerPath(const char* pageDirectory);
bool pagedir_init(const char* pageDirectory);
bool pagedir_validate(const char* pageDirectory);
char* pagedir_createPagePath(const char* pageDirectory, const int docID);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
webpage_t* pagedir_load(const char* pageDirectory, int docID);



/**************** functions ****************/

/* the user is responsible for calling free() for fullPath if they use the function 
for other purposes than pagedir_init or pagedir_validate.
*/
char* pagedir_createDotCrawlerPath(const char* pageDirectory)
{
    char* append = "/.crawler";
    char* fullPath = mem_malloc_assert(strlen(pageDirectory) + strlen(append) + 1, "myError: memory allocation failed.\n");
    mem_assert(fullPath, "myError: pagedir_init failed.\n");

    strcpy(fullPath, pageDirectory);
    strcat(fullPath, append);

    return fullPath;
}


bool pagedir_init(const char* pageDirectory)
{
    char* fullPath = pagedir_createDotCrawlerPath(pageDirectory);
    
    FILE* fp;

    fp = fopen(fullPath, "w");
    if (fp == NULL) {
        return false;
    } else {
        fclose(fp);
    }

    mem_free(fullPath);
    return true;   
}


bool pagedir_validate(const char* pageDirectory)
{
    bool returnCode;
    char* fullPath = pagedir_createDotCrawlerPath(pageDirectory);
    // check if there is a .crawler file in pageDirectory 
    if (access(fullPath, F_OK) == 0) {
        returnCode = true;
    } else {
        returnCode = false;
    }
    mem_free(fullPath);
    return returnCode;
}


/* the user is responsible for calling free() for fullPath if they use the function 
for other purposes than pagedir_save.
*/
char* pagedir_createPagePath(const char* pageDirectory, const int docID)
{
    size_t length = strlen(pageDirectory) + sizeof(int) + 2;
    char* fullPath = mem_malloc_assert(length, "myError: memory allocation failed.\n");
    mem_assert(fullPath, "myError: pagedir_save failed.\n");

    snprintf(fullPath, length, "%s/%d", pageDirectory, docID);

    return fullPath;
}


void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID)
{
    char* fullPath = pagedir_createPagePath(pageDirectory, docID);
    
    FILE* fp;

    // write in info
    fp = fopen(fullPath, "w");
    fprintf(fp, "%s\n", webpage_getURL(page));
    fprintf(fp, "%d\n", webpage_getDepth(page));
    fprintf(fp, "%s\n", webpage_getHTML(page));
    
    fclose(fp);

    mem_free(fullPath);   
}


webpage_t* pagedir_load(const char* pageDirectory, int docID)
{
    char* fullPath = pagedir_createPagePath(pageDirectory, docID);
    FILE* fp = fopen(fullPath, "r");
    
    // if we reach the end of all files or if we can't open /1
    if (fp == NULL) {
        return NULL;
    }
    
    char* url = file_readLine(fp); // first line
    char* depthChar = file_readLine(fp); // second line
    int depth = atoi(depthChar);
    char* html = file_readFile(fp); // the rest of the file
    fclose(fp);

    webpage_t* page = webpage_new(url, depth, html);
    
    free(url);
    free(depthChar);
    free(html);

    mem_free(fullPath);   
    return page;
}