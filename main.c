#include "heap.h"
#include "queue.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *nomTarea;
  Queue *tareasPrecedentes;
  bool completa;
  int prioridad;
} Tarea;//Es el (void *data) que utilizaran las estructuras

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
  Tarea *nodoTarea = NULL;
  printf("Advertencia: La tarea1 se debe realizar antes que la tarea2\n\n");
  
  do {
    printf("Ingrese el nombre de la tarea1: ");
    scanf("%s", tarea1);
    printf("\n");
    
    if (buscarTarea(monTareas, tarea1) == NULL)
      printf("El nombre de tarea ingresado no es valido. Por favor, intente nuevamente.\n");
    else break;
  } while (true);//Verificar que el nombre exista

  do {
    printf("Ingrese el nombre de la tarea2: ");
    scanf("%s", tarea2);
    printf("\n");

    nodoTarea = buscarTarea(monTareas, tarea2);
    
    if (nodoTarea == NULL || strcmp(tarea1, tarea2) == 0) {//ERROR DE SEGMENTACION ACA
      if (nodoTarea == NULL)printf("El nodo es NULL\n");
      if (strcmp(tarea1, tarea2) == 0)printf("Las tareas son iguales\n");
      printf("El nombre de tarea ingresado no es valido. Por favor, intente nuevamente.\n");
    }
    else { 
      break;
    }
  } while (true);//Verificar que el nombre exista y no sea igual

  queue_clear(nodoTarea->tareasPrecedentes);
  nodoTarea->tareasPrecedentes = queue_create();
  
  queue_enqueue(nodoTarea->tareasPrecedentes, tarea1);
  return;
}

Queue *mostrarTareasPorHacer(Heap *monTareas) {
  Heap *monAux = monTareas;
  Heap *monParalelo = createHeap();
  Tarea *tareaAux = NULL;
  
  for (unsigned int i = 0; i < heap_size(monTareas); i++){
    tareaAux = heap_top(monAux);
    if (tareaAux->tareasPrecedentes == NULL){
      heap_push(monParalelo, tareaAux, tareaAux->prioridad);
    }
    else{
      
    }
  }
  return NULL;
}

int main() {
  Queue *tareasPorHacer = queue_create();
  Queue *tareasOrdenadas = queue_create();
  Heap *monTareas = createHeap();
  
  if (tareasPorHacer == NULL || tareasOrdenadas == NULL || monTareas == NULL) {
    printf("ERROR DE MEMORIA");
    exit(EXIT_FAILURE);
  }

  while (true) {

    int opcion;
    menu(&opcion);
    
    switch (opcion) {
    case 1:
      agregarTarea(monTareas);
      printf("\nTAMAÑO SIZE: %d", heap_size(monTareas));
      printf("\nTAMAÑO CAPACIDAD: %d", heap_capac(monTareas));
      break;
    case 2:
      agregarPrecedencia(monTareas);
      break;
    case 3:
   //   tareasPorHacer = mostrarTareasPorHacer(monTareas);
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