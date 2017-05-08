/*
* index.h - header file for CS50 'index' module
* 
* The index module that contains all the logic for building, saving and loading index files 
* (this module is common between the Crawler and Indexer). Given a directory created by crawler, 
* it first builds an index of all the words and the frequency of the words in each document in the 
* given directory. After building an index, it outputs the index in a formatted way to a given file. 
* Then, load_index reads the output of index_save and rebuilds an index from it.
*/ 

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/set.h"
#include "../libcs50/counters.h"
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"
#include "../libcs50/file.h"

/**************** functions ****************/

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

#endif // __INDEX_H