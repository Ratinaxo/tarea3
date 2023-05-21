#include "heap.h"
#include "list.h"
#include "graph.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *nomTarea;
  List *tareasPrecedentes;
  bool completa;
  bool explorado;
  int prioridad;
  int cantPrec;
} Tarea;//Es el (void *data) que utilizaran las estructuras


Tarea *crearTarea(char *nombreTarea, int prioridad) {
  
  Tarea *nuevo = (Tarea *)malloc(sizeof(Tarea));
  if (nuevo == NULL)exit(EXIT_FAILURE);
  nuevo->nomTarea = malloc(strlen(nombreTarea) + 1);
  if (nuevo->nomTarea == NULL)exit(EXIT_FAILURE);
  
  strcpy(nuevo->nomTarea, nombreTarea);
  nuevo->tareasPrecedentes = NULL;
  nuevo->completa = false;
  nuevo->explorado = false;
  nuevo->prioridad = prioridad;
  nuevo->cantPrec = 0;
  return nuevo;
}

Tarea *buscarTarea(Heap *monTareas, char *nomTarea){
  Heap *monAux = createHeap();
  Tarea *tareaAux = NULL;
  
 while (heap_size(monTareas) > 0){
   tareaAux = heap_top(monTareas);
   if (strcmp(tareaAux->nomTarea, nomTarea) == 0)break;
   heap_push(monAux, tareaAux, tareaAux->prioridad);
   heap_pop(monTareas);
 }
  while (heap_size(monAux) > 0){
    Tarea *tarea = heap_top(monAux);
    heap_push(monTareas, tarea, tarea->prioridad);
    heap_pop(monAux);
  }
  
  free(monAux);
  if (tareaAux == NULL)return NULL;
  else return tareaAux;
}

void menu(int *opcion) {
  printf("\n------------------------------------------------------\n");
  printf("\nElija una opcion para continuar:\n\n");
  printf("1.- Agregar tarea\n");
  printf("2.- Establecer precedencia entre tareas\n");
  printf("3.- Mostrar tareas por hacer\n");
  printf("4.- Marcar tarea como completada\n");
  printf("0.- Salir\n");
  printf("\n------------------------------------------------------\n");
  printf("\nSu opcion: ");
  char comprobar[2];
  while (1) {
    scanf("%s", comprobar);

    if (isdigit(comprobar[0]) && strlen(comprobar) == 1) {
      *opcion = atoi(comprobar);
      printf("\n");
      return;
    }
    printf("Entrada invalida, ingrese una opcion valida entre 0 y 9: ");
  }
}

void agregarTarea(Heap *monTareas) {
  char tareaAux[101];
  int prioAux;

  printf("Ingrese el nombre de la tarea: ");
  scanf("%s", tareaAux);
  printf("");
  
  printf("Ingrese la prioridad de la tarea: ");
  scanf("%d", &prioAux);

  Tarea *tarea = crearTarea(tareaAux, prioAux);
  heap_push(monTareas, tarea, prioAux);

  return;
}

void agregarPrecedencia(Heap *monTareas) {
  char tarea1[101], tarea2[101];
  Tarea *nodoTarea1 = NULL, *nodoTarea2 = NULL;
  List *listaAux = createList();
  printf("Advertencia: La tarea1 se debe realizar antes que la tarea2\n\n");
  
  do {
    printf("Ingrese el nombre de la tarea1: ");
    scanf("%100s", tarea1);
    getchar();
    nodoTarea1 = buscarTarea(monTareas, tarea1);
    if (nodoTarea1== NULL)
      printf("El nombre de tarea ingresado no es valido. Por favor, intente nuevamente.\n");
    else break;
  } while (true);//Verificar que el nombre exista

  do {
    printf("Ingrese el nombre de la tarea2: ");
    scanf("%100s", tarea2);
    getchar();
    nodoTarea2 = buscarTarea(monTareas, tarea2);

    if (nodoTarea2 == NULL || strcmp(tarea1, tarea2) == 0) {
      printf("El nombre de tarea ingresado no es valido. Por favor, intente nuevamente.\n");
    }
    else break;
  } while (true);//Verificar que el nombre exista y no sea igual
  
  nodoTarea2->tareasPrecedentes = createList();
  nodoTarea2->cantPrec++;
  pushFront(nodoTarea2->tareasPrecedentes, nodoTarea1);
}

