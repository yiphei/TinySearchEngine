/* 
 * pagedir.h - header file for CS50 'pagedir' module
 * 
 * This module provides functions used by crawler, indexer, and queries. For crawler, this module 
 * write each explored page from crawler.c to the directory with a unique document ID, 
 * wherein the document id starts at 1 and increments by 1 for each new page, and the 
 * filename is of form directory/id, and the first line of the file is the URL, and 
 * the second line of the file is the depth, and the rest of the file is the page content.
 * 
 * For indexer, it builds a webpage from a file craeted by crawler and check that pageDirectory provided
 * to indexer is valid.
 *  
 *
 * Yifei Yan
 */

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"

/**************** global types ****************/


/**************** functions ****************/

/* Saves a copy of the webpage "page" to the directory */
/* Caller is rensposible for passing valid and correct parameters */
void pageSaver(char * directory, webpage_t * page, int id);

/* Creates a webpage by readling the lines of a file created by crawler*/
webpage_t * retrieve_page(FILE * fp);

/* checks if pageDirectory provided to indexer is a valid one*/
bool isCrawlerDirectory(char *dir);

#endif // __PAGEDIR_H
