# CS50 Lab 4
## Yifei Yan

### Implementation of  'crawler.c'



###User Interface

The crawler’s only interface with the user is on the command-line; it must always have three arguments.

	crawler seedURL pageDirectory maxDepth

For example:
	
	$ crawler http://old-www.cs.dartmouth.edu/index.html ./data/ 2

###Major data structures

Three helper modules provide data structures:

* bag of page (URL, depth) structures - this will keep track of webpages that still need to be visited
* set of URLs (indirectly used by hashtable)
* hashtable of URLs - this will keep track of webpages already visited


###Modules used

The following modules were used:

* pagedir.h : this module saves the HTML of webpages into a given directory
* webpage.h : this module provides some operation for creating webpage_t structs and related operations

###Functional decomposition into modules

1. *main*, which parses arguments, checks for invalid arguments by calling some helper functions, initializes global constants, and calls *crawler*
2. *crawler*, which initializes a bag (this will keep track of webpages that still need to be visisted), a hashtable (this will keep track of webpages already visisted), a webpage_t struct for seedURL (initialized to `depth` of 0 and `html` to NULL), and a counter starting from one (which will be used as the filename where the html of a webpage will be stored). It then goes on a while loop that calls *isBagEmpty*. As long as the bag is not empty, the loop will continue. In the loop, it calls *crawlPage*.
3. *crawlPage*, which takes a hashtable, a bag, and a fileID as paramenters. It first tries to extract a webpage from bag and tries to fetch the HTML of it. If the fetching is successful, then it will call *pageSaver* to save the html of the webpage in the directory. If not successful, then it ignores *pageSaver*. Then, as long as the depth of the extracted webpage is less than `maxDepth`, it will try to search for other URLs in the extracted page by using the function *webpage_getNextURL*. Once an URL is found, then *checkPage* is called to check if the URL found is valid. 
4. *checkPage*, which takes a bag, a hashtable, a webpage, and the found URL as parameters. It calls *NormalizeURL* and *IsInternalURL* to check that the found URL is a valid URL and an Internal URL. It then tries to insert it into the hashtable. If the insertion is successful, a new webpage is created and is inserted into the bag.
5. *directoryCheck*, which checks that the `pageDirectory` given is a writable one. It creates a filename `pageDirectory/.crawler` and tries to open it as a file. This is called by *main* to check parameters
6. *isNumber*, which checks that `maxDepth`is an integer. This is called by *main* to check parameters
7. *checkSeedURL*, which check that a URL pointing to a valid server is a existing URL. This is called by *main* to check parameters
8. *isBagEmpty*, which checks that the bag is empty. This is called by *crawler*
