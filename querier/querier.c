/* 
 * querier.c -  standalone program that reads the index file produced by the TSE Indexer, and page 
 * files produced by the TSE Querier, and answers search queries submitted via stdin.
 * Querier loads the index into memory (a data structure we developed for the Indexer) and then 
 * prompts the user for queries. Queries are comprised of words, with optional and/or operators.
 *
 * usage: ./querier pageDirectory indexFilename
 * pageDirectory :  pathname of a directory produced by the Crawler
 * indexFilename: pathname of a file produced by the Indexer
 *
 *
 * input: read search queries from stdin, one per line, until EOF
 * output: rank the resulting set of documents according to its score 
 * and print the set of documents in decreasing rank order; for each, list the score, document ID and URL
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

#define MAX_QUERY_WORDS 100  //size of the array where the query words will be stored

//struct to hold a document
typedef struct docnode{
  char * URL;
  int docID;
  int freq;  //frequency of the query
} docnode_t;

//struct to hold the docnodes in an array
typedef struct docsArray {
   docnode_t * array;   //array of docnodes
   int size;		//size of the array
 }docsArray_t;  

//struct to hold two counters and the intersection or union of those two cunters
struct counterslist{
	counters_t * counters1;
	counters_t * counters2;
	counters_t * mergecounter;  //intersection or union of counters1,counters2
};

//global constants
char * pageDirectory;
char * indexFilename;
char * querier;
struct counterslist * list;

// function prototype *declarations*
static void delete(void *item);
static bool check_indexFilename (char * filename);
int readInput(char * array[]);
counters_t * query(char * word, hashtable_t * index);
counters_t * andSequence (counters_t * c1, counters_t * c2);
void intersection(void *arg, const int key, int count);
counters_t * orSequence (counters_t * counters1, counters_t * counters2);
void sum(void *arg, const int key, int count);
void computeCountersSize(void *arg, const int key, int count);
void parseInput(char * input);
int line_getNextWord(char * line, int pos, char **word);
counters_t * queryInput(hashtable_t * index, char * array[]);
int node_compare(const void *a, const void *b);
static void NormalizeWord(char * word);
int is_empty(const char *s);
void buildArray(void *arg, const int key, int count);
void sort(counters_t * counter);
int re_readInput(char * array[]);
int buildQueryArray(char * array[]);


int main(const int argc, const char *argv[]) {

	//check if there are two arguments
	if (argc != 3){
		printf("./querier pageDirectory indexFilename\n");
		exit (1);
	}

	pageDirectory = malloc(strlen(argv[1])+1);       
	strcpy(pageDirectory,argv[1]);
	indexFilename = malloc(strlen(argv[2])+1);
	strcpy(indexFilename,argv[2]);

	//check that pageDirectory is a valid directory created by crawler
	if (!isCrawlerDirectory(pageDirectory)){
		printf("pageDirectory provided is an invalid directory\n");
		free(pageDirectory);
		exit (2);
	}
	//check that indexFilename is a valid file
	if (!check_indexFilename(indexFilename)){
		printf("indexFilename provided is an invalid file\n");
		free(indexFilename);
		exit (3);
	}
	
	hashtable_t * index = load_index(indexFilename);  //load the index
	list = malloc(sizeof(struct counterslist));

	while (!feof(stdin)){

		printf("KEY WORDs:> ");
		char * array [MAX_QUERY_WORDS];  //array of query words
		//initialize array
		for (int i =0; i<MAX_QUERY_WORDS; i++) {
		array[i] = NULL;
		}

		int x = readInput(array);  //read the user input

		//terminate if the input is EOF
		if (x == 1){
			break;
		}

		counters_t * finalcounter = queryInput(index, array);  //the final counter for the entire query search

		if (finalcounter == NULL){
			printf("No documents match\n");
		}
		else{
			sort(finalcounter);  
			counters_delete(finalcounter);
		}
		printf("--------------------------\n");

		//free the array
		for (int i=0; i<MAX_QUERY_WORDS; i++) {
			if (array[i] != NULL) {
				free(array[i]);
			}
		}
	}

	free(list);
	//hashtable_delete(index, delete); 
	free(querier);
	free(pageDirectory);
	free(indexFilename);
	exit(0);

}

/*
* functiont that takes a filename and checks that it is readable.
*/
static bool check_indexFilename (char * filename){

 	FILE *fp = fopen(filename, "r");
 	if(fp != NULL){
 		fclose(fp);
 		return true;
 	}
 	return false;
}

