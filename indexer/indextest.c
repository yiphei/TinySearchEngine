/* 
 * indextest.c -  indextest is a program that loads an index file produced by the indexer and 
 * saves it to another file.
 * 
 *
 * usage: ./indextest oldIndexFilename newIndexFilename
 * oldIndexFilename: is the name of a file produced by the indexer
 * newIndexFilename: is the name of a file into which the index should be written
 *
 *
 * input: the file created by indexer.c
 * output: create a file newIndexFilename and write the index to that file, in the format 
 * identical to indexer.c, which is one line per word, one word per line, 
 * each line provides the word and one or more (docID, count) pairs, in the format
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
#include <math.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/set.h"
#include "../libcs50/counters.h"
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"
#include "../libcs50/file.h"
#include "../common/index.h"


//global constants
char * oldIndexFilename;
char * newIndexFilename;

// function prototype *declarations*
static void delete(void *item);


int main(const int argc, const char *argv[]) {


	//check if there are two arguments
	if (argc != 3){
		printf("usage: ./indextest oldIndexFilename newIndexFilename\n");
		exit (1);
	}

	oldIndexFilename = malloc(strlen(argv[1])+1);       
	strcpy(oldIndexFilename,argv[1]);
	newIndexFilename = malloc(strlen(argv[2])+1);
	strcpy(newIndexFilename,argv[2]);
	

	hashtable_t * index = load_index(oldIndexFilename);
	index_save(index, newIndexFilename);


	hashtable_delete(index, delete);

	free(oldIndexFilename);
	free(newIndexFilename);
	exit(0);

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
