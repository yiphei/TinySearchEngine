/* 
 * indexer.c -  indexer is a program that builds an index from a directory created by crawler 
 * The program reads files from the given directory, builds an index that maps from words to pages (URLs), 
 * and writes that index to a given file.
 *
 * usage: ./indexer pageDirectory indexFilename
 * pageDirectory : is the pathname for an existing directory produced by the crawler
 * indexFilename: pathname of a writeable file; it may or may not already exist
 *
 *
 * input: none
 * output: The indexer writes the inverted index to a file, and both the index tester and the querier 
 * read the inverted index from a file; the file shall be in the following format: one line per word, 
 * one word per line, each line provides the word and one or more (docID, count) pairs, in the format
 * word docID count [docID count]…
 *
 * exit: If the program terminates normally, it exits with a return code of 0. Otherwise, it terminates with a documented, 
 * non-zero return code.
 *
 * Yifei Yan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/set.h"
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"
#include "../libcs50/file.h"
#include "../libcs50/counters.h"
#include "../common/index.h"

//global constants
char * pageDirectory;  //directory created by crawler
char * indexFilename;  //filename where to save the index of words
int indexSize = 1000;  //size of the index


// function prototype *declarations*
static bool check_indexFilename (char * filename);
static void delete(void *item);

int main(const int argc, const char *argv[]) {

	//check if there are two arguments
	if (argc != 3){
		printf("usage: ./indexer pageDirectory indexFilename\n");
		exit (1);
	}

	pageDirectory = malloc(strlen(argv[1])+1);       
	strcpy(pageDirectory,argv[1]);
	indexFilename = malloc(strlen(argv[2])+1);
	strcpy(indexFilename,argv[2]);

	//check that pageDirectory is a valid directory created by crawler
	if (!isCrawlerDirectory(pageDirectory)){
		printf("pageDirectory provided is an invalid directory\n");
		exit (2);
	}

	//check that indexFilename is a valid file
	if (!check_indexFilename(indexFilename)){
		printf("indexFilename provided is an invalid file\n");
		exit (3);
	}

	//create index for words
	hashtable_t * index;
	index = hashtable_new(indexSize);

	index_build(index, pageDirectory); 
	index_save(index, indexFilename);

	hashtable_delete(index, delete); 
	free(pageDirectory);
	free(indexFilename);
	exit(0);

}

/*
* functiont that takes a filename and checks that it is writable. If file does not exists,
* it will then create one
*/
static bool check_indexFilename (char * filename){

 	FILE *fp = fopen(filename, "w");
 	if(fp != NULL){
 		fclose(fp);
 		return true;
 	}
 	return false;
}


/*
* helper function to delete the index. It calls counter_delete to delete the items in index
*/
static void 
delete(void *item)
{
  if (item) {
    counters_delete(item);
  }
}
