# CS50 Lab 4
## Yifei Yan

### Testing 'crawler.c'

To test my **crawler.c** program, I ran the following commands. **crawler.c** makes us of a separate module **pagedir.h** that helps saving the html of the webpages.

###Test Run

####1.Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.

Testing with invalid number of parameters

	//5 parameters passed
	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html data 1 a
	usage: ./crawler seedURL pageDirectory maxDepth
	//1 parameter passed
	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler aaa
	usage: ./crawler seedURL pageDirectory maxDepth
	
Testing with invalid and non-internal `seedURL`

	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler dartmouth.edu/~cs50/index.html data 1
	invalid seedURL
	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://www.youtube.com data 1
	seedURL is not internal
	
Testing with invalid `pageDirectory`

	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/ datasssss 1
	Invalid pageDirectory
	
Testing with invalid and negative `maxDepth`

	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/ data one
	maxDepth must be an integer
	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/ data -5
	maxDepth cannot be a negative value


####2.Test the crawler with a seedURL that points to a valid server but non-existent page.

	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/helloworld/index.html data 2
	seedURL points to a valid server but it is a non-existing page
	
####3.Point the crawler at a page in that site, and explore at depths 0, 1, 2, 3, 4.

Exploring at `maxDepth` of 0

	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html data 0
	DEPTH:0  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/index.html
	DEPTH:0  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/index.html
	[yiphei@flume ~/cs50/labs/tse/crawler]$ cd data
	[yiphei@flume ~/cs50/labs/tse/crawler/data]$ head -3 1
	http://old-www.cs.dartmouth.edu/~cs50/index.html
	0
	<!DOCTYPE html>
	
Exploring at `maxDepth` of 1

	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html data 1
	DEPTH:0  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/index.html
	DEPTH:0  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/index.html
	DEPTH:0  SCANNING Url: http://old-www.cs.dartmouth.edu/~cs50/index.html
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:0  FOUND Url: https://canvas.dartmouth.edu/courses/14815
	DEPTH:0  IGNORED Url: https://canvas.dartmouth.edu/courses/14815
	DEPTH:0  FOUND Url: https://piazza.com/dartmouth/spring2017/cosc050sp17/home
	DEPTH:0  IGNORED Url: https://piazza.com/dartmouth/spring2017/cosc050sp17/home
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/Schedule.pdf
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/Schedule.pdf
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Logistics/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Logistics/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Lectures/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Lectures/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Reading/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Reading/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/examples/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/examples/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Sections/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Sections/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Labs/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Labs/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Labs/Project/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Labs/Project/
	DEPTH:0  FOUND Url: https://gitlab.cs.dartmouth.edu
	DEPTH:0  IGNORED Url: https://gitlab.cs.dartmouth.edu
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Resources/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Resources/
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/
	[yiphei@flume ~/cs50/labs/tse/crawler]$ cd data
	[yiphei@flume ~/cs50/labs/tse/crawler/data]$ ls
	1  2  3
	[yiphei@flume ~/cs50/labs/tse/crawler/data]$ head -3 1
	http://old-www.cs.dartmouth.edu/~cs50/index.html
	0
	<!DOCTYPE html>
	[yiphei@flume ~/cs50/labs/tse/crawler/data]$ head -3 2
	http://old-www.cs.dartmouth.edu/~dfk/
	1
	<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
	[yiphei@flume ~/cs50/labs/tse/crawler/data]$ head -3 3
	http://old-www.cs.dartmouth.edu/~cs50/
	1
	<!DOCTYPE html>
	
	
