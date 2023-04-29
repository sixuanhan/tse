/* 
 * word.h - header file for CS50 'word' module
 * 
 * The module normalizes words to lower case.
 *
 * Sixuan Han, April 29 2023
 */


/* convert word to all lower case and return it.
The user is responsible for calling mem_free() to the return and words
*/
char* word_normalize(const char* word);