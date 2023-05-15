#include "heap.h"
#include "list.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *nomTarea;
  int prioridad;
  List *tareasPrecedentes;
  bool completa;
} Nodo;//Es el (void *data) dentro del nodo de la lista enlazada

typedef struct {
  int numTareas;
  Nodo *nodos;
} Grafo;

Nodo *crearNodo(char *data, int prio) {
  
  Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
  if (nuevo == NULL)exit(EXIT_FAILURE);
  nuevo->nomTarea = malloc(strlen(data) + 1);
  if (nuevo->nomTarea == NULL)exit(EXIT_FAILURE);
  
  strcpy(nuevo->nomTarea, data);
  nuevo->prioridad = prio;
  nuevo->tareasPrecedentes = createList();
  nuevo->completa = false;
  
  return nuevo;
}

Grafo *crearGrafo(int numTareas) { return NULL; }

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

void agregarTarea(List *tareaSinOrden) {
  char tareaAux[101];
  int prioAux;

  printf("Ingrese el nombre de la tarea\n");
  scanf("%s", tareaAux);

  printf("Ingrese la prioridad de la tarea\n");
  scanf("%d", &prioAux);

  Nodo *tarea = crearNodo(tareaAux, prioAux);
  pushFront(tareaSinOrden, tarea);
  return;
}

void agregarPrecedencia(List *tareasSinOrden) {
  char tarea1[101], tarea2[101];
  bool flag1 = false;
  bool flag2 = false;
  Nodo *tareaAux1 = firstList(tareasSinOrden);
  Nodo *tareaAux2 = firstList(tareasSinOrden);
  
  printf("La tarea1 se debe realizar antes que la tarea2\n");
  
  do {
    printf("Ingrese el nombre de la tarea: ");
    scanf("%s", tarea1);
    printf("\n");
    tareaAux1 = firstList(tareasSinOrden);

    while (tareaAux1 != NULL) {
      if (strcmp(tareaAux1->nomTarea, tarea1) == 0) {
        flag1 = true;
        break;
      }
      tareaAux1 = nextList(tareasSinOrden);
    }
  
    if (!flag1) {
      printf("El nombre de tarea ingresado no es válido. Por favor, intente nuevamente.\n");
    }
  } while (!flag1);

  do {
    printf("Ingrese el nombre de la tarea2: ");
    scanf("%s", tarea2);
    printf("\n");
    tareaAux2 = firstList(tareasSinOrden);

    while (tareaAux2 != NULL) {
      if (strcmp(tareaAux2->nomTarea, tarea2) == 0 && strcmp(tarea1, tarea2) != 0) {
        flag2 = true;
        break;
      }
      tareaAux2 = nextList(tareasSinOrden);
    }
  
    if (!flag2) {
      printf("El nombre de tarea ingresado no es válido. Por favor, intente nuevamente.\n");
    }
  } while (!flag2);

  pushFront(tareaAux2->tareasPrecedentes, tarea1);
}

void mostrarTareas() {}

int main() {
  List *tareasPorHacer = createList();
  List *tareasOrdenadas = createList();

  if (tareasPorHacer == NULL || tareasOrdenadas == NULL) {
    printf("ERROR DE MEMORIA");
    exit(EXIT_FAILURE);
  }

  while (true) {

    int opcion;
    printf("Ingrese la opcion que desee realizar:\n");
    menu(&opcion);

    switch (opcion) {
    case 1:
      agregarTarea(tareasPorHacer);
      break;
    case 2:
      agregarPrecedencia(tareasPorHacer);
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