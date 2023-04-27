Turn on the CRAWLERTEST in makefile to view detailed crawler logging.
Turn on the MEMTEST in makefile to view detailed memory logging.

The test will not erase data after a run, since we probably need the downloaded files for the indexer and querier.
I implemented the test in a way that it erases data at the start of a new run.