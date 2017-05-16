# Makefile for 'querier.c'
#
# Yifei Yan


PROG = querier
OBJS = querier.o ../common/pagedir.o ../common/index.o
LIBS = -lm -lcurl
LLIBS = ../libcs50/libcs50.a-Linux

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
pagedir.o: ../common/pagedir.h ../libcs50/webpage.h../libcs50/file.h
index.o: ../common/index.h ../libcs50/webpage.h ../libcs50/webpage_internal.h ../libcs50/hashtable.h ../libcs50/jhash.h ../libcs50/set.h ../libcs50/counters.h ../libcs50/file.h

.PHONY: all clean

test: $(PROG)
	./$(PROG) ~cs50/data/tse-output/cs50-3 ~cs50/data/tse-output/cs50-index3


clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f $(TEST)



#./$(PROG) ../indexer/test_dir ../indexer/indexFile
#./$(PROG) ~cs50/data/tse-output/cs50-3 ~cs50/data/tse-output/cs50-index3