/*
* Function that searches the query in the index. It keeps track of two counters
* The andSum counter is the intersection counter. The orSum counter is the union counter.
* It returns the final counter for the entire query search.
*/
counters_t * queryInput(hashtable_t * index, char * array[]){

	counters_t * andSum = NULL;  //the intersection counter of two words/sequences(or just one)        //free this?
	counters_t * orSum = NULL;  //the union counter of two words/sequences            //free this?
	int x = 0;  //current position in the array

	while(x < MAX_QUERY_WORDS && array[x] != NULL){

		//for single word query or conjuction
		if (strcmp(array[x],"or") != 0 && strcmp(array[x],"and") != 0){
			andSum = andSequence(query(array[x], index), andSum);
		}

		//for disjuntions
		if (strcmp(array[x],"or") == 0 || array[x+1] == NULL){
			orSum = orSequence(andSum, orSum);
			andSum = NULL;
		}
		x++;
	}

	// if there was no "or" in the query entry
	if (orSum == NULL){
		return andSum;
	}
	return orSum;
}


/*
* Function that prompts the user for a new query entry after an incorret query.
* Returns 0 if successful. Returns 1 is there was an EOF
*/
int re_readInput(char * array[]){
	printf("KEY WORDs:> ");
	querier = readlinep(stdin);

	if(feof(stdin)){
		return 1;
	 }

	//free the array
	for (int i =0; i<MAX_QUERY_WORDS; i++) {
		array[i] = NULL;
	}

	return 0;
}

/*
* helper function that break the query line into an array of words.
* If there was an incorrect query input, the user will be prompted again.
* Returns 0 if array built successfully. Returns 1 if there was an EOF
*/
int buildQueryArray(char * array[]){

	int pos = 0;
    char *word; 
    int x = 0; //current position in the array

    while ((pos = line_getNextWord(querier, pos, &word)) > 0) {
    	NormalizeWord(word);  //convert to lowercase
    	array[x] = malloc(strlen(word) +1);
    	strcpy(array[x], word);

    	//if and/or appear at the beginning of the query entry
    	if (strcmp(array[0],"and") == 0 || strcmp(array[0],"or") == 0){
    		printf("the literal ‘and’ must come between words, and the literal ‘or’ must come between andsequences. They cannot appear at the beginning or end of a query\n");
    		//ask for a new query
    		if( re_readInput(array) == 1){
    			return 1;
    		}
    		x = -1;
    		pos = 0;
    	}

    	//if and/or are adjacent
    	if(strcmp(word, "and") == 0 || strcmp(word, "or") == 0){
    		if (strcmp(array[x-1], "and") == 0 || strcmp(array[x-1], "or") == 0){
    			printf("The literals (‘and’ & ‘or’) cannot be adjacent\n");
    			//ask for a new query
    			if( re_readInput(array) == 1){
    				return 1;
    			}
    			x = -1;
    			pos = 0;
    		}
    	}
    	x++;
        free(word);
    }

    //if a word is non-alphabetical
    if (pos == -2) {
    	printf("Characters other than letters or spaces are disallowed\n");
    	//ask for a new query
    	if( re_readInput(array) == 1){
    		return 1;
    	}
    	//build the array again
    	if (buildQueryArray(array) ==1){
    		return 1;
    	}
    }

    //if and/or appear at the end of the query entry
    if (strcmp(array[x-1],"and") == 0 || strcmp(array[x-1],"or") == 0 ){
    	printf("the literal ‘and’ must come between words, and the literal ‘or’ must come between andsequences. They cannot appear at the beginning or end of a query\n");
    	//ask for a new query
    	if( re_readInput(array) == 1){
    		return 1;
    	}
    	//build the array again
    	if (buildQueryArray(array) ==1){
    		return 1;
    	}
    }
    return 0;
}

