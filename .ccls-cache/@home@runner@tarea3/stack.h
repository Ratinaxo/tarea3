#ifndef queue_h
#define queue_h

#include "list.h"
typedef List Queue;

#define queue_create() createList()

#define queue_pop(stack) popFront(stack)

#define queue_push(stack, data) pushFront(stack, data)

#define queue_top(stack) firstList(stack)

#define queue_clean(stack) cleanList(stack)

#endif /* Queue.h */