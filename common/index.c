/* 
 * index.c - CS50 'index' module
 *
 * see index.h for more information.
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


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** global types ****************/


/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static void printWord(void *arg, const char *key, void *item);
static void printCounter(void *arg, const int key, int count);
static void NormalizeWord(char * word);

/**************** set_new() ****************/

void index_build(hashtable_t * index, const char * pageDirectory){
  int MAX_DOC_ID_LENGTH = 64;   //assume that the document id will never exceed 64 bytes
  int docID = 1;   //filename ID in which the HTML is stored
  char *file = malloc(strlen(pageDirectory)+1+MAX_DOC_ID_LENGTH+1);  //name of the file
  sprintf(file, "%s/%d", pageDirectory, docID);   

  FILE *fp;
  fp = fopen(file, "r");

  while (fp != NULL){

    webpage_t * page = retrieve_page(fp);  //retrieve the webpage from the file
    int pos = 0;
    char *word; 

    while ((pos = webpage_getNextWord(page, pos, &word)) > 0) {
        //ignore words less than three characters
        if (strlen(word) > 2){  
          NormalizeWord(word);  //covert word to lower case

          //initialize counter if word is never encountered
          if (hashtable_find(index, word) == NULL){  
            hashtable_insert(index, word, counters_new());
          }

          //increment count
          counters_add(hashtable_find(index, word), docID);
        }
        free(word);
    }

    webpage_delete(page);
    fclose(fp);
    docID ++;

    sprintf(file, "%s/%d", pageDirectory, docID);  //next file
    fp = fopen(file, "r");  //open next file
  }
  free(file);
}


void index_save(hashtable_t * index, const char * indexFilename){

  FILE *fp = fopen(indexFilename, "w");
  hashtable_iterate(index,fp, printWord);  
  fclose(fp);
}

/*
* helper function that outputs the word to a given file. It then calls a helper fuction
* to output the docID and frequency. Then, it prints a newline.
*/
static void printWord(void *arg, const char *key, void *item){
    if ((FILE * )arg != NULL && key != NULL && item != NULL){
      counters_t * counter = item;
      fprintf((FILE * )arg,"%s", key);  //print the word
      counters_iterate(counter, (FILE * )arg, printCounter);  //print the docID and frequency
      fprintf((FILE * )arg,"\n");  //print newline for next word
  }
}

/*
* helper function that outputs the docID and the frequency of a word into a given file
*/ 
static void printCounter(void *arg, const int key, int count){

  if ((FILE * )arg != NULL && key >= 0 && count >= 0){
    fprintf((FILE * )arg, " %d %d", key, count); //print docID and frequency
  }
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


hashtable_t * load_index(const char * oldIndexFilename){

  FILE * fp = fopen(oldIndexFilename, "r");
  int indexSize = lines_in_file(fp);  //size of the index
  hashtable_t * index;
  index = hashtable_new(indexSize);
  char * word;  

  //while it is not the end of the file
  while ((!feof(fp))){ 

    word = readwordp(fp);  //read the word
    counters_t * counter = counters_new(); //create new counter
    hashtable_insert(index, word, counter);  //insert word with new counter 
    int docID;
    int frequency;

    //read the docID and frequency of the word and set counter accordingly
    while (fscanf(fp, "%d %d ",&docID, &frequency) > 1){
        counters_set(counter, docID, frequency);
      }
    free(word);
  }

  fclose(fp);
  return index;
}


