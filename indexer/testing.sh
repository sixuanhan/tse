# testing for indexer
# Author: Sixuan Han
# Date: April 29 2023


#testing indexer: zero argument
./indexer


#testing indexer: one argument
./indexer ../../shared/tse/crawldata/letters-1/


#testing indexer: three arguments
./indexer ../../shared/tse/crawldata/letters-1/ output outputNew


#testing indexer: invalid pageDirectory (non-existent path)
./indexer invalid output


#testing indexer: invalid pageDirectory (not a crawler directory)
./indexer ../crawler output


#testing indexer: invalid indexFile (non-existent path)
./indexer ../../shared/tse/crawldata/letters-1/ ../invalid/output


#testing indexer: invalid indexFile (read-only directory)
mkdir readOnly
chmod -w readOnly
./indexer ../../shared/tse/crawldata/letters-1/ readOnly/output
chmod +w readOnly
rm -rf readOnly


#testing indexer: invalid indexFile (existing, read-only file)
touch readOnly
chmod -w readOnly
./indexer ../../shared/tse/crawldata/letters-1/ readOnly
rm -f readOnly


#testing indexer: success with letters-1
./indexer ../../shared/tse/crawldata/letters-1/ output


#testing indextest: wrong num of arguments
./indextest


#testing indextest: invalid oldIndexFilename
./indextest invalid outputNew


#testing indextest: a successful transcription of output to outputNew
./indextest output outputNew


#testing indexer: success with toscrape-1
./indexer ../../shared/tse/crawldata/toscrape-1/ output


#testing indextest: a successful transcription of output to outputNew
./indextest output outputNew
~/cs50-dev/shared/tse/indexcmp output outputNew


#testing indexer: success with wikipedia_2
./indexer ../../shared/tse/crawldata/wikipedia_2/ output


#testing indextest: a successful transcription of output to outputNew
./indextest output outputNew
~/cs50-dev/shared/tse/indexcmp output outputNew