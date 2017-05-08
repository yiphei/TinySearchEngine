# CS50 Lab 5
## Yifei Yan

### Testing 'indexer'

To test my **indexer.c** program, I ran the following commands. **indexer.c** makes us of separate modules **pagedir.h**, **index.h**, and **file.h**. For the `pageDirectory` passed to **indexer.c**, I created a directory with some files to test the basic functionalities of the program.

In addition, I also created the **indextest.c** program which loads an index file produced by the indexer and saves it to another file. To compare the files created by **indexer.c** and **indextest.c**, I created a bashscript **indextest.sh** to compare them and see if they are identical.

###Test Run

####1.Test the indexer.c program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.

Testing with invalid number of parameters

	[yiphei@flume ~/cs50/labs/tse/indexer]$ ./indexer asd sdfd sdf
	usage: ./indexer pageDirectory indexFilename
	
Testing with invalid `pageDirectory`
	
	//efsefe is a non-existing directory
	[yiphei@flume ~/cs50/labs/tse/indexer]$ ./indexer efsefe indexFile
	pageDirectory provided is an invalid directory
	
Testing with invalid `indexFilename`
	
	//test_dir is directory
	[yiphei@flume ~/cs50/labs/tse/indexer]$ ./indexer test_dir test_dir
	indexFilename provided is an invalid file
	

####2.Test that the fucntions index_build and index_save of index.h works well and handles boundary cases

For the purpose of this test, I created the `test_dir` directory and created files `1`, `2`, and `.crawler` in it. These files mimic files created by crawler and have the same format as them. I created `test_dir` because it allows me to manually check the output.

The following are the files `1` and `2`

	[yiphei@flume ~/cs50/labs/tse/indexer]$ cd test_dir
	[yiphei@flume ~/cs50/labs/tse/indexer/test_dir]$ ls
	1  2
	[yiphei@flume ~/cs50/labs/tse/indexer/test_dir]$ more 1
	www.google.com
	1
	a hello crab box
	ff444 crabb
	t hello hello crab x 5
	[yiphei@flume ~/cs50/labs/tse/indexer/test_dir]$ more 2
	www.dartmouth.edu
	2
	the box box cRAb CRAB crab an
	
This is the output of *indexer.c*

	[yiphei@flume ~/cs50/labs/tse/indexer]$ ./indexer test_dir indexFile
	[yiphei@flume ~/cs50/labs/tse/indexer]$ more indexFile
	crabb 1 1
	the 2 1
	crab 1 2 2 3
	box 1 1 2 2
	hello 1 3
	
####3.Test indextest.c with various forms of incorrect command-line arguments

Testing with invalid number of parameters

	[yiphei@flume ~/cs50/labs/tse/indexer]$ ./indextest indexFile indexFileTested asd
	usage: ./indextest oldIndexFilename newIndexFilename
	
####4.Test that function load_index of index.h works well

Testing *indextest.c*

	[yiphei@flume ~/cs50/labs/tse/indexer]$ ./indextest indexFile indexFileTested
	[yiphei@flume ~/cs50/labs/tse/indexer]$ more indexFileTested
	box 2 2 1 1
	crabb 1 1
	hello 1 3
	crab 2 3 1 2
	the 2 1

To test that the output of *indextest.c* and *indexer.c* are the same, I run the bash script *indextest.sh*

	[yiphei@flume ~/cs50/labs/tse/indexer]$ ./indextest.sh indexFile indexFileTested
	the two files are the same
	
### Limitations

* didnt test on a big dataset