Exploring at `maxDepth` of 2

	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html test1 2  
	DEPTH:0  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/index.html
	DEPTH:0  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/index.html
	DEPTH:0  SCANNING Url: http://old-www.cs.dartmouth.edu/~cs50/index.html
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:0  FOUND Url: https://canvas.dartmouth.edu/courses/14815
	DEPTH:0  IGNORED Url: https://canvas.dartmouth.edu/courses/14815
	DEPTH:0  FOUND Url: https://piazza.com/dartmouth/spring2017/cosc050sp17/home
	DEPTH:0  IGNORED Url: https://piazza.com/dartmouth/spring2017/cosc050sp17/home
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/Schedule.pdf
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/Schedule.pdf
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Logistics/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Logistics/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Lectures/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Lectures/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Reading/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Reading/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/examples/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/examples/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Sections/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Sections/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Labs/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Labs/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Labs/Project/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Labs/Project/
	DEPTH:0  FOUND Url: https://gitlab.cs.dartmouth.edu
	DEPTH:0  IGNORED Url: https://gitlab.cs.dartmouth.edu
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Resources/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Resources/
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:1  SCANNING Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/ChampionInternationalProfessor.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/ChampionInternationalProfessor.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/ChampionInternationalProfessor.html
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/
	DEPTH:1  FOUND Url: http://www.dartmouth.edu/
	DEPTH:1  IGNORED Url: http://www.dartmouth.edu/
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/papers/wordle.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/wordle.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/wordle.html
	DEPTH:1  FOUND Url: http://www.wordle.net/
	DEPTH:1  IGNORED Url: http://www.wordle.net/
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/vita.pdf
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/vita.pdf
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/bio-dfk.txt
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/bio-dfk.txt
	DEPTH:1  FOUND Url: http://scholar.google.com/citations?user=w_Q7iBoAAAAJ
	DEPTH:1  IGNORED Url: http://scholar.google.com/citations?user=w_Q7iBoAAAAJ
	DEPTH:1  FOUND Url: http://orcid.org/0000-0001-7411-2783
	DEPTH:1  IGNORED Url: http://orcid.org/0000-0001-7411-2783
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/people.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/people.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/people.html
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/teaching.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/teaching.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/teaching.html
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/postdoc.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/postdoc.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/postdoc.html
	DEPTH:1  FOUND Url: http://web.cs.dartmouth.edu/news-events/research-programmer-position-available-david-kotzs-team
	DEPTH:1  IGNORED Url: http://web.cs.dartmouth.edu/news-events/research-programmer-position-available-david-kotzs-team
	DEPTH:1  FOUND Url: http://c4tbh.org
	DEPTH:1  IGNORED Url: http://c4tbh.org
	DEPTH:1  FOUND Url: http://www.ists.dartmouth.edu
	DEPTH:1  IGNORED Url: http://www.ists.dartmouth.edu
	DEPTH:1  FOUND Url: http://youtu.be/ngPflO_uyVo
	DEPTH:1  IGNORED Url: http://youtu.be/ngPflO_uyVo
	DEPTH:1  FOUND Url: http://thaw.org
	DEPTH:1  IGNORED Url: http://thaw.org
	DEPTH:1  FOUND Url: http://amulet-project.org
	DEPTH:1  IGNORED Url: http://amulet-project.org
	DEPTH:1  FOUND Url: https://www.youtube.com/watch?v=RmI3Pq1Z8Cs
	DEPTH:1  IGNORED Url: https://www.youtube.com/watch?v=RmI3Pq1Z8Cs
	DEPTH:1  FOUND Url: http://auracle-project.org
	DEPTH:1  IGNORED Url: http://auracle-project.org
	DEPTH:1  FOUND Url: http://www.healthit.gov/FACAS/health-it-policy-committee
	DEPTH:1  IGNORED Url: http://www.healthit.gov/FACAS/health-it-policy-committee
	DEPTH:1  FOUND Url: http://www.pbk.org/
	DEPTH:1  IGNORED Url: http://www.pbk.org/
	DEPTH:1  FOUND Url: http://www.ieee.org/web/membership/fellows/index.html
	DEPTH:1  IGNORED Url: http://www.ieee.org/web/membership/fellows/index.html
	DEPTH:1  FOUND Url: http://www.computer.org
	DEPTH:1  IGNORED Url: http://www.computer.org
	DEPTH:1  FOUND Url: http://www.acm.org
	DEPTH:1  IGNORED Url: http://www.acm.org
	DEPTH:1  FOUND Url: http://www.usenix.org/
	DEPTH:1  IGNORED Url: http://www.usenix.org/
	DEPTH:1  FOUND Url: http://www.cs.duke.edu/
	DEPTH:1  IGNORED Url: http://www.cs.duke.edu/
	DEPTH:1  FOUND Url: http://www.dartmouth.edu/
	DEPTH:1  IGNORED Url: http://www.dartmouth.edu/
	DEPTH:1  FOUND Url: http://www.alum.dartmouth.org/classes/86/
	DEPTH:1  IGNORED Url: http://www.alum.dartmouth.org/classes/86/
	DEPTH:1  FOUND Url: http://www.choate.edu/
	DEPTH:1  IGNORED Url: http://www.choate.edu/
	DEPTH:1  FOUND Url: http://photos.davidkotz.org/
	DEPTH:1  IGNORED Url: http://photos.davidkotz.org/
	DEPTH:1  FOUND Url: http://davidkotz.org/
	DEPTH:1  IGNORED Url: http://davidkotz.org/
	DEPTH:1  FOUND Url: http://www.cs.dartmouth.edu/~dfk/blog/
	DEPTH:1  IGNORED Url: http://www.cs.dartmouth.edu/~dfk/blog/
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/kids.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/kids.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/kids.html
	DEPTH:1  FOUND Url: https://www.facebook.com/david.kotz.37
	DEPTH:1  IGNORED Url: https://www.facebook.com/david.kotz.37
	DEPTH:1  FOUND Url: http://www.crossroadsacademy.org
	DEPTH:1  IGNORED Url: http://www.crossroadsacademy.org
	DEPTH:1  FOUND Url: http://www.cies.org/US_scholars/
	DEPTH:1  IGNORED Url: http://www.cies.org/US_scholars/
	DEPTH:1  FOUND Url: http://www.cs.dartmouth.edu/~dfk/blog/Travel/India.html
	DEPTH:1  IGNORED Url: http://www.cs.dartmouth.edu/~dfk/blog/Travel/India.html
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/seatpack/
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/seatpack/
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/seatpack/
	DEPTH:1  FOUND Url: http://dfkotz.smugmug.com/House/Construction
	DEPTH:1  IGNORED Url: http://dfkotz.smugmug.com/House/Construction
	DEPTH:1  FOUND Url: http://dfkotz.smugmug.com/House/Projects/1998-Deck
	DEPTH:1  IGNORED Url: http://dfkotz.smugmug.com/House/Projects/1998-Deck
	DEPTH:1  FOUND Url: http://dfkotz.smugmug.com/House/2000-Addition
	DEPTH:1  IGNORED Url: http://dfkotz.smugmug.com/House/2000-Addition
	DEPTH:1  FOUND Url: http://dfkotz.smugmug.com/House/Projects/2005-Patio
	DEPTH:1  IGNORED Url: http://dfkotz.smugmug.com/House/Projects/2005-Patio
	DEPTH:1  FOUND Url: http://dfkotz.smugmug.com/House/Projects/2006-Walls
	DEPTH:1  IGNORED Url: http://dfkotz.smugmug.com/House/Projects/2006-Walls
	DEPTH:1  FOUND Url: http://dfkotz.smugmug.com/House/Projects/2006-Riverbank
	DEPTH:1  IGNORED Url: http://dfkotz.smugmug.com/House/Projects/2006-Riverbank
	DEPTH:1  FOUND Url: http://dfkotz.smugmug.com/House/Projects/2007-Boatshed
	DEPTH:1  IGNORED Url: http://dfkotz.smugmug.com/House/Projects/2007-Boatshed
	DEPTH:1  FOUND Url: http://where
	DEPTH:1  IGNORED Url: http://where
	DEPTH:1  FOUND Url: http://www.gnuplot.info
	DEPTH:1  IGNORED Url: http://www.gnuplot.info
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/photos/Kotz-old/Kotz-PDP11e.jpg
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/photos/Kotz-old/Kotz-PDP11e.jpg
	DEPTH:1  FOUND Url: http://www.choate.edu/
	DEPTH:1  IGNORED Url: http://www.choate.edu/
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/Kotz.vcf
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/Kotz.vcf
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/visit-dartmouth.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/visit-dartmouth.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/visit-dartmouth.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/visit-dartmouth.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/visit-dartmouth.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/seatpack/
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/seatpack/
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/kids.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/kids.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/postdoc.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/postdoc.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/teaching.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/teaching.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/people.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/people.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/wordle.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/wordle.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/ChampionInternationalProfessor.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/ChampionInternationalProfessor.html
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:1  SCANNING Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/
	DEPTH:1  FOUND Url: https://canvas.dartmouth.edu/courses/14815
	DEPTH:1  IGNORED Url: https://canvas.dartmouth.edu/courses/14815
	DEPTH:1  FOUND Url: https://piazza.com/dartmouth/spring2017/cosc050sp17/home
	DEPTH:1  IGNORED Url: https://piazza.com/dartmouth/spring2017/cosc050sp17/home
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/Schedule.pdf
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/Schedule.pdf
	DEPTH:1  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Logistics/
	DEPTH:1  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Logistics/
	DEPTH:1  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Lectures/
	DEPTH:1  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Lectures/
	DEPTH:1  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Reading/
	DEPTH:1  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Reading/
	DEPTH:1  FOUND Url: http://www.cs.dartmouth.edu/~cs50/examples/
	DEPTH:1  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/examples/
	DEPTH:1  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Sections/
	DEPTH:1  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Sections/
	DEPTH:1  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Labs/
	DEPTH:1  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Labs/
	DEPTH:1  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Labs/Project/
	DEPTH:1  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Labs/Project/
	DEPTH:1  FOUND Url: https://gitlab.cs.dartmouth.edu
	DEPTH:1  IGNORED Url: https://gitlab.cs.dartmouth.edu
	DEPTH:1  FOUND Url: http://www.cs.dartmouth.edu/~cs50/Resources/
	DEPTH:1  IGNORED Url: http://www.cs.dartmouth.edu/~cs50/Resources/
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/
	//the output is saved in test1. please check that directory for output
	[yiphei@flume ~/cs50/labs/tse/crawler]$ cd test1
	[yiphei@flume ~/cs50/labs/tse/crawler/test1]$ ls
	1  10  11  12  13  2  3  4  5  6  7  8	9
	
