# Makefile for 'indexer.c'
#
# Yifei Yan
# source: Makefile for bagtest.c from cs50

PROG = indexer
OBJS = indexer.o ../libcs50/jhash.o ../libcs50/webpage_fetch.o ../libcs50/hashtable.o ../libcs50/set.o ../libcs50/memory.o ../libcs50/webpage.o ../libcs50/counters.o ../libcs50/file.o ../common/pagedir.o ../common/index.o
LIBS = -lm -lcurl

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make

#$(LIB):					# this line contains target: dependency list
#	cp $(LIB)-`uname` $(LIB)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@


indexer.o: indexer.c ../libcs50/hashtable.o ../libcs50/memory.o ../libcs50/set.o ../libcs50/webpage.o ../libcs50/counters.o ../common/pagedir.o ../common/index.o
hashtable.o: ../libcs50/hashtable.h ../libcs50/jhash.h ../libcs50/set.h
set.o: ../libcs50/set.h
file.o: ../libcs50/file.h
counters.o : ../libcs50/counters.h
webpage.o: ../libcs50/webpage.h ../libcs50/webpage_internal.h
webpage_fetch.o: ../libcs50/webpage.h ../libcs50/webpage_internal.h ../libcs50/webpage_fetch.c
jhash.o: ../libcs50/jhash.h
memory.o: ../libcs50/memory.h
pagedir.o: ../common/pagedir.h ../libcs50/webpage.h../libcs50/file.h
index.o: ../common/index.h ../libcs50/webpage.h ../libcs50/webpage_internal.h ../libcs50/hashtable.h ../libcs50/jhash.h ../libcs50/set.h ../libcs50/counters.h ../libcs50/file.h

.PHONY: test clean

test: $(PROG)
	./$(PROG) ../crawler/data2 hello

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)



#./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/ data 1
