# Makefile for 'crawler.c'
#
# Yifei Yan
# source: Makefile for bagtest.c from cs50

PROG = crawler
OBJS = crawler.o ../libcs50/jhash.o ../libcs50/webpage_fetch.o ../libcs50/hashtable.o ../libcs50/set.o ../libcs50/memory.o ../libcs50/webpage.o ../libcs50/bag.o ../common/pagedir.o ../libcs50/file.o
LIBS = -lm -lcurl

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

crawler.o: crawler.c ../libcs50/hashtable.o ../libcs50/memory.o ../libcs50/set.o ../libcs50/webpage.o ../libcs50/bag.o ../common/pagedir.o
hashtable.o: ../libcs50/hashtable.h ../libcs50/jhash.h ../libcs50/set.h
set.o: ../libcs50/set.h
bag.o: ../libcs50/bag.h
webpage.o: ../libcs50/webpage.h ../libcs50/webpage_internal.h
webpage_fetch.o: ../libcs50/webpage.h ../libcs50/webpage_internal.h ../libcs50/webpage_fetch.c
jhash.o: ../libcs50/jhash.h
memory.o: ../libcs50/memory.h
pagedir.o: ../common/pagedir.h ../libcs50/webpage.h ../libcs50/file.h
file.o: ../libcs50/file.h

.PHONY: test clean

test: $(PROG)
	./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/ data 1

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)



#./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/ data 1
