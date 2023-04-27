/*
 * pagedir.h - header file for CS50 pagedir module
 * Sixuan Han, April 23 2023

*/

#include <stdio.h>
#include <stdbool.h>

/**************** functions ****************/

/* creates a .crawler path

Return:
char* fullPath;
*/
char* pagedir_createDotCrawlerPath(const char* pageDirectory);


/*
initialize the .crawler file.

Return:
true if success; false if failure.
*/
bool pagedir_init(const char* pageDirectory);


/* creates a path for a download page

Return:
char* fullPath;
*/
char* pagedir_createPagePath(const char* pageDirectory, const int docID);


/*
save a page to the pageDirectory with URL, depth, and HTML content.
*/
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);


/*
for indexer
check if there is a .crawler file in pageDirectory.

Return:
true if there is; false if there is not.
*/
bool pagedir_validate(const char* pageDirectory);



/*
for indexer
load a webpage given pageDirectory and docID.

Return:
webpage_t* page or NULL if unsuccessful.
*/
webpage_t* pagedir_load(const char* pageDirectory, int docID);