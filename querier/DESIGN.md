# CS50 TSE Querier
## Design Spec

According to the [Indexer Requirements Spec](REQUIREMENTS.md), the TSE *querier* is a program that reads the document files produced by the TSE crawler and the index file produced by the TSE indexer, and gives search result back to the user.

### User interface

The querier's only interface with the user is on the command-line; it must always have two arguments.

```
$ ./querier pageDirectory indexFilename
```

For example,

``` bash
$ indexer ../data/letters ../data/letters.ndx
```

### Inputs and outputs

**Input**: the querier reads files in the pageDirectory produced by the crawler as well as the index file produced by the indexer.

**Output**: We save first print the clean query for the user to see; then
1. if the query is empty (no words), print nothing.
2. if no documents satisfy the query, print `No documents match`.
3. otherwise, print the set of documents in decreasing rank order; for each, list the score, document ID and URL.
We output nothing to stdout other than what is indicated above.

### Functional decomposition into modules

We anticipate the following modules or functions:

 1. *main*, which parses arguments and initializes other modules;
 2. *parseQuery*, which cleans and parses each query according to the syntax. It separates words into tokens and normalizes all words. It eventually prints the clean query for the user to see.
 3. *validateQuery*, which checks a parsed query for correct syntax.
 4. *searchIndex*, which goes through the index, keeping track of the result as it goes, and prints the ranking as the result.
 5. *process_and_sequence*, the helper function of *searchIndex*, which calculate the result of and and-sequence.
 6. *countersOrMerge* (and its helper function), which merges two counters with OR logic (looks for identical keys in two counters and taking the sum of values as the new value).
 7. *countersAndMerge* (and its helper function), which merges two counters with AND logic (looks for identical keys in two counters and taking the minimum value as the new value).
 9. *printRank* (and its helper function), which ranks the result from the query and prints to the user.

And some helper modules that provide data structures:

 1. *index*, a module providing the data structure to represent the in-memory index, and functions to read and write index files;
 2. *webpage*, a module providing the data structure to represent webpages, and to scan a webpage for words;
 3. *pagedir*, a module providing functions to load webpages from files in the pageDirectory;
 4. *word*, a module providing a function to normalize a word.

### Pseudo code for logic/algorithmic flow

The querier will run as follows:

    parse the command line, validate parameters, initialize other modules
    call parseQuery
    call validateQuery
    call printQuery
    call searchIndex

where *parseQuery:*

      creates a new array of strings
      parses the input into tokens according to space
      loop over all tokens
        if the token contains non-alphabetic characters
          exit with non-zero and report error
        call word_normalize on the token

where *validateQuery:*

    the first and last tokens have to be 'words' (not logical operators)
    record the current token as `prev`
    steps through each token in the query
      if the token is a logical operator
        if `prev` is also a logical operator
          exit with non-zero and report error
      else (if the token is a word)
        if `prev` is also a word
          add "and" in between `prev` and the current word
      record the current token as `prev`

where *printQuery:*

    loop over each token
      print the token

where *searchIndex:*

    if the query is empty
      we're done
    else
      call index_load
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
        



       

### Major data structures

The key data structure is the *query*, which is an array of normalized words.
The *index* is a *hashtable* keyed by *word* and storing *counters* as items.
The *counters* is keyed by *docID* and stores a count of the number of occurrences of that word in the document with that ID. 

### Testing plan

*Unit testing*.  A program *indextest* will serve as a unit test for the *index* module; it reads an index file into the internal *index* data structure, then writes the index out to a new index file.

*Integration testing*.  The *indexer*, as a complete program, will be tested by building an index from a pageDirectory, and then the resulting index will be validated by running it through the *indextest* to ensure it can be loaded.

1. Test `querier` with various invalid arguments.

0. Run *querier* on a variety of pageDirectories and indexFilename as one means of validating the resulting index.
0. Run *valgrind* on both *querier* to ensure no memory leaks or errors.