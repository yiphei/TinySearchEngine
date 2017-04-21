### Memory functions

In my `memory.c` file I include an extended version of my `malloc`/`free` tracking code, introduced in the code provided for Lab 3.  These functions introduce a new concept: `assert`.  The traditional notion of an `assert` function is to "assert that a given condition is true, and if not, to print an error message and exit the program."  In this case, I wanted a convenient way to test the pointers returning from `malloc` (and related calls); if NULL, which is an unexpected and rare occurrence, I want to print an error message and exit. 

> Such behavior is not really appropriate for general-purpose use, because crashing (exiting) the program is not behavior many systems or users will accept - but it will do for our purposes.

Here are two of the function prototypes:

```c
/**************** assertp ****************/
/* If pointer p is NULL, print error message and die,
 * otherwise, return p unchanged.  Works nicely as a pass-through:
 *   thingp = assertp(malloc(sizeof(thing)), "thing");
 */
void *assertp(void *p, char *message);

/**************** count_malloc_assert() ****************/
/* Like malloc() but track the number of successful allocations,
 * and, if response is NULL, print error and die.
 * Unlike malloc(), it takes a 'message' parameter.
 */
void *count_malloc_assert(size_t size, char *message);

```

The first is used by the second; indeed, the first line of `count_malloc_assert` is 

```
  void *ptr = assertp(malloc(size), message);
```

Notice that it acts like a pass-through function, when all is well.  The pointer coming from `malloc` is returned by `assertp` and is saved in the variable.  At that point it is assured to be non-NULL.  When `assertp` receives a NULL pointer, it prints a message to `stderr` and exits:

```c
void *
assertp(void *p, char *message)
{
  if (p == NULL) {
    fprintf(stderr, "MALLOC FAILED: %s\n", message);
    exit (99);
  }
  return p;
}
```

