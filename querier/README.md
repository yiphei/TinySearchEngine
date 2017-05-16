
# Querier.c

Yifei Yan May 2017

Querier is standalone program that reads the index file produced by the TSE Indexer, and page files produced by the TSE Querier, and answers search queries submitted via stdin. Querier loads the index into memory (a data structure we developed for the Indexer) and then prompts the user for queries. Queries are comprised of words, with optional and/or operators.

## Usage
QUerier follows the following **usage**:  
`./querier pageDirectory indexFilename`

* `pageDirectory`: pathname of a directory produced by the Crawler
* `indexFilename`: pathname of a file produced by the Indexer

**Input**: read search queries from stdin, one per line, until EOF

**Output**: rank the resulting set of documents according to its score and print the set of documents in decreasing rank order; for each, list the score, document ID and URL

## Example Command Lines

* `./querier ~cs50/data/tse-output/cs50-3 ~cs50/data/tse-output/cs50-index3`
`KEY WORDs:> dartmouth`
* `./querier ../indexer/test_dir ../indexer/indexFile`  
`KEY WORDs:> crab`

##Exit Status
0 – success  
1 – invalid number of arguments passed  
2 – `pageDirectory` is not a valid directory created by crawler  
3 – `indexFilename` is a file that cannot be opened for reading 

## Compilation

To compile, simply `make`.  

To test, simply `make test`.

To clean up, simply `make clean`.

## Assumptions

* we assume that the document id will never exceed 64 bytes
* we assume `pageDirectory` has files named 1, 2, 3, …, without gaps.
* The content of files in `pageDirectory` follow the format as defined in the specs
* The content of the file named by `indexFilename` follows our Index file format
* we assume 100 to be a good size for the query array

## "Non"-Assumptions

NA

## Limitations
NA