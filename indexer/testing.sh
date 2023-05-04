# testing for indexer
# Author: Sixuan Han
# Date: April 29 2023


#testing indexer: zero argument
./indexer


#testing indexer: one argument
./indexer ../../shared/tse/crawldata/letters-1/


#testing indexer: three arguments
./indexer ../../shared/tse/crawldata/letters-1/ output.ndx outputNew.ndx


#testing indexer: invalid pageDirectory (non-existent path)
./indexer invalid output.ndx


#testing indexer: invalid pageDirectory (not a crawler directory)
./indexer ../crawler output.ndx


#testing indexer: invalid indexFile (non-existent path)
./indexer ../../shared/tse/crawldata/letters-1/ ../invalid/output.ndx


#testing indexer: invalid indexFile (read-only directory)
mkdir readOnly
chmod -w readOnly
./indexer ../../shared/tse/crawldata/letters-1/ readOnly/output.ndx
chmod +w readOnly
rm -rf readOnly


#testing indexer: invalid indexFile (existing, read-only file)
touch readOnly.ndx
chmod -w readOnly.ndx
./indexer ../../shared/tse/crawldata/letters-1/ readOnly.ndx
rm -f readOnly.ndx


#testing indexer: success with letters-1
./indexer ../../shared/tse/crawldata/letters-1/ output.ndx


#testing indextest: wrong num of arguments
./indextest


#testing indextest: invalid oldIndexFilename
./indextest invalid.ndx outputNew.ndx


#testing indextest: a successful transcription of output to outputNew
./indextest output.ndx outputNew.ndx


#testing indexer: success with toscrape-1
./indexer ../../shared/tse/crawldata/toscrape-1/ output.ndx

#should print nothing (because the two files should be the same)
~/cs50-dev/shared/tse/indexcmp output.ndx ~/cs50-dev/shared/tse/indices/toscrape-1.ndx


#testing indextest: a successful transcription of output to outputNew
./indextest output.ndx outputNew.ndx

#should print nothing (because the two files should be the same)
~/cs50-dev/shared/tse/indexcmp output.ndx outputNew.ndx


#testing indexer: success with wikipedia_2
./indexer ../../shared/tse/crawldata/wikipedia_2/ output.ndx

#should print nothing (because the two files should be the same)
~/cs50-dev/shared/tse/indexcmp output.ndx ~/cs50-dev/shared/tse/indices/wikipedia_2.ndx


#testing indextest: a successful transcription of output to outputNew
./indextest output.ndx outputNew.ndx

#should print nothing (because the two files should be the same)
~/cs50-dev/shared/tse/indexcmp output.ndx outputNew.ndx