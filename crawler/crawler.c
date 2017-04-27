


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../libcs50/memory.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/set.h"
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../common/pagedir.h"


//global constants
const int hashtableSize = 100;

// function prototype *declarations*
bool directoryCheck(char * directory);
void crawler(char * seedURL, char * directory, int maxDepth);
bool isBagEmpty(bag_t *bag);
static void delete(void *item);
bool isNumber(const char number[]);


int main(const int argc, const char *argv[]) {
	int maxDepth = atoi(argv[3]);   //do malloc instead
	char seed[100];       //do malloc instead
	strcpy(seed,argv[1]);
	char directory[100];    //do malloc instead
	strcpy(directory,argv[2]);

	if (argc != 4){
		printf("usage: ./crawler seedURL pageDirectory maxDepth\n");
		exit (1);
	}

	if (!isNumber(argv[3])){
		printf("maxDepth must be an integer\n");
		exit(2);
	}

	if (!directoryCheck(directory)){
		printf("Invalid pageDirectory\n");
		exit(3);
	}

	if ( maxDepth < 0){
		printf("maxDepth cannot be a negative value\n");
		exit(4);
	}

	if ( !NormalizeURL(seed)){
		printf("invalid seedURL\n");
		exit(5);
	}
	else if (!IsInternalURL(seed)){
		printf("seedURL is not internal\n");
		exit (6);
	}
	crawler(seed, directory, maxDepth);

	exit(0);
}

/*
*author: niyasc
*Date: 4/26/1996
*Source: stackoverflow
*functionality: check if an array is of type integer. Returns true if it is of type int.
*/
bool isNumber(const char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

bool directoryCheck(char * directory){

	char pathway[900];

	sprintf(pathway, "%s/.crawler", directory);

 	FILE *fp = fopen(pathway, "w");
 	if(fp != NULL){
 		fclose(fp);
 		return true;
 	}
 	return false;
}



void crawler(char * seedURL, char * directory, int maxDepth){

	bag_t *bag;     //free this
	bag = bag_new();    
	hashtable_t *ht;
	ht = hashtable_new(hashtableSize);     //free this
	int fileID = 1;   //id for the file output
	webpage_t * seedPage;
	seedPage = webpage_new(seedURL, 0, NULL); //what to put as third parameter? fre this
	bag_insert(bag,seedPage);
	hashtable_insert(ht, seedURL, seedURL); //check if you want seedURL as the item

	while(! isBagEmpty(bag)){
		// webpage_t *page = malloc(sizeof(webpage_t));
		// page = bag_extract(bag);

		webpage_t *page = bag_extract(bag);
	
		if (webpage_fetch(page)){
			pageSaver(directory, page, fileID); //write this module
			printf("SAVED TO DIR Url: %s\n", webpage_getURL(page));
			fileID++;
		}

		if (webpage_getDepth(page) < maxDepth){
			int pos = 0;
 			char *result;  //free this.  //all the urls in the html

			while ((pos = webpage_getNextURL(page, pos, &result)) > 0) {
    			printf("Found url: %s\n", result);

    			if (NormalizeURL(result) && IsInternalURL(result)){
					printf("VALID Url: %s\n", result);
    				if (hashtable_insert(ht, result,result)){
    					printf("ADDED Url: %s\n", result);
    					webpage_t * resultPage;   //free this?
						resultPage = webpage_new(result, webpage_getDepth(page) + 1, NULL);
						bag_insert(bag,resultPage);
						printf("SAVED Url: %s\n", result);
    				}
    			}
     			free(result);
			}

		}
		

	}
	
	hashtable_delete(ht, delete);
	bag_delete(bag, webpage_delete);

}

static void 
delete(void *item)
{}

bool isBagEmpty(bag_t *bag){
	webpage_t *page = bag_extract(bag);

	if (page == NULL){

		webpage_delete(page);
		return true;
	}
	else{

		bag_insert(bag,page);  //do i need to free it?
		return false;
	}
}