/*
* function that reads the stdin and break it into an array of words.
* it calls some helper function
* Return 1 if successful; returns 0 input was EOF
*/
int readInput(char * array[]){
	querier = readlinep(stdin); 

	//exit if EOF
	if(feof(stdin)){
		return 1;
	 }
	 //keep asking for a query if the query is an empty line
    if (is_empty(querier) == 1){
    	while (is_empty(querier) == 1){
    		printf("Line is empty. Please write something\n");
    		printf("KEY WORDs:> ");
    		querier = readlinep(stdin);
    		if(feof(stdin)){
				return 1;
	 		}
    	}
    }

    //break the input into an array of words. If returns 1, then there was an EOF
    if (buildQueryArray(array) == 1){
    	return 1;
    }

    //print out the array of words
    printf("Query: ");
	for (int x = 0; x < MAX_QUERY_WORDS; x++){
		if (array[x]!= NULL) {
		printf("%s ", array[x]);
		}
	}
	printf("\n");

	return 0;
}

/*
* Source: stackoverflow.com
* Author: casablanca
* Check is a string is an empty line. Returns 1 if it is an empty line, otherwise return 0
*/
int is_empty(const char *s) {
  while (*s != '\0') {
    if (!isspace(*s))
      return 0;
    s++;
  }
  return 1;
}

/*
* Source: stackoverflow.com
* Author: Earlz
* This function takes a string as a parameters and converts all of its characters into lowercase
*
*/
static void NormalizeWord(char * word){
  for(int i = 0; word[i]; i++){
    word[i] = tolower(word[i]);
  }
}

/*
* Source: webpage_getNextWord from webpage.c
* returns the next word from char * line into word.
* It returns -2 if some word in line contains a nonalphabetical character
* return -1 if the entire input has been processed
*/
int 
line_getNextWord(char * line, int pos, char **word)
{

  // make sure we have something to search, and a place for the result
  if (line == NULL || word == NULL) {
    return -1;
  }

  const char *beg;                         // beginning of word
  const char *end;                         // end of word

	while (line[pos] && isspace(line[pos])) {
		pos++;
	}

  // line fully consumed.
  if (line[pos] == '\0') {
    *word = NULL;
    return -1;
  }

  // pos is at the first character of a word
  beg = &(line[pos]);

  // consume word
  while (line[pos] != '\0' && !isspace(line[pos])) {
  	if (!isalpha(line[pos]) && !isspace(line[pos])) {
  		return -2;
  	}
    pos++;
  }
  // at this point, doc[pos] is the first character *after* the word.

  // pos refers to the last character of the word
  end = &(line[pos-1]);

  // 'beg' points to first character of the word
  // 'end' points to last character of the word
  int wordlen = end - beg + 1;

  // allocate space for length of new word + '\0'
  *word = calloc(wordlen + 1, sizeof(char));
  if (*word == NULL) {	      // out of memory!
    return -1;
  }

  // copy the new word
  strncpy(*word, beg, wordlen);
  return pos;
}

/*
* helper function that returns the counter for a specific word in the index.
*/
counters_t * query(char * word, hashtable_t * index){
	return hashtable_find(index, word);
}

/*
* Function that returns the counter of the intersection of two counters. 
* It iterates through one counter to build the intersection counter.
* If counters2 is NULL, counters1 is returned.
* If counters1 is NULL, NULL is returned.
*/
counters_t * andSequence (counters_t * counters1, counters_t * counters2){

	if (counters2 == NULL){
		return counters1;
	}
	if (counters1 == NULL){
		return NULL;
	}

	counters_t * mergecounter = counters_new();  //intersection of counters1 and counters2

	//store countesr1,countesr2, and mergecounter into a counterslist
	list->counters1 = counters1;
	list->counters2 = counters2;
	list->mergecounter = mergecounter;
	//iterate to create a counter that is the intersection of counters1 and counters2
	counters_iterate(counters1, list, intersection);
	return list->mergecounter;
}

