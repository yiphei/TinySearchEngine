# CS50 Lab 5
## Yifei Yan

### Testing 'querier'

To test my **querier.c** program, I ran the following commands. **querier.c** makes us of separate modules **pagedir.h**, **index. h**, and **file.h**. For the `pageDirectory` passed to **indexer.c**, I used `~cs50/data/tse-output/cs50-3`, and for `indexFilename`, I used `~cs50/data/tse-output/cs50-index3`


###Test Run

####1.Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.

Testing with invalid number of parameters

	[yiphei@flume ~/cs50/labs/tse/querier]$ ./querier ~cs50/data/tse-output/cs50-3 ~cs50/data/tse-output/cs50-index3 asda
	./querier pageDirectory indexFilename
	
Testing with invalid `pageDirectory`
	
	[yiphei@flume ~/cs50/labs/tse/querier]$ ./querier ~cs50/data/tse-AAAAAAut/cs50-3 ~cs50/data/tse-output/cs50-index3
	pageDirectory provided is an invalid directory
	
Testing with invalid `indexFilename`
	
	[yiphei@flume ~/cs50/labs/tse/querier]$ ./querier ~cs50/data/tse-output/cs50-3 ~cs50/data/tse-output/cs50-OOOOOOO
	indexFilename provided is an invalid file
	

####2.Test that program handles syntax errors

	./querier ~cs50/data/tse-output/cs50-3 ~cs50/data/tse-output/cs50-index3
	KEY WORDs:> 
	Line is empty. Please write something
	KEY WORDs:> and hello
	the literal ‘and’ must come between words, and the literal ‘or’ must come between andsequences. They cannot appear at the beginning or end of a query
	KEY WORDs:> hwllo and or se
	The literals (‘and’ & ‘or’) cannot be adjacent
	KEY WORDs:> hello and
	the literal ‘and’ must come between words, and the literal ‘or’ must come between andsequences. They cannot appear at the beginning or end of a query
	KEY WORDs:> sf 8 d
	Characters other than letters or spaces are disallowed
	
####3.Test program produces valid result (please check ~cs50/data/tse-output/queries.txt for reference)


	./querier ~cs50/data/tse-output/cs50-3 ~cs50/data/tse-output/cs50-index3
	KEY WORDs:> aslam
	Query: aslam 
	One
	AA
	in And
	BB
	two
	Matched 10 documents(ranked):
	Score:  7  doc:  19: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	Score:  6  doc:  349: http://old-www.cs.dartmouth.edu/~dfk/papers/index-t.html
	Score:  6  doc:  348: http://old-www.cs.dartmouth.edu/~dfk/papers/index-a.html
	Score:  6  doc:  347: http://old-www.cs.dartmouth.edu/~dfk/papers/index-c.html
	Score:  4  doc:  244: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/aslam-toolkit.html
	Score:  3  doc:  246: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/aslam-kerf-news.html
	Score:  3  doc:  243: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/aslam-toolkit-tr.html
	Score:  3  doc:  242: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/aslam-toolkit-p.html
	Score:  2  doc:  245: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/aslam-kerf-WIP.html
	Score:  2  doc:  149: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/aslam-position.html
	
	
	KEY WORDs:> vesta and parallel or wanda and amulet
	Query: vesta and parallel or wanda and amulet 
	Matched 6 documents(ranked):
	Score:  7  doc:  105: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/carter-vesta.html
	Score:  4  doc:  349: http://old-www.cs.dartmouth.edu/~dfk/papers/index-t.html
	Score:  4  doc:  348: http://old-www.cs.dartmouth.edu/~dfk/papers/index-a.html
	Score:  4  doc:  347: http://old-www.cs.dartmouth.edu/~dfk/papers/index-c.html
	Score:  4  doc:  19: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	Score:  1  doc:  10: http://old-www.cs.dartmouth.edu/~dfk/nils/galley.html
	
	
	
	KEY WORDs:> guanling and solar or guanling and agents
	Query: guanling and solar or guanling and agents 
	Matched 15 documents(ranked):
	Score:  43  doc:  19: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	Score:  30  doc:  349: http://old-www.cs.dartmouth.edu/~dfk/papers/index-t.html
	Score:  30  doc:  348: http://old-www.cs.dartmouth.edu/~dfk/papers/index-a.html
	Score:  30  doc:  347: http://old-www.cs.dartmouth.edu/~dfk/papers/index-c.html
	Score:  4  doc:  9: http://old-www.cs.dartmouth.edu/~dfk/people.html
	Score:  2  doc:  258: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/chen-thesis.html
	Score:  1  doc:  269: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/chen-jsolar.html
	Score:  1  doc:  260: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/chen-fusenet.html
	Score:  1  doc:  254: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/chen-naming.html
	Score:  1  doc:  253: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/chen-abstraction.html
	Score:  1  doc:  252: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/chen-abstraction-tr.html
	Score:  1  doc:  251: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/chen-pervasive.html
	Score:  1  doc:  250: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/chen-pervasive-tr.html
	Score:  1  doc:  249: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/chen-solar.html
	Score:  1  doc:  248: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/chen-solar-tr.html