#ifndef queue_h
#define queue_h

#include "list.h"
typedef List Queue;

#define queue_create() createList()

#define queue_enqueue(queue, data) pushBack(queue, data)

#define queue_dequeue(queue) popFront(queue)

#define queue_peek(queue) firstList(queue)

#define queue_clear(queue) cleanList(queue)

#endif /* Queue.h */