Exploring at `maxDepth` of 3 (debugging statements will be omitted because there is not enough space)
	
	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html test2 3
	//the output is saved in test2. please check that directory for output
	[yiphei@flume ~/cs50/labs/tse/crawler]$ cd test2
	[yiphei@flume ~/cs50/labs/tse/crawler/test2]$ ls
	1    116  133  150  168  185  201  219	236  253  270  288  304  321  339  37  54  71  89
	10   117  134  151  169  186  202  22	237  254  271  289  305  322  34   38  55  72  9
	100  118  135  152  17	 187  203  220	238  255  272  29   306  323  340  39  56  73  90
	101  119  136  153  170  188  204  221	239  256  273  290  307  324  341  4   57  74  91
	102  12   137  154  171  189  205  222	24   257  274  291  308  325  342  40  58  75  92
	103  120  138  155  172  19   206  223	240  258  275  292  309  326  343  41  59  76  93
	104  121  139  156  173  190  207  224	241  259  276  293  31	 327  344  42  6   77  94
	105  122  14   157  174  191  208  225	242  26   277  294  310  328  345  43  60  78  95
	106  123  140  158  175  192  209  226	243  260  278  295  311  329  346  44  61  79  96
	107  124  141  159  176  193  21   227	244  261  279  296  312  33   347  45  62  8   97
	108  125  142  16   177  194  210  228	245  262  28   297  313  330  348  46  63  80  98
	109  126  143  160  178  195  211  229	246  263  280  298  314  331  349  47  64  81  99
	11   127  144  161  179  196  212  23	247  264  281  299  315  332  35   48  65  82
	110  128  145  162  18	 197  213  230	248  265  282  3    316  333  350  49  66  83
	111  129  146  163  180  198  214  231	249  266  283  30   317  334  351  5   67  84
	112  13   147  164  181  199  215  232	25   267  284  300  318  335  352  50  68  85
	113  130  148  165  182  2    216  233	250  268  285  301  319  336  353  51  69  86
	114  131  149  166  183  20   217  234	251  269  286  302  32	 337  354  52  7   87
	115  132  15   167  184  200  218  235	252  27   287  303  320  338  36   53  70  88
	
	
