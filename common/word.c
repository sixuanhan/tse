/* word.c - CS 50
implements normalizeWord to help the indexer.

Sixuan Han, April 28 2023



NOTE FOR MYSELF:
completed, not debugged.


*/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"

/* convert word to all lower case and return it
remember to mem_free the return and words
*/
char* word_normalize(const char* word) {
    size_t len = strlen(word);

    // Allocate a new string to hold the normalized word
    char* normalized = (char*) mem_malloc(len + 1);

    for (size_t i = 0; i < len; i++) {
        normalized[i] = tolower(word[i]);
    }

    normalized[len] = '\0';

    return normalized;
}
