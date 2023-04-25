/*
 * pagedir.h - header file for CS50 pagedir module
 * Sixuan Han, April 23 2023

*/

#include <stdio.h>
#include <stdbool.h>

/**************** functions ****************/
/*
initialize the .crawler file.

Return:
true if success; false if failure.
*/
bool pagedir_init(const char* pageDirectory);

/*
save a page to the pageDirectory with URL, depth, and HTML content.
*/
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);