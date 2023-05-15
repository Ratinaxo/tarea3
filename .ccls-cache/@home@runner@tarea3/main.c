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
} Tarea;//Es el (void *data) que utilizaran las estructuras

bool buscarTarea(Heap *monTareas, char *nomTarea){
  Heap *heapAux = monTareas;
  Tarea *tareaAux = NULL;
  
  do {
    tareaAux = (Tarea*)heap_top(monTareas);
    if (strcmp(tareaAux->nomTarea,nomTarea) == 0){
      free(tareaAux);
      free(heapAux);
      return true;
    }
    heap_pop(heapAux);
  }while(tareaAux != NULL);

  free(tareaAux);
  free(heapAux);
  return false;
}

Tarea *crearTarea(char *nombreTarea) {
  
  Tarea *nuevo = (Tarea *)malloc(sizeof(Tarea));
  if (nuevo == NULL)exit(EXIT_FAILURE);
  nuevo->nomTarea = malloc(strlen(nombreTarea) + 1);
  if (nuevo->nomTarea == NULL)exit(EXIT_FAILURE);
  
  strcpy(nuevo->nomTarea, nombreTarea);
  nuevo->tareasPrecedentes = createList();
  nuevo->completa = false;
  
  return nuevo;
}

void menu(int *opcion) {
  printf("\nElija una opcion para continuar:\n");
  printf("1.- Agregar tarea\n");
  printf("2.- Establecer precedencia entre tareas\n");
  printf("3.- Mostrar tareas por hacer\n");
  printf("4.- Marcar tarea como completada\n");
  printf("0.- Salir\n");

  char comprobar[2];
  while (1) {
    scanf("%s", comprobar);

    if (isdigit(comprobar[0]) && strlen(comprobar) == 1) {
      *opcion = atoi(comprobar);
      return;
    }
    printf("Entrada invalida, ingrese una opcion valida entre 0 y 9\n");
    return;
  }
}

void agregarTarea(Heap *monTareas) {
  char tareaAux[101];
  int prioAux;

  printf("Ingrese el nombre de la tarea\n");
  scanf("%s", tareaAux);

  printf("Ingrese la prioridad de la tarea\n");
  scanf("%d", &prioAux);

  Tarea *tarea = crearTarea(tareaAux);
  heap_push(monTareas, tarea, prioAux);
  
  return;
}

void agregarPrecedencia(Heap *monTareas) {
  char tarea1[101], tarea2[101];
  
  printf("La tarea1 se debe realizar antes que la tarea2\n");
  
  do {
    printf("Ingrese el nombre de la tarea: ");
    scanf("%s", tarea1);
    printf("\n");
  
    if (!buscarTarea(monTareas, tarea1)) {
      printf("El nombre de tarea ingresado no es válido. Por favor, intente nuevamente.\n");
    }
    else break;
  } while (true);//Verificar que el nombre exista

  do {
    printf("Ingrese el nombre de la tarea2: ");
    scanf("%s", tarea2);
    printf("\n");

    if (!buscarTarea(monTareas, tarea2) || strcmp(tarea1, tarea2) == 0) {
      printf("El nombre de tarea ingresado no es válido. Por favor, intente nuevamente.\n");
    }
  } while (true);//Verificar que el nombre exista y no sea igual

  
  
}

void mostrarTareas() {}

int main() {
  List *tareasPorHacer = createList();
  Queue *tareasOrdenadas = queue_create();
  Heap *monTareas = createHeap();
  
  if (tareasPorHacer == NULL || tareasOrdenadas == NULL || monTareas == NULL) {
    printf("ERROR DE MEMORIA");
    exit(EXIT_FAILURE);
  }

  while (true) {

    int opcion;
    printf("Ingrese la opcion que desee realizar:\n");
    menu(&opcion);
    
    switch (opcion) {
    case 1:
      agregarTarea(monTareas);
      break;
    case 2:
      agregarPrecedencia(monTareas);
      break;
    case 3:
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