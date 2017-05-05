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

char * pageDirectory;
char * indexFilename;
int indexSize = 50;


// function prototype *declarations*
static void delete(void *item);


int main(const int argc, const char *argv[]) {


	pageDirectory = malloc(strlen(argv[1])+1);       
	strcpy(pageDirectory,argv[1]);
	indexFilename = malloc(strlen(argv[2])+1);
	strcpy(indexFilename,argv[2]);
	hashtable_t * index;
	index = hashtable_new(indexSize);
	index_build(index, pageDirectory);
	//printf("AAAA\n");
	index_save(index, indexFilename);
	hashtable_delete(index, delete); 

	free(pageDirectory);
	free(indexFilename);
	exit(0);

}

static void 
delete(void *item)
{
  if (item) {
    counters_delete(item);
  }
}
