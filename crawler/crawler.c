/* 
 * crawler.c -  crawler is a standalone program that crawls the web and retrieves 
 * webpages starting from a “seed” URL. It parses the seed webpage, extracts any embedded 
 * URLs, then retrieves each of those pages, recursively, but limiting its exploration to 
 * a given “depth”
 *
 * usage: ./crawler seedURL pageDirectory maxDepth
 * seedURL : the initial URL and it must be internal
 * pageDirectory: pathname for an existing directory in which to write downloaded webpages
 * maxDepth: non-negative integer representing the maximum crawl depth
 *
 * input: none
 * output: write each explored page to the pageDirectory with a unique document ID, 
 * wherein * the document id starts at 1 and increments by 1 for each new page, * and 
 * the filename is of form pageDirectory/id, * and the first line of the file is the 
 * URL, * and the second line of the file is the depth, * and the rest of the file is the page
 * content
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
#include "../libcs50/memory.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/set.h"
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../common/pagedir.h"


//global constants
const int hashtableSize = 100;  //size of the hastable
int maxDepth;  //maximum crawl depth
char *directory; //directory where downloaded webpages are written
char* seedURL;  //initial URL

// function prototype *declarations*
bool directoryCheck(char * directory);
void crawler();
bool isBagEmpty(bag_t *bag);
static void delete(void *item);
bool isNumber(const char number[]);
int crawlPage(bag_t *bag,hashtable_t *ht, int fileID);
bool checkSeedURL(void);


int main(const int argc, const char *argv[]) {

	//check if there are four arguments
	if (argc != 4){
		printf("usage: ./crawler seedURL pageDirectory maxDepth\n");
		exit (1);
	}

	seedURL = malloc(strlen(argv[1])+1);       
	strcpy(seedURL,argv[1]);
	directory = malloc(strlen(argv[2])+1);
	strcpy(directory,argv[2]);

	//check if maxDepth is an integer
	if (!isNumber(argv[3])){
		printf("maxDepth must be an integer\n");
		exit(2);
	}

	maxDepth = atoi(argv[3]); 

	//check if directory exists
	if (!directoryCheck(directory)){
		printf("Invalid pageDirectory\n");
		exit(3);
	}

	//check that maxdDepth is non-negative
	if ( maxDepth < 0){
		printf("maxDepth cannot be a negative value\n");
		exit(4);
	}

	//check URL validity
	if ( !NormalizeURL(seedURL)){
		printf("invalid seedURL\n");
		exit(5);
	}
	else if (!IsInternalURL(seedURL)){  //check internality
		printf("seedURL is not internal\n");
		exit (6);
	}
	else if (!checkSeedURL()){  //check if URL exists
		printf("seedURL points to a valid server but it is a non-existing page\n");
		exit(7);
	}
	crawler();
	free(seedURL);
	free(directory);
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

/*
* function to check if given directory is writable. returns true if directory is writable
* returns false if directory is not writable
*/
bool directoryCheck(char * directory){

	char *pathway = malloc(strlen(directory)+10);  //name of the file to be created
	sprintf(pathway, "%s/.crawler", directory);
 	FILE *fp = fopen(pathway, "w");
 	if(fp != NULL){
 		free(pathway);
 		fclose(fp);
 		return true;
 	}
 	free(pathway);
 	return false;
}


/*
* function to check that an url found during crawling a html page is valid and internal.
* It then tries to insert it into the hastable if it has not been visited yet.
*/
void checkPage(bag_t *bag,hashtable_t *ht, webpage_t * page, char * result){

if (NormalizeURL(result) && IsInternalURL(result)){
    if (hashtable_insert(ht, result,result)){
    	webpage_t * resultPage;   //free this?
		resultPage = webpage_new(result, webpage_getDepth(page) + 1, NULL);
		bag_insert(bag,resultPage);
		printf("DEPTH:%d  ADDED Url: %s\n", webpage_getDepth(page),result);
    	}
    }

printf("DEPTH:%d  IGNORED Url: %s\n",webpage_getDepth(page), result);
}

/*
* function that crawls through a webpage. It tries to save a copy the html of the page to
* the directory and then it tries to look for more urls within the html. It returns
* fileID because it needs to be updated at each loop.
*/
int crawlPage(bag_t *bag,hashtable_t *ht, int fileID) {

		webpage_t *page = bag_extract(bag);
	
		if (webpage_fetch(page)){
			printf("DEPTH:%d  FETCHED Url: %s\n",webpage_getDepth(page), webpage_getURL(page));
			pageSaver(directory, page, fileID); //saves a copy of the page to the directory
			printf("DEPTH:%d  SAVED Url: %s\n",webpage_getDepth(page), webpage_getURL(page));
			fileID++;
		}

		//find url in the webpage if the depth is not exceeded
		if (webpage_getDepth(page) < maxDepth){
			printf("DEPTH:%d  SCANNING Url: %s\n",webpage_getDepth(page), webpage_getURL(page));
			int pos = 0;
 			char *result;  //url of a webpage
			while ((pos = webpage_getNextURL(page, pos, &result)) > 0) {
				printf("DEPTH:%d  FOUND Url: %s\n", webpage_getDepth(page),result);
    			checkPage(bag,ht,page,result);
     			free(result);
			}
		}
		webpage_delete(page);
		return fileID;
}

/*
* checks if a seed that points to an internal server is an existing page. returns true
* if page exists and false if page does not. 
*/
bool checkSeedURL(void){
	webpage_t * seedPage;
	seedPage = webpage_new(seedURL, 0, NULL); //initialize webapge for seedURL
	if (webpage_fetch(seedPage)){
		webpage_delete(seedPage);
		return true;
	}
	webpage_delete(seedPage);
	return false;
}


/*
* the main crawler function. Here, bag, hashtable, and the seed webpage are initialized.
* It then calls helper functions to crawl webpages.
*/
void crawler(void){

	bag_t *bag;     
	bag = bag_new();  //initialize bag. It contains the list of webstages that still need to be explored
	hashtable_t *ht;
	ht = hashtable_new(hashtableSize);     //initialize hashtable. It checks if we already visisted a page
	int fileID = 1;   //id for the file output
	webpage_t * seedPage;
	seedPage = webpage_new(seedURL, 0, NULL); //initialize webapge for seedURL
	bag_insert(bag,seedPage);
	hashtable_insert(ht, seedURL, seedURL); 

	while(! isBagEmpty(bag)){
		fileID = crawlPage(bag,ht,fileID);
	}
	
	hashtable_delete(ht, delete);
	bag_delete(bag, webpage_delete);
}

/*
* Helper function needed because hashtable_delete needs a function as a parameter.
* However, this function does nothing.
*/
static void 
delete(void *item)
{}

/*
* Checks if the bag is empty. return true if bag is empty, otherwise returns false.
*/
bool isBagEmpty(bag_t *bag){
	
	webpage_t *page = bag_extract(bag);
	if (page != NULL) {
		bag_insert(bag,page); 
		return false;
	}
	return true;
}


