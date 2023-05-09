# CS50 TSE Querier
## Design Spec

The TSE *querier* is a program that reads the document files produced by the TSE crawler and the index file produced by the TSE indexer, and gives search result back to the user.

### User interface

The querier's only interface with the user is on the command-line; it must always have two arguments.

```
$ ./querier pageDirectory indexFilename
```

For example,

``` bash
$ ./querier ../data/letters ../data/letters.ndx
```

### Inputs and outputs

**Input**: the querier reads files in the pageDirectory produced by the crawler as well as the index file produced by the indexer.

**Output**: We save first print the clean query for the user to see; then
1. if the query is empty (no words), print nothing.
2. if no documents satisfy the query, print "No documents match."
3. otherwise, print the set of documents in decreasing rank order; for each, list the score, document ID and URL.
We output nothing to stdout other than what is indicated above.

### Functional decomposition into modules

We anticipate the following modules or functions:

 1. *main*, which parses arguments and initializes other modules;
 2. *parseQuery*, which cleans and parses each query according to the syntax. It separates words into tokens and normalizes all words. 
 3. *validateQuery*, which checks a parsed query for correct syntax. It eventually prints the clean query for the user to see.
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
 5. *fuzzquery*, a module providing a function to generate random queries.


### Pseudo code for logic/algorithmic flow

The querier will run as follows:

    parse the command line, validate parameters, initialize other modules
        as long as we get a query
          check if there contains illegal characters in the query
          tokenize the query
          check if the syntax is correct
          load index from indexFileName to an internal data structure
          calculate the result and scores of the query according to the index
          rank the result
          print the result
          clean up


Specifics of the aforemetioned functions can be found in the paragraph and in-line comments in the code. Pseudocode for other functions or modules can be found either in `IMPLEMENTATION.md` or they are explained earlier in crawler or indexer.


### Major data structures

The key data structure is the *query*, which is an array of normalized words.
The *index* is a *hashtable* keyed by *word* and storing *counters* as items.
The *counters* is keyed by *docID* and stores a count of the number of occurrences of that word in the document with that ID. 


### Testing plan
#### Integration/system testing
1. Test `querier` with various invalid arguments.
2. Test `querier` with various invalid queries.
3. Test `querier` with various valid queries with need of parsing and normalizing.
4. Test `querier` with various clean hard-coded queries in `test.txt`.
5. Test `querier` with `fuzzquery` on a variety of pageDirectories and indexFilename.
6. Run *valgrind* on both *querier* to ensure no memory leaks or errors.