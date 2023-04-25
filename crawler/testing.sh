# testing for crawler
# Author: Sixuan Han
# Date: April 24 2023

mkdir ../data/letters

# a successful crawl
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 2

# wrong num of arguments
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters

# invalid URL
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index ../data/letters 2

# invalid directory
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index ../data/letter 2

