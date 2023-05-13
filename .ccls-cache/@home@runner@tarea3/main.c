#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct{
  char *nombre;
  int prioridad;
}tarea;

typedef struct{
  tarea *tareas;
  int size;
  int capac;
}colaTareas;


void agregarTarea(char *nombreTarea, int prioridad){
  
}

void precedencia(char *tarea1, char *tarea2){
  
}

void mostrarTareas(colaTareas listaTareas){
  
}

int main(){
  colaTareas *listaTareas = (colaTareas*)createHeap();
  if (listaTareas == NULL){
    printf("ERROR DE MEMORIA");
    exit(EXIT_FAILURE);
  }
}