List *marcarTareaCompletada(List *listaTareas){
  Tarea *tareaAux = NULL;
  char tarea[101];
  int opcion;
  printf("Que tarea desea marcar como completada: ");
  scanf("%s", tarea);
  getchar();
  tareaAux = firstList(listaTareas);
  if (tareaAux == NULL)
    printf("ERROR");
  
  
  while(tareaAux != NULL){
    if (strcmp(tareaAux->nomTarea, tarea) == 0){
      if (tareaAux->tareasPrecedentes == NULL){
        printf("ADVERTENCIA: Es posible que deba realizar esta tarea para continuar con otras, ¿Desea continuar?\n");
        printf("|0.Si | 1.No|: ");
        scanf("%d", &opcion);
      }
      if (opcion == 1)return listaTareas;
      tareaAux->completa = true;
      popCurrent(listaTareas);
      return listaTareas;
    }
    else{
      tareaAux = nextList(listaTareas);
    }
  }
  return listaTareas;
}

List* ordenarYGuardarTareas(Heap *monTareas){
  List* lista = createList();
  Heap* monAux = createHeap();
  Graph* grafoTareas = graph_create(heap_size(monTareas));
  Tarea* tareaAux = NULL;
  Tarea* tareaQueueAux = NULL;
  
  while (heap_size(monTareas) > 0) {
    tareaAux = heap_top(monTareas);

    if (tareaAux->tareasPrecedentes == NULL) {
      graph_addNode(grafoTareas, tareaAux->nomTarea);
      heap_push(monAux, tareaAux, tareaAux->prioridad);
      heap_pop(monTareas);
    } else {
        while(firstList(tareaAux->tareasPrecedentes) != NULL){
          
        tareaQueueAux = popFront(tareaAux->tareasPrecedentes);
        graph_addAdjNodes(grafoTareas, tareaAux->nomTarea, tareaQueueAux->nomTarea);
        heap_push(monAux, tareaAux, tareaAux->prioridad);
        heap_pop(monTareas);
        }
    }
  }

  while (heap_size(monAux) > 0) {
    tareaAux = heap_top(monAux);
    pushFront(lista, tareaAux);
    
    heap_push(monTareas, tareaAux, tareaAux->prioridad);
    heap_pop(monAux);
  }

  free(monAux);
  free(grafoTareas);
  return lista;
}

void mostrarTareas(List *listaTareas){
  Tarea *tareaPrecedenteAux = NULL;
  List *listaAux = NULL;
  Tarea *tareaAux = firstList(listaTareas);
  int size = sizeList(listaTareas);
  
  printf("Tareas por hacer, ordenadas por prioridad y precedencia:\n");
  
  for (int i = 0; i < size; i++){
    tareaAux = popFront(listaTareas);
    if (!tareaAux->completa){
      printf("%i. ", i+1);
      printf("%s ", tareaAux->nomTarea);
      printf("(Prioridad: %d)", tareaAux->prioridad);
      printf("\n");
    }
    else{
      size--;
      i--;
    }
  }
}

int main() {
  Heap *monTareas = createHeap();
  List *listaTareas = NULL;
  Graph *grafoTareas = NULL;
  
  if (monTareas == NULL) {
    printf("ERROR DE MEMORIA");
    exit(EXIT_FAILURE);
  }

  while (true) {
    listaTareas = ordenarYGuardarTareas(monTareas);
    int opcion;
    menu(&opcion);
    
    switch (opcion) {
    case 1:
      agregarTarea(monTareas);
      break;
    case 2:
      agregarPrecedencia(monTareas);
      break;
    case 3:
      mostrarTareas(listaTareas);
      break;
    case 4:
      listaTareas = marcarTareaCompletada(listaTareas);
      break;
    case 0:
      exit(EXIT_SUCCESS);
      break;
    }
  }
  return (EXIT_SUCCESS);
}