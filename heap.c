#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;

void swap(heapElem *a, heapElem *b){
  heapElem aux = *a;
  *a = *b;
  *b = aux;
  return;
}

void* heap_top(Heap* pq){
  if (pq == NULL || pq->size == 0)return NULL;
  return pq->heapArray[0].data;
}

void heap_push(Heap* pq, void* data, int priority){
  if (pq == NULL || pq->size == 0)return;
  if(pq->size == pq->capac){
    int newCapac = (pq->capac * 2) + 1;
    pq->heapArray = realloc(pq->heapArray, (newCapac * sizeof(heapElem)));
    if(pq->heapArray == NULL)return;
    pq->capac = newCapac;
  }

  int index = pq->size;
  pq->heapArray[index].data = data;
  pq->heapArray[index].priority = priority;
  pq->size++;

  while(index > 0 && pq->heapArray[(index - 1) / 2].priority < pq->heapArray[index].priority){
    swap(&pq->heapArray[(index - 1) / 2], &pq->heapArray[index]);
    index = (index - 1) / 2;
  }
  return;
}


void heap_pop(Heap* pq){
  if(pq == NULL || pq->size == 0)return;
  pq->heapArray[0] = pq->heapArray[pq->size - 1];
  pq->size--;

  int index = 0;
  while(1){
    int izq = (index * 2) + 1;
    int der = (index * 2) + 2;
    int grande = index;

    if (izq < pq->size && pq->heapArray[izq].priority > pq->heapArray[grande].priority)
      grande = izq;
    
    if (der < pq->size && pq->heapArray[der].priority > pq->heapArray[grande].priority)
      grande = der;

    if(grande == index)break;

    swap(&pq->heapArray[index], &pq->heapArray[grande]);
    index = grande;
  }
  return;
}

Heap* createHeap(){
  Heap *heap = (Heap*)malloc(sizeof(Heap));
  if (heap == NULL)return NULL;

  heap->heapArray = (heapElem*)malloc(3 * sizeof(heapElem));
  if (heap->heapArray == NULL){
    free(heap);
    return NULL;
  }

  heap->size = 0;
  heap->capac = 3;
  return heap;
}

int heap_size(Heap* pq){
  return pq->size;
}

int heap_capac(Heap* pq){
  return pq->capac;
}