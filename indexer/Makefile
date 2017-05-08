# Makefile for 'indexer.c'
#
# Yifei Yan
# source: Makefile for bagtest.c from cs50
TEST = indextest
TESTOBJC = indextest.o ../common/pagedir.o ../common/index.o


PROG = indexer
OBJS = indexer.o ../common/pagedir.o ../common/index.o
LIBS = -lm -lcurl
LLIBS = ../libcs50/libcs50.a-Linux

BASH = indextest.sh

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make


all: $(PROG) $(TEST)
#$(LIB):					# this line contains target: dependency list
#	cp $(LIB)-`uname` $(LIB)

$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LLIBS) $(LIBS) -o $@

$(TEST): $(TESTOBJC) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LLIBS) $(LIBS) -o $@

indextest.o: indextest.c ../libcs50/hashtable.o ../libcs50/memory.o ../libcs50/set.o ../libcs50/webpage.o ../libcs50/counters.o ../common/pagedir.o ../common/index.o
indexer.o: indexer.c ../libcs50/hashtable.o ../libcs50/memory.o ../libcs50/set.o ../libcs50/webpage.o ../libcs50/counters.o ../common/pagedir.o ../common/index.o
#hashtable.o: ../libcs50/hashtable.h ../libcs50/jhash.h ../libcs50/set.h
#set.o: ../libcs50/set.h
#file.o: ../libcs50/file.h
#counters.o : ../libcs50/counters.h
#webpage.o: ../libcs50/webpage.h ../libcs50/webpage_internal.h
#webpage_fetch.o: ../libcs50/webpage.h ../libcs50/webpage_internal.h ../libcs50/webpage_fetch.c
#jhash.o: ../libcs50/jhash.h
#memory.o: ../libcs50/memory.h
pagedir.o: ../common/pagedir.h ../libcs50/webpage.h../libcs50/file.h
index.o: ../common/index.h ../libcs50/webpage.h ../libcs50/webpage_internal.h ../libcs50/hashtable.h ../libcs50/jhash.h ../libcs50/set.h ../libcs50/counters.h ../libcs50/file.h

.PHONY: all clean

test: $(PROG)
	./$(PROG) test_dir indexFile

tester: $(TEST)
	./$(TEST) indexFile indexFileTested

compare: $(BASH)
	./$(BASH) indexFile indexFileTested

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f $(TEST)



#./$(PROG) ../crawler/data indexFile
