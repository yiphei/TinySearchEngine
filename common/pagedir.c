/* 
 * pagedir.c - CS50 'pagedir' module
 *
 * see pagedir.h for more information.
 *
 * Yifei Yan
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "pagedir.h"
#include "../libcs50/webpage.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** global types ****************/


/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */

 void pageSaver(char * directory, webpage_t * page, int id){
 	char *pathway = malloc(strlen(directory)+1+floor(log10(id))+1+1);
 	sprintf(pathway, "%s/%d", directory, id);   

 	FILE *fp;
 	fp = fopen(pathway, "w");

 	fprintf(fp, webpage_getURL(page));  //print URL
 	fprintf(fp,"\n");

 	char depth[64]; 
 	sprintf(depth, "%d",webpage_getDepth(page));  
 	
 	fprintf(fp,depth);  //print depth of the page
 	fprintf(fp,"\n");

 	fprintf(fp, webpage_getHTML(page));   //print the entire HTML of the page

 	fclose(fp);
 	free(pathway);
 }