Exploring at `maxDepth` of 4 (debugging statements will be omitted because there is not enough space)

	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html test3 4
	//the output is saved in test3. please check that directory for output
	[yiphei@flume ~/cs50/labs/tse/crawler]$ cd test3
	[yiphei@flume ~/cs50/labs/tse/crawler/test3]$ ls
	1    117  135  153  171  19   207  225	243  261  28   298  315  333  351  37	45  63	81
	10   118  136  154  172  190  208  226	244  262  280  299  316  334  352  370	46  64	82
	100  119  137  155  173  191  209  227	245  263  281  3    317  335  353  371	47  65	83
	101  12   138  156  174  192  21   228	246  264  282  30   318  336  354  372	48  66	84
	102  120  139  157  175  193  210  229	247  265  283  300  319  337  355  373	49  67	85
	103  121  14   158  176  194  211  23	248  266  284  301  32	 338  356  374	5   68	86
	104  122  140  159  177  195  212  230	249  267  285  302  320  339  357  375	50  69	87
	105  123  141  16   178  196  213  231	25   268  286  303  321  34   358  376	51  7	88
	106  124  142  160  179  197  214  232	250  269  287  304  322  340  359  377	52  70	89
	107  125  143  161  18	 198  215  233	251  27   288  305  323  341  36   378	53  71	9
	108  126  144  162  180  199  216  234	252  270  289  306  324  342  360  379	54  72	90
	109  127  145  163  181  2    217  235	253  271  29   307  325  343  361  38	55  73	91
	11   128  146  164  182  20   218  236	254  272  290  308  326  344  362  380	56  74	92
	110  129  147  165  183  200  219  237	255  273  291  309  327  345  363  39	57  75	93
	111  13   148  166  184  201  22   238	256  274  292  31   328  346  364  4	58  76	94
	112  130  149  167  185  202  220  239	257  275  293  310  329  347  365  40	59  77	95
	113  131  15   168  186  203  221  24	258  276  294  311  33	 348  366  41	6   78	96
	114  132  150  169  187  204  222  240	259  277  295  312  330  349  367  42	60  79	97
	115  133  151  17   188  205  223  241	26   278  296  313  331  35   368  43	61  8	98
	116  134  152  170  189  206  224  242	260  279  297  314  332  350  369  44	62  80	99


