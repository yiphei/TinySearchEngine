
# Indexer.c

Yifei Yan May 2017

Indexer is a program that builds an index from a directory created by crawler. The program reads files from the given directory, builds an index that maps from words to pages (URLs), and writes that index to a given file. Indexer makes use of **pagedir.h**, **file.h**, **index.h** modules to save the html of the webpages, to build and save idexes, and some helper functions.

## Usage
Indexer follows the following **usage**:  
`usage: ./indexer pageDirectory indexFilename`

* `pageDirectory`: the pathname for an existing directory produced by the crawler
* `indexFilename`: pathname of a writeable file; it may or may not already exist

**Input**: It takes no input besides those parameters.

**Output**: The indexer writes the inverted index to `indexFilename`, and both the **index tester** and the **querier** read the inverted index from a file; the file shall be in the following format: one line per word, one word per line, each line provides the word and one or more (docID, count) pairs, in the format word docID count [docID count]…

## Example Command Lines

* `./indexer ../crawler/data indexFile`
* `./indexer ../crawler/wiki0 file`

##Exit Status
0 – success  
1 – invalid number of arguments passed  
2 – `pageDirectory` is not a valid directory created by crawler  
3 – `indexFilename` is a file that cannot be opened for writing 

## Compilation

To compile, simply `make`.  

To test, simply `make test`.

To clean up, simply `make clean`.

## Assumptions

* we assume that 1000 is a good size for the index
* we assume that the document id will never exceed 64 bytes
* we assume pageDirectory has files named 1, 2, 3, …, without gaps.
* The content of files in pageDirectory follow the format as defined in the specs

## "Non"-Assumptions

NA

## Limitations
NA

# Indextest.c

Indextest is a program that loads an index file produced by the indexer and saves it to another file.

## Usage
Indexer follows the following **usage**:  
`usage: ./indextest oldIndexFilename newIndexFilename`

* `oldIndexFilename` : is the name of a file produced by the indexer
* `newIndexFilename`: is the name of a file into which the index should be written

**Input**: the file created by indexer.c

**Output**: create a file `newIndexFilename` and write the index to that file, in the format identical to indexer.c, which is one line per word, one word per line, each line provides the word and one or more (docID, count) pairs, in the format word docID count [docID count]…

## Example Command Lines

* `./indextest indexFile indexFileTested`
* `./indextest indexFile indexTested`

##Exit Status
0 – success  
1 – invalid number of arguments passed

## Compilation

To compile, simply `make`.  

To test, simply `make tester`.

To clean up, simply `make clean`.
## Assumptions
* The content of the index file follows the format specified below
* assume that command-line arguments are valid

## "Non"-Assumptions
NA

## Limitations
NA
