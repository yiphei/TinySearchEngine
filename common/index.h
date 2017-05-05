

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/set.h"
#include "../libcs50/counters.h"
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"
#include "../libcs50/file.h"

/**************** global types ****************/

/**************** functions ****************/

/* Create a new (empty) counter structure; return NULL if error. */
void index_build(hashtable_t * index, char * pageDirectory);

void index_save(hashtable_t * index, char * indexFilename);

#endif // __INDEX_H