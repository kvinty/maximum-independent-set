#ifndef _def_graph
#define _def_graph

#include "stdlib.h"
#include "stdio.h"

#define OUT      1
#define TO_CHECK 2         
#define MARKED   4
#define VISITED  8

typedef struct Graph{
  int **adjacency;
  int *adj_size, *adj_capacity;
  char *mark;
  int *v, *x, *y;
  int size, capacity;
} Graph;

Graph* init_graph(int);
int add_vertex(Graph*);
void add_edge(int, int, Graph*);
void extend_graph(Graph*);
void free_graph(Graph*);
int get_degree(int, Graph*);
char are_connected(int, int, Graph*);
Graph* read_graph(char*);

#endif
