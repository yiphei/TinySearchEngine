# CS50 Lab 5
## Yifei Yan - common.a library

## **index**

The index module that contains all the logic for building, saving and loading index files (this module is common between the Crawler and Indexer). Given a directory created by crawler, it first builds an index of all the words and the frequency of the words in each document in the given directory. After building an index, it outputs the index in a formatted way to a given file. 
Then, load_index reads the output of index_save and rebuilds an index from it.

### Usage

The *index* module, defined in `index.h` and implemented in `index.c`, exports the following functions through `index.h`:

```c
/*
* Given an index and a pageDirectory created by crawler, it builds an index of words with their 
* frequencies in each documents. The index maps from words to (docID, count) pairs, representing the
* number of occurences of that word in that document. We use a hashtable where in each item is a 
* counters_t where we use the docID as the key.
*/
void index_build(hashtable_t * index, const char * pageDirectory);

/*
* This fucntion takes an index and an indexFilename, and it outputs the index built from 
* index_build to indexFilename in a formatted way. The format it one word per line, each line 
* provides the word and one or more (docID, count) pairs, in the format: word docID count [docID count]…
*/
void index_save(hashtable_t * index, const char * indexFilename);

/*
* This function takes a oldIndexFilename created by index_save, and rebuilds an index in the format of 
* index_build by reading the entire file.
*/
hashtable_t * load_index(const char * oldIndexFilename);
```

### Implementation

The `index_build` method builds an index of type hashtable. The method loop over all the files in `pageDirectory` and extracts words from the files. It then inserts these words and their frequencies in each file into the index.

The `index_save` method outputs the index built in `index_built` to `indexFilename` in a formatted way. It makes use of the iteration methods of hashtable and counters

The `load_index` method reads a file created by `index_save` and rebuilds and index of words from it.

### Assumptions

No assumptions beyond those that are clear from the spec.  

### Compilation

To compile, simply `make`.  


## **pagedir**

This module provides functions used by crawler, indexer, and queries. For crawler, this module write each explored page from crawler.c to the directory with a unique document ID, wherein the document id starts at 1 and increments by 1 for each new page, and the filename is of form directory/id, and the first line of the file is the URL, and the second line of the file is the depth, and the rest of the file is the page content. For indexer, it builds a webpage from a file craeted by crawler and check that pageDirectory provided to indexer is valid.

### Usage

The *pagedir* module, defined in `pagedir.h` and implemented in `pagedir.c`, and exports the following functions through `pagedir.h`:

```c
/* Saves a copy of the webpage "page" to the directory */
/* Caller is rensposible for passing valid and correct parameters */
void pageSaver(char * directory, webpage_t * page, int id);

/* Creates a webpage by readling the lines of a file created by crawler*/
webpage_t * retrieve_page(FILE * fp);

/* checks if pageDirectory provided to indexer is a valid one*/
bool isCrawlerDirectory(char *dir);
```

### Implementation

The `pageSaver` method simply takes a webpage and saves it in a formatted way to a file.

The `retrieve_page` method creates a webpage by reading the lines of a file created by crawler. It makes use of functions provided by *file.h* module

The `isCrawlerDirectory` method checks that `pageDirectory` is a valid directory. To do so, it just checks if it can open the file `pageDirectory/.crawler`.

### Assumptions

No assumptions beyond those that are clear from the spec.  

### Compilation

To compile, simply `make`.  
