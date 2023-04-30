# CS50 TSE Indexer Implementation Spec
## Data structures
The `index` is inherently a hashtable with `char* word` as the key and `counters*` as the item; each `counter` has `docID` as the key and the number of occurrence as the item.

## Control flow
The Indexer is implemented in one file `indexer.c`, with ? functions.

### main
The `main` function first checks the validity of arguments,then calls `indexBuild`, with `pageDirectory`. It eventually calls `index_write` to write the index to the output file.

### indexBuild
The `main` function loops over documents in the `pageDirectory` and passes the `webpage` and `docID` to `indexPage`.

### indexPage
The `indexPage` function loops over words and records occurrences with the help of `index_save`.


## Other modules
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
The indexer checks the number of arguments that it takes, that `pageDirectory` is the pathname for a directory produced by the Crawler, and that `indexFilename` is the pathname of a file that can be written.
When allocating memories, the indexer and related modules use `mem_malloc_assert()` to defend against unsuccessful memory allocation.

## Testing plan
See `DESIGN.md`.