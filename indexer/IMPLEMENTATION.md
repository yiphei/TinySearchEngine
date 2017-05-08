# CS50 Lab 5
## Yifei Yan

### Implementation of  'indexer.c'



###User Interface

The indexer's only interface with the user is on the command-line; it must always have two arguments.

	indexer pageDirectory indexFilename

For example:
	
	$ indexer test_dir indexFile

###Major data structures

Three helper modules provide data structures:

* counters of docID and word frequency - this keeps the counter of each words in each file(docID). It will be used as the item in the hashtable
* set of URLs (indirectly used by hashtable)
* hashtable of words - this will store the words as key and counters as item


###Modules used

The following modules were used:

* pagedir.h : this module saves the HTML of webpages into a given directory, builds a webpage from an HTML file, checks if `pageDirectory` is a valid directory
* webpage.h : this module provides some operation for creating webpage_t structs and related operations
* index.h : this module provides functions to build, save, and load indexes of words
* file.h : this module provides file operations like reading a word, line, or entire file

###Functional decomposition into modules

1. *main*, which parses arguments, checks for invalid arguments by calling some helper functions, initializes global constants, and calls *index_build* and *index_save*  

2. *index_build*, a function in the index.h module. This function basically build an index of words with counters given a `pageDirectory` created by crawler. The function first opens the first file in `pageDirectory`. While there is always a file to open, retrive the webpage for the current file by calling *retrieve_page*. Then, it calls *webpage_getNextWord* to pull the words out of the html file of the webpage. During the pulling of words, all words with less than tree characters are ignored and all words are converted to lowercase by calling *NormalizeWord*. Then, they are accordingly inserted into the index and the counter is accordingly incremented. When all the words are pulled out, open the next file and repeat the cycle. 

3. *index_save*, a function in the index.h module. This function basically outputs the index built by *index_built* in a formatted way to `indexFilename`. The functions first opens `indexFilename` and iterates through the index by calling the helper function *printWord*. At the end of the iteration, the function would have print one line per word, one word per line, each line provides the word and one or more (docID, count) pairs, in the format word docID count [docID count]…
4. *printWord*, which is a helper function in index.h module that is called by *index_save*. This function prints the word to `indexFilename`, call the helper function *printCounter* , and then prints a new line. 
5. *printCounter*, which is a helper function in index.h module that is called by *printWord*. This function prints the docID and the frequency of the word to `indexFilename`.
6. *retrieve_page*, a function in the pagedir.h module. This function basically build a webpage given a file in `pageDirectory`. It uses *readlinep* (in file.h module) to get the URL and depth of the page, and it uses *readfilep* (in file.h module) to get the HTML of the page.
