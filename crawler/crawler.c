/* 
 * crawler.c - CS50
 *
 * user interface: crawler seedURL pageDirectory maxDepth
 * function: crawls the web and download pages
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
#include <ctype.h>


/**************** prototypes ****************/
static int parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

static void logStatus(int depth, char* note, char* url);



int main(const int argc, char* argv[])
{
  // define parameters
  char* seedURL;
  char* pageDirectory;
  int maxDepth = 0;

  parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
 
  #ifdef MEMTEST
    mem_report(stdout, "End of parseArgs");
  #endif

  crawl(seedURL, pageDirectory, maxDepth);

  #ifdef MEMTEST
    mem_report(stdout, "End");
  #endif
  exit(0);
}

static int parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth)
{
  if (argc != 4) {
    fprintf(stderr, "myError: wrong number of arguments.\n");
    exit(1);
  }

  *seedURL = normalizeURL(argv[1]); 
  if (!(*seedURL) || !isInternalURL(*seedURL)) { 
    fprintf(stderr, "myError: invalid seed url.\n"); 
    exit(2); 
  } 

  *pageDirectory = argv[2];

  if (!pagedir_init(*pageDirectory)) {
    fprintf(stderr, "myError: initialize page failed.\n");
    exit(3);
  }

  *maxDepth = atoi(argv[3]);
  if (*maxDepth < 0 || *maxDepth > 10) {
    fprintf(stderr, "myError: maxDepth out of range.\n");
    exit(4);
  }

  return 0;
}


static void crawl(char* seedURL, char* pageDirectory, const int maxDepth)
{
  // hashtable
  const int slots = 200;
  hashtable_t* pagesSeen = hashtable_new(slots);
  mem_assert(pagesSeen, "myError: initialize hashtable failed.\n");

  hashtable_insert(pagesSeen, seedURL, "");

  // bag
  bag_t* pagesToCrawl = bag_new();
  mem_assert(pagesToCrawl, "myError: initialize hashtable failed.\n");


  webpage_t* page = webpage_new(seedURL, 0, NULL);
  bag_insert(pagesToCrawl, page);
  

  if (pagedir_init(pageDirectory)){
    webpage_t* webpage;
    int ID = 1; 
    while ((webpage = bag_extract(pagesToCrawl)) != NULL) {
      if (webpage_fetch(webpage)) {
        logStatus(webpage_getDepth(webpage), "Fetched", webpage_getURL(webpage));
        pagedir_save(webpage, pageDirectory, ID); 
        ID++;

        if (webpage_getDepth(webpage) < maxDepth) {
          logStatus(webpage_getDepth(webpage), "Scanning", webpage_getURL(webpage));
          pageScan(webpage, pagesToCrawl, pagesSeen);
        }
      }
      webpage_delete(webpage);
    }
    hashtable_delete(pagesSeen, NULL);
    bag_delete(pagesToCrawl, NULL);
  }
}

static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen)
{
  int pos = 0;
  char * nextURL;

  // loop through all urls in the webpage
  while ((nextURL = webpage_getNextURL(page, &pos)) != NULL){
    logStatus(webpage_getDepth(page), "Found", nextURL);
    char * normalized = normalizeURL(nextURL);
    if (isInternalURL(normalized)) {
      if (hashtable_insert(pagesSeen, normalized, "")) {
        webpage_t* newwebpage = webpage_new(normalized, webpage_getDepth(page)+1, NULL);
        bag_insert(pagesToCrawl, newwebpage);
        logStatus(webpage_getDepth(page), "Added", normalized);
      } 
      // have seen that page
      else {
        logStatus(webpage_getDepth(page), "IngDupl", normalized);
      }
    }
    // url is external
    else {
      logStatus(webpage_getDepth(page), "IgnExtrn", normalized);
    }
    #ifdef MEMTEST
      mem_report(stdout, "End of one pagescan");
    #endif
  }
}

/* prints out the status as the crawler crawls. format: depth note: url
*/
static void logStatus(int depth, char* note, char* url)
{
  #ifdef CRAWLERTEST
    printf("%-2d %-10s: %s\n", depth, note, url);
  #endif
}