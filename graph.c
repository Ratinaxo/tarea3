#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "graph.h"

typedef struct GraphNode GraphNode;

struct GraphNode {
  char* data;
  //Se ha adaptado el grafo para ser utilizado con cadenas
  GraphNode* next;
};

struct Graph {
  int cantNodes;
  GraphNode **adj;
};

typedef Graph Graph;

GraphNode* node_create(char* data){
  GraphNode *newNode = (GraphNode*)malloc(sizeof(GraphNode));
  newNode->data = strdup(data);
  newNode->next = NULL;
  return newNode;
}

Graph* graph_create(int cantNodes) {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  graph->adj = (GraphNode**)calloc(cantNodes, sizeof(GraphNode*));
  graph->cantNodes = cantNodes;
  return graph;
}


void graph_addNode(Graph* graph, char* data) {
  if (graph == NULL)return;
  GraphNode *newNode = node_create(data);
  int index = -1;
  for (unsigned int i = 0; i < graph->cantNodes; i++){
    if (graph->adj[i] == NULL){
      index = i;
      break;
    }
  }
  if (index == -1)return;
  graph->adj[index] = newNode;
  
}

void graph_addAdjNodes(Graph *graph, char* src, char* dest){
  if (graph == NULL)return;
  int srcIndex = -1, destIndex = -1;
  
  for (int i = 0; i < graph->cantNodes; i++){
    if (graph->adj[i] != NULL){
      if(strcmp(graph->adj[i]->data, src) == 0)
        srcIndex = i;
      if (strcmp(graph->adj[i]->data, dest) == 0)
        destIndex = i;
    }
  }
  if (srcIndex == -1 || destIndex == -1)return;

  GraphNode *newNode = node_create(dest);
  newNode->next = graph->adj[srcIndex];
  graph->adj[srcIndex] = newNode;
}

bool graph_haveAdj(Graph *graph){
  for (unsigned int i = 0; i <= graph->cantNodes; i++){
    if(graph->adj[i]->next == NULL)return false;
  }
}

void graph_clear(Graph* graph) {
  if (graph != NULL) {
    for (unsigned int i = 0; i < graph->cantNodes; i++) {
      GraphNode* node = graph->adj[i];
        while (node != NULL) {
          GraphNode* temp = node;
          node = node->next;
          free(temp);
        }
    }
    free(graph->adj);
    free(graph);
  }
}