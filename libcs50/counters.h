/* 
 * counters.h - header file for CS50 'counters' module
 * 
 * A counter set is a set of counters, each distinguished by an integer key. 
 * It’s a set - each key can only occur once in the set - but instead of storing (key,item) 
 * pairs, it tracks a counter for each key. It starts empty. Each time counters_add 
 * is called on a given key, that key’s counter is incremented. The current counter 
 * value can be retrieved by asking for the relevant key.
 *
 * Yifei Yan
 */

#ifndef __COUNTERS_H
#define __COUNTERS_H

#include <stdio.h>

/**************** global types ****************/
typedef struct counters counters_t;  // opaque to users of the module

/**************** functions ****************/

/* Create a new (empty) counter structure; return NULL if error. */
counters_t *counters_new(void);

/* Increment the counter indicated by key; key must be >= 0.
 * If the key does not yet exist, create a counter for it and initialize to 1.
 * Ignore if ctrs is NULL or key is negative.
 */
void counters_add(counters_t *ctrs, const int key);

/* Return current value of counter associated with the given key;
 * return 0 if ctrs is NULL or if key is not found.
 */
int counters_get(counters_t *ctrs, const int key);

/* Set the current value of counter associated with the given key;
 * ignore if ctrs is NULL or if key is negative.
 */
void counters_set(counters_t *ctrs, const int key, int count);

/* Print all counters; provide the output file.
 * Ignore if NULL fp. Print (null) if NULL ctrs.
 */
void counters_print(counters_t *ctrs, FILE *fp);

/* Iterate over all counters in the set (in undefined order):
 * call itemfunc for each item, with (arg, key, count).
 * If ctrs==NULL or itemfunc==NULL, do nothing.
 */
void counters_iterate(counters_t *ctrs, void *arg, 
                      void (*itemfunc)(void *arg, const int key, int count));

/* Delete the whole counters. ignore NULL ctrs. */
void counters_delete(counters_t *ctrs);


#endif // __COUNTERS_H