####4.Repeat with a different seed page in that same site.


	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~dfk/ test4 1
	DEPTH:0  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:0  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:0  SCANNING Url: http://old-www.cs.dartmouth.edu/~dfk/
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/ChampionInternationalProfessor.html
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/ChampionInternationalProfessor.html
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/ChampionInternationalProfessor.html
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/
	DEPTH:0  FOUND Url: http://www.dartmouth.edu/
	DEPTH:0  IGNORED Url: http://www.dartmouth.edu/
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/papers/wordle.html
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/wordle.html
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/wordle.html
	DEPTH:0  FOUND Url: http://www.wordle.net/
	DEPTH:0  IGNORED Url: http://www.wordle.net/
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/vita.pdf
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/vita.pdf
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/bio-dfk.txt
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/bio-dfk.txt
	DEPTH:0  FOUND Url: http://scholar.google.com/citations?user=w_Q7iBoAAAAJ
	DEPTH:0  IGNORED Url: http://scholar.google.com/citations?user=w_Q7iBoAAAAJ
	DEPTH:0  FOUND Url: http://orcid.org/0000-0001-7411-2783
	DEPTH:0  IGNORED Url: http://orcid.org/0000-0001-7411-2783
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/people.html
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/people.html
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/people.html
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/teaching.html
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/teaching.html
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/teaching.html
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/postdoc.html
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/postdoc.html
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/postdoc.html
	DEPTH:0  FOUND Url: http://web.cs.dartmouth.edu/news-events/research-programmer-position-available-david-kotzs-team
	DEPTH:0  IGNORED Url: http://web.cs.dartmouth.edu/news-events/research-programmer-position-available-david-kotzs-team
	DEPTH:0  FOUND Url: http://c4tbh.org
	DEPTH:0  IGNORED Url: http://c4tbh.org
	DEPTH:0  FOUND Url: http://www.ists.dartmouth.edu
	DEPTH:0  IGNORED Url: http://www.ists.dartmouth.edu
	DEPTH:0  FOUND Url: http://youtu.be/ngPflO_uyVo
	DEPTH:0  IGNORED Url: http://youtu.be/ngPflO_uyVo
	DEPTH:0  FOUND Url: http://thaw.org
	DEPTH:0  IGNORED Url: http://thaw.org
	DEPTH:0  FOUND Url: http://amulet-project.org
	DEPTH:0  IGNORED Url: http://amulet-project.org
	DEPTH:0  FOUND Url: https://www.youtube.com/watch?v=RmI3Pq1Z8Cs
	DEPTH:0  IGNORED Url: https://www.youtube.com/watch?v=RmI3Pq1Z8Cs
	DEPTH:0  FOUND Url: http://auracle-project.org
	DEPTH:0  IGNORED Url: http://auracle-project.org
	DEPTH:0  FOUND Url: http://www.healthit.gov/FACAS/health-it-policy-committee
	DEPTH:0  IGNORED Url: http://www.healthit.gov/FACAS/health-it-policy-committee
	DEPTH:0  FOUND Url: http://www.pbk.org/
	DEPTH:0  IGNORED Url: http://www.pbk.org/
	DEPTH:0  FOUND Url: http://www.ieee.org/web/membership/fellows/index.html
	DEPTH:0  IGNORED Url: http://www.ieee.org/web/membership/fellows/index.html
	DEPTH:0  FOUND Url: http://www.computer.org
	DEPTH:0  IGNORED Url: http://www.computer.org
	DEPTH:0  FOUND Url: http://www.acm.org
	DEPTH:0  IGNORED Url: http://www.acm.org
	DEPTH:0  FOUND Url: http://www.usenix.org/
	DEPTH:0  IGNORED Url: http://www.usenix.org/
	DEPTH:0  FOUND Url: http://www.cs.duke.edu/
	DEPTH:0  IGNORED Url: http://www.cs.duke.edu/
	DEPTH:0  FOUND Url: http://www.dartmouth.edu/
	DEPTH:0  IGNORED Url: http://www.dartmouth.edu/
	DEPTH:0  FOUND Url: http://www.alum.dartmouth.org/classes/86/
	DEPTH:0  IGNORED Url: http://www.alum.dartmouth.org/classes/86/
	DEPTH:0  FOUND Url: http://www.choate.edu/
	DEPTH:0  IGNORED Url: http://www.choate.edu/
	DEPTH:0  FOUND Url: http://photos.davidkotz.org/
	DEPTH:0  IGNORED Url: http://photos.davidkotz.org/
	DEPTH:0  FOUND Url: http://davidkotz.org/
	DEPTH:0  IGNORED Url: http://davidkotz.org/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~dfk/blog/
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~dfk/blog/
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/kids.html
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/kids.html
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/kids.html
	DEPTH:0  FOUND Url: https://www.facebook.com/david.kotz.37
	DEPTH:0  IGNORED Url: https://www.facebook.com/david.kotz.37
	DEPTH:0  FOUND Url: http://www.crossroadsacademy.org
	DEPTH:0  IGNORED Url: http://www.crossroadsacademy.org
	DEPTH:0  FOUND Url: http://www.cies.org/US_scholars/
	DEPTH:0  IGNORED Url: http://www.cies.org/US_scholars/
	DEPTH:0  FOUND Url: http://www.cs.dartmouth.edu/~dfk/blog/Travel/India.html
	DEPTH:0  IGNORED Url: http://www.cs.dartmouth.edu/~dfk/blog/Travel/India.html
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/seatpack/
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/seatpack/
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/seatpack/
	DEPTH:0  FOUND Url: http://dfkotz.smugmug.com/House/Construction
	DEPTH:0  IGNORED Url: http://dfkotz.smugmug.com/House/Construction
	DEPTH:0  FOUND Url: http://dfkotz.smugmug.com/House/Projects/1998-Deck
	DEPTH:0  IGNORED Url: http://dfkotz.smugmug.com/House/Projects/1998-Deck
	DEPTH:0  FOUND Url: http://dfkotz.smugmug.com/House/2000-Addition
	DEPTH:0  IGNORED Url: http://dfkotz.smugmug.com/House/2000-Addition
	DEPTH:0  FOUND Url: http://dfkotz.smugmug.com/House/Projects/2005-Patio
	DEPTH:0  IGNORED Url: http://dfkotz.smugmug.com/House/Projects/2005-Patio
	DEPTH:0  FOUND Url: http://dfkotz.smugmug.com/House/Projects/2006-Walls
	DEPTH:0  IGNORED Url: http://dfkotz.smugmug.com/House/Projects/2006-Walls
	DEPTH:0  FOUND Url: http://dfkotz.smugmug.com/House/Projects/2006-Riverbank
	DEPTH:0  IGNORED Url: http://dfkotz.smugmug.com/House/Projects/2006-Riverbank
	DEPTH:0  FOUND Url: http://dfkotz.smugmug.com/House/Projects/2007-Boatshed
	DEPTH:0  IGNORED Url: http://dfkotz.smugmug.com/House/Projects/2007-Boatshed
	DEPTH:0  FOUND Url: http://where
	DEPTH:0  IGNORED Url: http://where
	DEPTH:0  FOUND Url: http://www.gnuplot.info
	DEPTH:0  IGNORED Url: http://www.gnuplot.info
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/photos/Kotz-old/Kotz-PDP11e.jpg
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/photos/Kotz-old/Kotz-PDP11e.jpg
	DEPTH:0  FOUND Url: http://www.choate.edu/
	DEPTH:0  IGNORED Url: http://www.choate.edu/
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/Kotz.vcf
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/Kotz.vcf
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~dfk/visit-dartmouth.html
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~dfk/visit-dartmouth.html
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~dfk/visit-dartmouth.html
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/visit-dartmouth.html
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/visit-dartmouth.html
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/seatpack/
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/seatpack/
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/kids.html
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/kids.html
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/postdoc.html
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/postdoc.html
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/teaching.html
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/teaching.html
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/people.html
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/people.html
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/wordle.html
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/papers/wordle.html
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~dfk/ChampionInternationalProfessor.html
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~dfk/ChampionInternationalProfessor.html
	[yiphei@flume ~/cs50/labs/tse/crawler]$ cd test4
	[yiphei@flume ~/cs50/labs/tse/crawler/test4]$ ls
	1  10  11  2  3  4  5  6  7  8	9


