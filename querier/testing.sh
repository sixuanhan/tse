# testing for querier
# Author: Sixuan Han
# Date: May 7 2023


# edge cases for incorrect args
#testing: zero argument
./querier


#testing: one argument
./querier ../../shared/tse/crawldata/toscrape-1


#testing: three arguments
./querier ../../shared/tse/crawldata/letters-1/ output.ndx outputNew.ndx


#testing: invalid pageDirectory (non-existent path)
./querier invalid ../../shared/tse/indices/toscrape-1.ndx


#testing: invalid pageDirectory (not a crawler directory)
./querier ../crawler ../../shared/tse/indices/toscrape-1.ndx


#testing: invalid indexFile (non-existent path)
./querier ../../shared/tse/crawldata/toscrape-1 ../invalid/output.ndx


#testing: invalid indexFile (can't read file)
touch invalid.ndx
chmod -r invalid.ndx
./querier ../../shared/tse/crawldata/toscrape-1/ invalid.ndx
rm -f invalid.ndx



# edge cases for invalid queries
#testing: start with literal
./querier ../../shared/tse/crawldata/toscrape-1 ../../shared/tse/indices/toscrape-1.ndx


#testing: end with literal
./querier ../../shared/tse/crawldata/toscrape-1 ../../shared/tse/indices/toscrape-1.ndx


#testing: adjacent literals
./querier ../../shared/tse/crawldata/toscrape-1 ../../shared/tse/indices/toscrape-1.ndx


#testing: invisible "and"
./querier ../../shared/tse/crawldata/toscrape-1 ../../shared/tse/indices/toscrape-1.ndx


#testing: bad characters
./querier ../../shared/tse/crawldata/toscrape-1 ../../shared/tse/indices/toscrape-1.ndx


#testing: empty query
./querier ../../shared/tse/crawldata/toscrape-1 ../../shared/tse/indices/toscrape-1.ndx


#testing: successful
./querier ../../shared/tse/crawldata/toscrape-1 ../../shared/tse/indices/toscrape-1.ndx < test.txt