#ifndef Heap_h
#define Heap_h

typedef struct Heap Heap;

Heap* createHeap();
void* heap_top(Heap* pq);
void heap_push(Heap* pq, void* data, int priority);
void heap_pop(Heap* pq);
int heap_size(Heap* pq);
int heap_capac(Heap* pq);

#endif /* HashMap_h */