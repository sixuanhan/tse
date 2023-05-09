1. For validating and printing the query, I implemented it this way:
raw query --check if there contains illegal characters--> clean query --> print the clean query --> check if the syntax is correct and insert implicit "and"s --> final query
So the final query that the user sees on stdout will contain explicit "and"s, which should be the only difference between "clean query" and "final query". The requirement does not specify what exactly is the clean query apart from that it should tokenize the raw query.

2. 