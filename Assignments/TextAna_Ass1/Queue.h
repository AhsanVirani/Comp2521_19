// Queue.h ... interface to Queue-of-BSTree-nodes ADT

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "Dict.h"

typedef struct QueueRep *Queue;
typedef struct _DictNode *Link;

// create new empty queue
Queue newQueue (void);
// free memory used by queue
void dropQueue (Queue);
// display as 3 > 5 > 4 > ...
void showQueue (Queue);
// add item on queue
void QueueJoin (Queue, Link);
// remove item from queue
Link QueueLeave (Queue);
// check for no items
bool QueueIsEmpty (Queue);

#endif
