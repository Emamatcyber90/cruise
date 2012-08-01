/* implements a fixed-size stack which stores integer values in range
 * of 0 to size-1, entire structure stored in an int array of size+2
 *   int size
 *   int last
 *   int entries[size] 
 * last records index within entries that points to item one past
 * the item at the top of the stack */

#include "scrmfs-stack.h"

/* returns number of bytes needed to represent stack data structure */
size_t scrmfs_stack_bytes(int size)
{
  size_t bytes = sizeof(scrmfs_stack) + size * sizeof(int);
  return bytes;
}
  
/* intializes stack to record all entries as being free */
void scrmfs_stack_init(void* start, int size)
{
  scrmfs_stack* stack = (scrmfs_stack*) start;
  stack->size = size;
  stack->last = size;

  int i;
  int* entries = (int*) ((char*)start + sizeof(scrmfs_stack));
  for (i = 0; i < size; i++) {
    /* flip the order so low numbers are at the top
     * to make debugging easier */
    entries[i] = size-1 - i;
  }
}

/* pops one entry from stack and returns its value */
int scrmfs_stack_pop(void* start)
{
  scrmfs_stack* stack = (scrmfs_stack*) start;

  /* check that the stack isn't empty */
  if (stack->last > 0) {
    /* decrement the last pointer by one */
    stack->last--;

    /* return the index into entries array,
     * this now points to item at top of stack */
    int idx = stack->last;

    /* return the value of this item */
    int* entries = (int*) ((char*)start + sizeof(scrmfs_stack));
    int value = entries[idx];
    return value;
  } else {
    /* out of space */
    return -1;
  }
}

/* pushes item onto free stack */
void scrmfs_stack_push(void* start, int value)
{
  scrmfs_stack* stack = (scrmfs_stack*) start;

  /* check that we have space to push item onto stack */
  if (stack->last < stack->size) {
    /* get index of first free slot in entries array */
    int idx = stack->last;

    /* place item on stack */
    int* entries = (int*) ((char*)start + sizeof(scrmfs_stack));
    entries[idx] = value;

    /* increment last pointer to point to next item */
    stack->last++;
  } else {
    /* freed one too many */
  }
}