/*
* helper function called by counters_iterate. It builds mergecounter.
*/
void intersection(void *arg, const int key, int count){

	struct counterslist * list = arg;

	//if counters1 an counters2 appear in the same document
	if (counters_get( list->counters2, key) != 0){
		//set the mergecounter to the lowest count
		if(count > counters_get(list->counters2,key)){
			counters_set(list->mergecounter, key, counters_get(list->counters2,key));
		}
		else{
			counters_set(list->mergecounter, key, count);
		}
	}
}

/*
* Function that returns the counter of the union of two counters. 
* It iterates through both counters to build the union counter.
* If counters2 is NULL, counters1 is returned.
* If counters1 is NULL, counters2 is returned.
*/
counters_t * orSequence (counters_t * counters1, counters_t * counters2){

	if (counters2 == NULL){
		return counters1;
	}

	if (counters1 == NULL){
		return counters2;
	}

	counters_t * mergecounter = counters_new(); //union of counters1 and counters2

	//store countesr1,countesr2, and mergecounter into a counterslist
	list->counters1 = counters1;
	list->counters2 = counters2;
	list->mergecounter = mergecounter;
	//iterate through both counters to build the union counter
	counters_iterate(counters1, list, sum);
	counters_iterate(counters2, list, sum);
	return list->mergecounter;

}

/*
* helper function called by counters_iterate. It builds mergecounter.
*/
void sum(void *arg, const int key, int count){

	struct counterslist * list = arg;
	//set the mergecounter to the sum of the counters1 and counters2
	counters_set(list->mergecounter, key, counters_get(list->counters1, key) + counters_get(list->counters2, key));
}

/*
* It sorts the final counter for the entire query line and prints out the ranking
* with the highest match on top.
*/
void sort(counters_t * counter){

	int size=0; //size of the counter
	//computer the size of the counter
	counters_iterate(counter, &size, computeCountersSize);

	docsArray_t * docs = malloc(sizeof(docsArray_t));  //free this
	docs->array = malloc(sizeof(docnode_t) * size);
	docs->size = 0;

	//build the array of docnodes
	counters_iterate(counter, docs, buildArray);
	qsort(docs->array, docs->size, sizeof(docnode_t), node_compare);

	//print out the ranking
	printf("Matched %d documents(ranked):\n", size);
	for (int x = 0; x < size; x++){
		docnode_t doc = docs->array[x];
		printf("Score:  %d  doc:  %d: %s\n", doc.freq, doc.docID, doc.URL);
	}

	//free the array in docs and the docs

	for (int x = 0; x < size; x ++){
		free(docs->array[x].URL);
	}

	free(docs->array);
	free(docs);
}

/*
* helper funciton to compute the size of the final counters
*/
void computeCountersSize(void *arg, const int key, int count){
	int *size = (int *)arg;
	(*size)++;
}

/*
* Builds an array of docndoes from the final counter. 
* It stores the docID, frequency, and the URL into the docnode.
* Then, the docnode is stored in the array in docs.
*/
void buildArray(void *arg, const int key, int count){
 	docsArray_t * docs = arg;

  	int MAX_DOC_ID_LENGTH = 64;   //assume that the document id will never exceed 64 bytes
  	char *file = malloc(strlen(pageDirectory)+1+MAX_DOC_ID_LENGTH+1);  //name of the file
  	sprintf(file, "%s/%d", pageDirectory, key);   

  	FILE *fp;
  	fp = fopen(file, "r");

  	//storing into the docnode
 	docs->array[docs->size].freq = count;
 	docs->array[docs->size].docID = key;
 	docs->array[docs->size].URL = readlinep(fp);
 	docs->size = docs->size+1;  //increase the size of the docs

 	free(file);
 	fclose(fp);
 }

/*
* helper fucnction called by qsort.
* it returns the difference between the freq of two documents.
* It basically sorts the documents in descending order
*/
int node_compare(const void *a, const void *b) {
	struct docnode *elem1=(struct docnode* ) a;
	struct docnode *elem2=(struct docnode *) b;
	return elem2->freq - elem1->freq;
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

