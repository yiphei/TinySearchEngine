# CS50 Lab 6
## Yifei Yan

### Implementation of  'querier.c'



###User Interface

The indexer's only interface with the user is on the command-line; it must always have two arguments.

	querier pageDirectory indexFilename

For example:
	
	$ ./querier test_dir indexFile

###Major data structures

Major data structures include:

* counters of docID and word frequency - this keeps the counter of each words in each file(docID). When the program queries for a word, it pulls the counter of that word from the hashtable of words
* set of URLs (indirectly used by hashtable)
* hashtable of words - this will store the words as key and counters as item
* counterslist – a struct that stores two counters and the intersection/union of the two
* docsArray – a struct that stores an array of docndoes and keeps track of the size of the array
* docnode – a struct that stores the URL, docID, and frequency of the query search in that document


###Modules used

The following modules were used:

* pagedir.h : this module saves the HTML of webpages into a given directory, builds a webpage from an HTML file, checks if `pageDirectory` is a valid directory
* webpage.h : this module provides some operation for creating webpage_t structs and related operations
* index.h : this module provides functions to build, save, and load indexes of words
* file.h : this module provides file operations like reading a word, line, or entire file

###Functional decomposition into modules

1. *main*, which parses arguments, checks for invalid arguments by calling some helper functions, initializes global constants, and calls *load_index* to extract the index of words from `indexFilename`. As long as it is not EOF, it reads input by calling *readInput*. Then, it queries the input by calling *queryInput*. If the query returned a final counter, then it will sort that counter in descending order by calling *sort*. When EOF is reached, then free memories.

2. *readInput*, a function that reads the stdin and break it into an array of words. It first read the stdin as a single string. Then, it parses the string and stores each word into an array by calling *buildQueryArray*. At the end, it prints out the array to the stdout. If a syntax rule was violated, it would return 1. Otherwise, it returns 0. 

3. *buildQueryArray*, a function that takes parses the string and stores the word into an array. It calls *line_getNextWord* to pull the words from the string. It normalizes the word by converting it to lowercase. It also checks for syntax errors. If there is a syntax error, then *re_readInput* is called.

4. *re_readInput*, a function that rereads the input after a syntax error
5.  *line_getNextWord*, a function inspired by *webpage_getNextWord* in the module webpage.h .
6. *queryInput*, a function that searches the query in the index and returns the final counter for the entire query. It keeps track of two counters. The andSum counter is the intersection counter. The orSum counter is the union counter. The function basically loops over every single word in the array. If the word is "and", then that word is ignored. If the word is neither and nor or, then *andSequence* is called to compute the intersection counter. If the word is or, then *orSequence* is called to compute the union counter.
7. *andSequence*, a function that builds the counter of the intersection of two counters. It creates a struct to store the two counters and the intersection counter in it. Then, this struct is passed to *counters_iterate*. The iteration calls the function *intersection* to build the intersection of two counters. 
8. *intersection*. It checks that the docID exists in both counters and then assign the lower counter to the new counter.
9. *orSequence*, function that returns the counter of the union of two counters. It creates a struct to store the two counters and the union counter in it. Then, this struct is passed to *conuters_iterate* twice. The iteration calls the function *sum* to build the unoin of two counters.
10. *sum*. The function basically, for every docID present, set the count as the sum of the two counters.
11. *sort*, a fucntion that sorts the final counter in descending order. It calls *counters_iterate* twice. The first time is to compute the size of the counter. The second time it builds an array of struct docnode. It then prints out the matched documents ranked in descending order.
