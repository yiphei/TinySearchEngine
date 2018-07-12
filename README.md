# Tiny Search Engine

## Yifei Yan - April 2017

Written in C, the Tiny Search Engine replicates a web search engine and is comprised of three components: Web Crawler, Page Indexer, and Querier. 

Web Crawler is a standalone program that crawls the web and retrieves webpages starting from a “seed” URL. It parses the seed webpage, extracts any embedded URLs, then retrieves each of those pages, recursively, but limiting its exploration to a given “depth”. 

Page Indexer is a program that builds an index from a directory created by Web Crawler. The program reads files from the given directory, builds an index that maps from words to pages (URLs), and writes that index to a given file. 

Querier is standalone program that reads the index file produced by the Page Indexer, and page files produced by the Querier, and answers search queries submitted via stdin. Querier loads the index into memory (a data structure developed for the Page Indexer) and then prompts the user for queries. Queries are comprised of words, with optional and/or operators.


To build, run `make`.

To clean up, run `make clean`.
