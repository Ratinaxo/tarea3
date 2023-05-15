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
} Nodo;

typedef struct {
  int numTareas;
  Nodo *nodos;
} Grafo;

Nodo *crearNodo(char *data, int prio) {
  Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
  if (nuevo == NULL)exit(EXIT_FAILURE);
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

void precedencia(List *tareasSinOrden) {
  char tarea1[101], tarea2[101];
  
  printf("La tarea1 se realizará antes que la tarea2\n");
  
  printf("Ingrese el nombre de la tarea1: ");
  scanf("%s", tarea1);
  printf("\n");
  
  printf("Ingrese el nombre de la tarea 2: ");
  scanf("%s", tarea2);
  printf("\n");
  
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