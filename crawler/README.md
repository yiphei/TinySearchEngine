
# Crawler.c

Yifei Yan April 2017

Crawler is a standalone program that crawls the web and retrieves webpages starting from a “seed” URL. It parses the seed webpage, extracts any embedded URLs, then retrieves each of those pages, recursively, but limiting its exploration to a given “depth”.

## Usage
Crawler follows the following **usage**:  
`./crawler seedURL pageDirectory maxDepth`

* `seedURL`: the initial URL and it must be internal
* `pageDirectory`: pathname for an existing directory in which to write downloaded webpages
* `maxDepth`: non-negative integer representing the maximum crawl depth

**Input**: It takes no input besides those parameters.

**Output**: write each explored page to the `pageDirectory` with a unique document `ID`, wherein * the document id starts at 1 and increments by 1 for each new page, * and the filename is of form `pageDirectory/id`, * and the first line of the file is the URL, * and the second line of the file is the depth, * and the rest of the file is the page content.

## Example Command Lines

* `./crawler http://old-www.cs.dartmouth.edu/~cs50/ data 1`
* `./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters data 1`
* `./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html data 1`
* `./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia data 1`
*  `./crawler http://old-www.cs.dartmouth.edu/~cs50/ data 0`
*  `./crawler http://old-www.cs.dartmouth.edu/~cs50/ data 2`

##Exit Status
0 – success  
1 – invalid number of arguments passed  
2 – `maxDepth` is not an integer  
3 – `pageDirectory` does not exists or it is not writable  
4 – `maxDepth` is a negative integer  
5 – `seedURL` is not a valid URL  
6 – `seedURL` is not an internal URL  
7 – `seedURL` points to a valid server but it is a non-existing page  

## Compilation

To compile, simply `make`.  

To test, simply `make test`.

To clean up, simply `make clean`.
## Assumptions

* assume 100 to be a good size for the hashtable

## "Non"-Assumptions
NA

## Limitations

 * the program wont handle non-internal `seedURL`
