# CS50 Lab 5
## Yifei Yan

### Design of  'indexer.c'



###Data structure

**indexer.c** need a data structure to represent the inverted index. It’s called an inverted index because it maps from words to documents, the opposite of a document (itself a sequence of words).

 A hashtable of countersets is perfect to map from a word to a list of (docID, count) pairs. The index maps from words to (docID, count) *pairs*, representing the number of occurences of that word in that document. We use a *hashtable* wherein each element is a *counters_t* where we use the docID as a key.

Therefore, we use hashtable, set, and counters as our data structures.

When processing a given document (identified by docID), consider each word; look up that word in the hashtable and retrieve a pointer to a counters_t* item; then use counters_add() on that item, using the docID as a key.

###Indexer pseudocode

Very high-level description of the indexer and indextest.

`indexer`:

1. Process and validate command-line parameters
2. Initialize data structure index
3. index_build(directory, index)
4. index_save(file, index);
5. clean up data structures


`indextest`:

1. Process and validate command-line parameters
2. Initialize data structure index
3. index_load(file1, index)
4. index_save(file2, index)
5. clean up data structures