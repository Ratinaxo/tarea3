#include "heap.h"
#include "list.h"
#include "queue.h"
#include "graph.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea Tarea;
typedef struct Nodo Nodo;

struct Tarea {
  char *nomTarea;
  bool completa;
  int prioridad;
  Tarea *tareasPrecedentes;
};//Es el (void *data) que utilizaran las estructuras

struct Nodo{
  Tarea tarea;
  Nodo* next;
};


Tarea *buscarTarea(Heap *monTareas, char *nomTarea){
  Heap *monAux = createHeap();
  Tarea *tareaAux = NULL;
  
 while (heap_size(monTareas) > 0){
   tareaAux =heap_top(monTareas);
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

Tarea *crearTarea(char *nombreTarea, int prioridad) {
  
  Tarea *nuevo = (Tarea *)malloc(sizeof(Tarea));
  if (nuevo == NULL)exit(EXIT_FAILURE);
  nuevo->nomTarea = malloc(strlen(nombreTarea) + 1);
  if (nuevo->nomTarea == NULL)exit(EXIT_FAILURE);
  
  strcpy(nuevo->nomTarea, nombreTarea);
  nuevo->tareasPrecedentes = NULL;
  nuevo->completa = false;
  nuevo->prioridad = prioridad;
  return nuevo;
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

void agregarTarea(Queue *tarea) {
  char nomAux[101];
  int prioAux;
  printf("Ingrese el nombre de la tarea: ");
  scanf("%s", nomAux);
  getchar();
  printf("\n");
  printf("Ingrese la prioridad de la tarea: ");
  scanf("%d", &prioAux);

  Tarea *tareaAux = crearTarea(nomAux, prioAux);
  queue_enqueue(tarea, tareaAux);
  
  return;
}

void agregarPrecedencia(Nodo **listaTareas) {
}

void mostrarTareasPorHacer(Heap *monTareas) {
}

int main() {
  Queue *tareasPorHacer = queue_create();
  Queue *tareasOrdenadas = queue_create();
  Heap *monTareas = createHeap();
  int cantTareas = 0;

  if (tareasPorHacer == NULL || tareasOrdenadas == NULL || monTareas == NULL) {
    printf("ERROR DE MEMORIA");
    exit(EXIT_FAILURE);
  }

  while (true) {

    int opcion;
    menu(&opcion);
    
    switch (opcion) {
    case 1:
      agregarTarea(tareasPorHacer);
      cantTareas++;
      break;
    case 2:
      agregarPrecedencia(monTareas);
      break;
    case 3:
      mostrarTareasPorHacer(monTareas);
      break;
    case 4:
      break;
    case 0:
      exit(EXIT_SUCCESS);
      break;
    }
  
    
  }
  return (EXIT_SUCCESS);
}