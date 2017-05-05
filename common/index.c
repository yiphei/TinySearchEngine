/* 
 * set.c - CS50 'set' module
 *
 * see set.h for more information.
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
static void stockprint(FILE *fp, const char *key, void *item);

/**************** set_new() ****************/

void index_build(hashtable_t * index, char * pageDirectory){
  int MAX_DOC_ID_LENGTH = 64;
  int docID = 1;
  int wordCount = 0;
  char *file = malloc(strlen(pageDirectory)+1+MAX_DOC_ID_LENGTH+1);
  sprintf(file, "%s/%d", pageDirectory, docID);   

  FILE *fp;
  fp = fopen(file, "r");

  while (fp != NULL){

    webpage_t * page = retrieve_page(fp);
    
    int pos = 0;
    char *word;

    while ((pos = webpage_getNextWord(page, pos, &word)) > 0) {

        if (strlen(word) > 3){
          NormalizeWord(word);
          printf("Found word:  %s\n", word);
          wordCount++;

          if (hashtable_find(index, word) == NULL){
            printf("initialize counter for %s\n", word);
            counters_t * counter = counters_new();
            bool success = hashtable_insert(index, word, counter);
            if (!success) {
              printf("the insert failed on key %s\n",word);
            }
          }

          counters_add(hashtable_find(index, word), docID);
          printf("counter incremented\n");

  //        hashtable_print(index, stdout, stockprint);
 //         printf("********\n");

        }
        free(word);
    }

    webpage_delete(page);
    fclose(fp);
    docID ++;

    sprintf(file, "%s/%d", pageDirectory, docID);
    fp = fopen(file, "r");
  }
  free(file);
}

void index_save(hashtable_t * index, const char * indexFilename){

  FILE *fp = fopen(indexFilename, "w");

  hashtable_print(index, stdout, stockprint);
  printf("---------------------\n");
  hashtable_iterate(index,fp, printWord);

  fclose(fp);
}

static void printWord(void *arg, const char *key, void *item){
    if ((FILE * )arg != NULL && key != NULL && item != NULL){
      counters_t * counter = item;
      fprintf((FILE * )arg,"%s", key);
      printf("%s\n", key);
      counters_iterate(counter, (FILE * )arg, printCounter);
      fprintf((FILE * )arg,"\n");
  }

}


static void printCounter(void *arg, const int key, int count){

  if ((FILE * )arg != NULL && key >= 0 && count >= 0){
    fprintf((FILE * )arg, " %d %d", key, count);
  }
}


static void NormalizeWord(char * word){
  for(int i = 0; word[i]; i++){
    word[i] = tolower(word[i]);
  }
}



static void 
stockprint(FILE *fp, const char *key, void *item)
{
  fprintf(fp, "%s", key);
  counters_t * counter = item;
  counters_print(counter, fp);
}

