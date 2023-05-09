# CS50 TSE Querier Implementation Spec
## Data structures
The `query` is inherently an array of strings consisting of normalized words, "and", and "or".
We also make use of the `index_t` type that we defined in `common`.

## Control flow
The Querier is implemented in one file `querier.c`, with ? functions.

### main
The `main` function first checks the validity of arguments, then calls `parseQuery` and `validateQuery` to check validity and create the final query. It calls `index_load` to load the index from `indexFilename` to an `index_t`, and eventually `searchIndex` to reads search the queries from stdin and `printRank` to rank and print the search result. Pseudocode:

    parse the command line, validate parameters, initialize other modules
    as long as we get a query
      call parseQuery
      end this query if we get an error in parseQuery or if the query is empty
      call validateQuery
      end this query if we get an error in validateQuery
      call index_load
      call searchIndex
      call printRank
      clean up

### parseQuery
The `parseQuery` clean and parse each query according to the syntax. It separates words into tokens, normalize all words. Pseudocode:

    go over the raw query
      if there is an illegal character
        report error, return -1
    creates a new array of strings
    parses the input into tokens according to space
    call word_normalize on the tokens

### validateQuery
The `validateQuery` function print the 'clean' query for user to see. Pseudocode:

    step through each token in the query
      the first token has to be a 'word' (not literal). If not, report error, return -1
      the first token has to be a 'word' (not literal). If not, report error, return -1
      if the token is a logical operator and `prev` is also a logical operator
        report error, return -1
      if the token is a word and `prev` is also a word
        add "and" in between `prev` and the current word
      record the current token as `prev`
      print out the final query

### searchIndex
The `searchIndex` function goes through the index, keeping track of the result as it goes, and prints the ranking as the result. Pseudocode:

    intialize a new counters `res` that keeps track of the current progress to NULL, like a dummy head
    pretend to add "NULL or" at the start of the query
    step through the operators in the query, starting at the "or" that we manually inserted
      if the next operator is "or"
        update `res` to the union
      if the next operator is "and"
        we identify the and-sequence
        we call `process_and_sequence`
        we merge the result of the and-sequence to the union
      move on to the next "or"

### printRank
The `printRank` function ranks the result counters according to the score in descending order and prints feedback to stdout. Pseudocode:

    iterate through the res counters once
      if we find no match at all
        print "No match found."
      else
        we keep iterate through the res counters
          we find the docID with the maximum score at this round
          if we can't find one with non-zero score
            break out of the loop
          else
            print out the score, docID, and url for this doc
            ignore this doc from now on


### other helper functions
I also have `countersAndMerge`, `countersAndMergeHelper`, `countersOrMerge`, `countersOrMergeHelper`, `process_and_sequence`, and `printRankHelper` in `querier.c`. They implement simple functions that are explained in DESIGN.md and in the paragraph comments in `querier.c`, so I will not go deep into their pseudocodes.


## Other modules
The following modules are located in tse-sixuanhan/common.
### pagedir
The `pagedir` module helps with creating pathnames, validating pageDirectory, and loading webpages.

### index
The `index` module implements functions to help reading words and docID into an `index_t` and writing the index to an output file.

### word
The `word` module implements one simple function that normalizes a word.

### libcs50
We leverage the modules of libcs50, most notably `hashtable`, `counters`, and `webpage`. See that directory for module interfaces.

### fuzzquery
The `fuzzquery` module generates random queries to help testing.


## Function prototypes
### querier
Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's implementation in `querier.c` and is not repeated here.

``` C
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
```

### pagedir
Please look at `pagedir.h` for detailed descriptions of usage and purpose.
``` C
char* pagedir_createDotCrawlerPath(const char* pageDirectory);
bool pagedir_init(const char* pageDirectory);
char* pagedir_createPagePath(const char* pageDirectory, const int docID);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
bool pagedir_validate(const char* pageDirectory);
webpage_t* pagedir_load(const char* pageDirectory, int docID);
```

### index
Please look at `index.h` for detailed descriptions of usage and purpose.
``` C
index_t* index_new();
void index_save(index_t* index, const char* word, int docID);
void index_direct_save(index_t* index, const char* word, int docID, int count);
void index_write(index_t* index, const char* indexFilename);
void index_iter_ctrs(void* arg, const char* word, void* item);
void index_write_ctrs(void* arg, const int docID, const int count);
void index_delete(index_t* index);
void index_helper_counters_delete(void* item);
```

### word
Please look at `word.h` for detailed descriptions of usage and purpose.
``` C
char* word_normalize(const char* word);
```


## Error handling and recovery


## Testing plan
We write a script `testing.sh` that invokes the querier several times, with a variety of command-line arguments. Run that script with `bash -v testing.sh` so the output of crawler is intermixed with the commands used to invoke the crawler. Verify correct behavior by studying the output, and by sampling the files created in the respective pageDirectories.
See `DESIGN.md`.