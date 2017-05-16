# CS50 Lab 6
## Yifei Yan

### Design of  'querier.c'


###Syntax
Queries are a sequence of words, with optional boolean operators (‘and’, ‘or’), where ‘and’ has higher precedence than ‘or’.

First, we ignore blank lines (i.e., empty or nothing but spaces).Second, we translate all upper-case letters on the input line into lower-case. A word is a sequence of one or more (lower-case) letters. The syntax also must abide to the following:

* the literal ‘and’ must come between words, and the literal ‘or’ must come between andsequences, so they cannot appear at the beginning or end of a query,
* the literals (‘and’ & ‘or’) cannot be adjacent
* characters other than letters or spaces are disallowed.


###Satisfy

A document satisfies a single-word query for `word` if that `word` appears in that document.

A document satisfies a conjunction (aka `andsequence`) `wordA and wordB` if both `wordA` and `wordB` appear in the document. By induction, a document satisfies `<andsequence> and wordC` if the document satisfies the `andsequence` and `wordC` also appears in the document.

A document satisfies a disjunction `wordA or wordB` if either `wordA` and `wordB` appear in the document. By induction, a document satisfies `<andsequenceA> or <andsequenceB>` if the document satisfies the `andsequenceB` or satisfies `andsequenceB`, or both.


###Score

The score for a document satisfying a single-word query for `word` is the number of occurrences of word in that document. (Fortunately, that’s what your index tells you.)

The score for a document satisfying a conjunction (aka `andsequence`) `wordA and wordB` is the minimum of the score for `wordA` and the score for `wordB` on this document. By induction, the score for a document satisfying `<andsequence> and wordC` is the minimum of the score for the `andsequence` and the score for `wordC` on this document.

The score for a document satisfying a disjunction `wordA or wordB` is the sum of the score for `wordA` and the score for `wordB` on this document. By induction, the score for a document satisfying `<andsequenceA> or <andsequenceB>` is the sum of the score for `andsequenceA` and the score for `andsequenceB` on this document.

###Combining results

If I am processing `wordA AND wordB`, the set of documents that match both words is the intersection of the two sets, and the score for each document (per the specs) is the minimum of the count for each document. I iterate over one set and, for each item, checking whether that document exists in the other set; update the first set according to what I find. I can use `counters_iterate`, `counters_get`, and `counters_set` to do this.

If I am processing `wordA OR wordB`, the set of documents that match either word is the union of the two sets, and the score for each document (per the definition above) is the sum of the count for each document. I iterate over the second set and, for each item, checking whether that document exists in the first set; update the first set according to what I find. Again, I can use `counters_iterate`, `counters_get`, and `counters_set` to do this.

While processing an `andsequence` you can compute a ‘running product’, that is, a `counters` object that represents the intersection of everything seen so far in the sequence.

When processing a query, that is, a disjunction of `andsequence` results, you can similarly compute a ‘running sum’, that is, a `counters` object that represents the union of everything seen so far in the sequence.

###Ranking results

After parsing and interpreting a query, I will likely have a `counters` object representing the score for each satisfying document. The `counters `module does not have a ‘sort’ method or a way to iterate over the items in sorted order. I use `counters_iterate()` in which the `itemfunc `inserts the items into a new array of structs, each struct representing one satisfying document (docID, score). Use `counters_iterate` twice - once to count the number of items in the set so you can allocate an appropriate-sized array, and again to stuff each item into the new array.