# testing for crawler
# Author: Sixuan Han
# Date: April 24 2023


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

echo "testing: a successful crawl of letters starting at index.html with depth 0"
mkdir ../data/letters-0
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters-0 0
echo "number of files in letters-0: (should be 1)"
ls ../data/letters-0 | wc -l
echo

echo "testing: another successful crawl of letters starting at index.html with depth 10"
mkdir ../data/letters-10
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters-10 10
echo "number of files in letters-10:"
ls ../data/letters-10 | wc -l
echo

echo "testing: another successful crawl of toscrape starting at index.html with depth 0"
mkdir ../data/toscrape-0
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../data/toscrape-0 0
echo "number of files in toscrape-0: (should be 1)"
ls ../data/toscrape-0 | wc -l
echo

echo "testing: another successful crawl of toscrape starting at index.html with depth 1"
mkdir ../data/toscrape-1
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../data/toscrape-1 1
echo "number of files in toscrape-1: (should be 73)"
ls ../data/toscrape-1 | wc -l
echo

echo "testing: another successful crawl of wikipedia starting at wikipedia with depth 0"
mkdir ../data/wikipedia_0
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wikipedia_0 0
echo "number of files in wikipedia_0: "
ls ../data/wikipedia_0 | wc -l
echo

echo "testing: another successful crawl of wikipedia starting at wikipedia with depth 1"
mkdir ../data/wikipedia_1
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wikipedia_1 1
echo "number of files in wikipedia_1: "
ls ../data/wikipedia_1 | wc -l
echo