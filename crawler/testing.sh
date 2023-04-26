# testing for crawler
# Author: Sixuan Han
# Date: April 24 2023


# turn on the CRAWLERTEST in makefile to view detailed logging!
rm -r ../data

mkdir ../data/


echo "testing: wrong num of arguments"
mkdir ../data/wrongNum
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/wrongNum
echo

echo "testing: invalid URL"
mkdir ../data/wrongUrl
./crawler asdfdsfa ../data/wrongUrl 2
echo

echo "testing: invalid directory"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/invalid 2
echo

echo "testing: invalid maxdepth"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/invalid 20
echo

echo "testing: a successful crawl of letters starting at index.html with depth 2"
mkdir ../data/letters-2a
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters-2a 2
echo "number of files in letters-2a: (should be 3)"
ls ../data/letters-2a | wc -l
echo

echo "testing: another successful crawl of letters starting at A.html with depth 2"
mkdir ../data/letters-2b
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/A.html ../data/letters-2b 2
echo "number of files in letters-2b: "
ls ../data/letters-2b | wc -l
echo

echo "testing: another successful crawl of letters starting at index.html with depth 3"
mkdir ../data/letters-3
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters-3 3
echo "number of files in letters-3: (should be 6)"
ls ../data/letters-3 | wc -l
echo

echo "testing: another successful crawl of toscrape starting at index.html with depth 3"
mkdir ../data/toscrape-3
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../data/toscrape-3 3
echo "number of files in toscrape-3: (should be 799)"
ls ../data/toscrape-3 | wc -l
echo

echo "testing: another successful crawl of wikipedia starting at wikipedia with depth 1"
mkdir ../data/wikipedia_1
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wikipedia_1 1
echo "number of files in wikipedia_1: "
ls ../data/wikipedia_1 | wc -l
echo

echo "testing: another successful crawl of wikipedia starting at wikipedia with depth 2"
mkdir ../data/wikipedia_2
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wikipedia_2 2
echo "number of files in wikipedia_2: "
ls ../data/wikipedia_2 | wc -l
echo
