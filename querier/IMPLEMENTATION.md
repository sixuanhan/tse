# CS50 TSE Querier Implementation Spec
## Data structures
The `query` is inherently an array of strings consisting of normalized words, "and", and "or".
We also make use of the `index_t` type that we defined in `common`.

## Control flow
The Querier is implemented in one file `querier.c`, with ? functions.

### main
The `main` function first checks the validity of arguments, then calls `index_load` to load the index from `indexFilename` to an `index_t`. It calls `parseQuery`, `printQuery`, and eventually `searchIndex` to reads search the queries from stdin and print the search result.

### parseQuery
The `parseQuery` clean and parse each query according to the syntax. It separates words into tokens, normalize all words.

### printQuery
The `printQuery` function print the 'clean' query for user to see.

### searchIndex
The `searchIndex` function goes through the index, keeping track of the result as it goes, and prints the ranking as the result.


## Other modules
The following modules are located in tse-sixuanhan/common.
### pagedir
We extend and modify `pagedir.c` to help with creating pathnames, validating pageDirectory, and loading webpages.

### index
The `index` module implements functions to help reading words and docID into an `index_t` and writing the index to an output file.

### word
The `word` module implements one simple function that normalizes a word.

### libcs50
We leverage the modules of libcs50, most notably `hashtable`, `counters`, and `webpage`. See that directory for module interfaces.

## Function prototypes
### indexer
Detailed descriptions of each function's interface is provided in `DESIGN.md` and is not repeated here.
``` C
static index_t* indexBuild(const char* pageDirectory);
static void indexPage(index_t* myIndex, webpage_t* page, int docID);
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
See `DESIGN.md`.