#ifndef GRAPH_H
#define GRAPH_H

typedef struct GraphNode GraphNode;
typedef struct Graph Graph;

Graph *graph_create(int cantNodes);
void graph_addNode(Graph* graph, char* data);
void graph_addAdjNodes(Graph *graph, char* src, char* dest);
void graph_clear(Graph *graph);

#endif  /* GRAPH_H */