####5.Point the crawler at our Wikipedia playground. Explore at depths 0, 1, 2.

Exploring Wikipedia playground at `maxDepth` of 0

	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia wiki0 0
	DEPTH:0  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia
	DEPTH:0  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia
	[yiphei@flume ~/cs50/labs/tse/crawler]$ cd wiki0
	[yiphei@flume ~/cs50/labs/tse/crawler/wiki0]$ ls
	1
	[yiphei@flume ~/cs50/labs/tse/crawler/wiki0]$ head -3 1
	http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia
	0
	<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
	
Exploring Wikipedia playground at `maxDepth` of 1

	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia wiki1 1
	DEPTH:0  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia
	DEPTH:0  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia
	DEPTH:0  SCANNING Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	[yiphei@flume ~/cs50/labs/tse/crawler]$ cd wiki1
	[yiphei@flume ~/cs50/labs/tse/crawler/wiki1]$ ls
	1  2
	[yiphei@flume ~/cs50/labs/tse/crawler/wiki1]$ head -3 1
	http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia
	0
	<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
	[yiphei@flume ~/cs50/labs/tse/crawler/wiki1]$ head -3 2
	http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	1
	<!-- Note: Template file not found, using internal one -->
	
Exploring Wikipedia playground at `maxDepth` of 2

	[yiphei@flume ~/cs50/labs/tse/crawler]$ ./crawler http://old-www.cs.dartmouth.edu/	~cs50/data/tse/wikipedia wiki2 2
	DEPTH:0  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia
	DEPTH:0  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia
	DEPTH:0  SCANNING Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia
	DEPTH:0  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	DEPTH:0  ADDED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	DEPTH:0  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	DEPTH:1  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	DEPTH:1  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	DEPTH:1  SCANNING Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/C_(programming_language).html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/C_(programming_language).html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/C_(programming_language).html
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Unix.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Unix.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Unix.html
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html
	DEPTH:1  FOUND Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
	DEPTH:1  ADDED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
	DEPTH:1  IGNORED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Hash_table.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Unix.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Unix.html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/C_(programming_language).html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/C_(programming_language).html
	DEPTH:2  FETCHED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
	DEPTH:2  SAVED Url: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
	[yiphei@flume ~/cs50/labs/tse/crawler]$ cd wiki2
	[yiphei@flume ~/cs50/labs/tse/crawler/wiki2]$ ls
	1  2  3  4  5  6  7  8

### Limitations

It doesnt test for `maxDepth` over 4.