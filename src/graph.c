#include "graph.h"

Graph* init_graph(int size){
  Graph *graph = (struct Graph*) malloc(sizeof(struct Graph));

  graph->size = size;
  graph->capacity = 1;

  while(graph->capacity < graph->size)
    graph->capacity <<= 1;
  
  graph->adjacency = (int**) malloc(graph->capacity*sizeof(int*));
  graph->adj_size = (int*) malloc(5*graph->capacity*sizeof(int));
  graph->mark = (char*) malloc(graph->capacity*sizeof(char));
  
  graph->adj_capacity = graph->adj_size + graph->capacity;
  graph->v = graph->adj_capacity + graph->capacity;
  graph->x = graph->v + graph->capacity;
  graph->y = graph->x + graph->capacity;
  
  for(int u=0; u<graph->capacity; u++){
    graph->adjacency[u] = (int*) malloc(sizeof(int));
    graph->adj_capacity[u]= 1;
  }
  for(int u=0; u<graph->size; u++){
    graph->adj_size[u] = 0;
    graph->mark[u] = 0;
    graph->v[u] = -1;
  }

  return graph;
}

int add_vertex(Graph* graph)
{
  if(graph->size == graph->capacity)
    extend_graph(graph);

  int u = graph->size;
  graph->size++;
  graph->mark[u] = 0;
  graph->v[u] = -1;
  graph->adj_size[u] = 0;

  return u;
}

void add_edge(int u, int v, Graph* graph)
{
  int adj_capacity_u = graph->adj_capacity[u];
  int *adj_u = graph->adjacency[u];
  if(graph->adj_size[u] == adj_capacity_u){
    int *new_adj_u = (int*) malloc((adj_capacity_u<<1)*sizeof(int));
    for(int i=0; i<adj_capacity_u; i++){
      new_adj_u[i] = adj_u[i];
    }
    free(adj_u);
    graph->adjacency[u] = new_adj_u;
    graph->adj_capacity[u] <<= 1;
  }
  graph->adjacency[u][graph->adj_size[u]++] = v;

  int adj_capacity_v = graph->adj_capacity[v];
  int *adj_v = graph->adjacency[v];
  if(graph->adj_size[v] == adj_capacity_v){
    int *new_adj_v = (int*) malloc((adj_capacity_v<<1)*sizeof(int));
    for(int j=0; j<adj_capacity_v; j++){
      new_adj_v[j] = adj_v[j];
    }
    free(adj_v);
    graph->adjacency[v] = new_adj_v;
    graph->adj_capacity[v] <<= 1;
  }
  graph->adjacency[v][graph->adj_size[v]++] = u;
}

void extend_graph(Graph* graph)
{
  int new_capacity = graph->capacity << 1;
  
  int **new_adjacency = (int**) malloc(new_capacity*sizeof(int*));
  int *new_adj_size = (int*) malloc(5*new_capacity*sizeof(int));
  char *new_mark = (char*) malloc(new_capacity*sizeof(char));
  
  int *new_adj_capacity = new_adj_size + new_capacity;
  int *new_v = new_adj_capacity + new_capacity;
  int *new_x = new_v + new_capacity;
  int *new_y = new_x + new_capacity;
  
  for(int u=0; u<graph->capacity; u++){
    new_adjacency[u] = graph->adjacency[u];
    new_mark[u] = graph->mark[u];
    new_v[u] = graph->v[u];
    new_x[u] = graph->x[u];
    new_y[u] = graph->y[u];
    new_adj_size[u] = graph->adj_size[u];
    new_adj_capacity[u] = graph->adj_capacity[u];
  }
  for(int u=graph->capacity; u<new_capacity; u++){
    new_adjacency[u] = (int*) malloc(sizeof(int));
    new_adj_capacity[u] = 1;
  }

  free(graph->adjacency);
  free(graph->mark);
  free(graph->adj_size);
  
  graph->adjacency = new_adjacency;
  graph->adj_size = new_adj_size;
  graph->adj_capacity = new_adj_capacity;
  graph->mark = new_mark;
  graph->v = new_v;
  graph->x = new_x;
  graph->y = new_y;
  
  graph->capacity = new_capacity;
}

void free_graph(Graph* graph)
{
  for(int u=0; u<graph->capacity; u++)
    free(graph->adjacency[u]);

  free(graph->adjacency);
  free(graph->adj_size);
  free(graph->mark);
  
  free(graph);
}

int get_degree(int u, Graph* graph){
  int degree_u = 0;
  int *adj_u = graph->adjacency[u];
  for(int i = 0; i<graph->adj_size[u]; i++){
    if(!(OUT & graph->mark[adj_u[i]]))
      degree_u++;
  }
  return degree_u;
}

char are_connected(int u, int v, Graph* graph)
{
  int *adj_v = graph->adjacency[v];
  for(int i=0; i<graph->adj_size[v]; i++){
    if(adj_v[i] == u)
      return 1;
  }
  return 0;
}

Graph* read_graph(char* filename)
{
  FILE *file = fopen(filename, "r");
  if(file == NULL){
    printf("Error: unable to read input file\n");
    exit(1);
  }
  
  int nb_vertices;
  fscanf(file, "%d", &nb_vertices);

  Graph *graph = init_graph(nb_vertices);
  
  for(int u=0; u<nb_vertices; u++){
    int degree_u;
    fscanf(file, "%d", &degree_u);
    
    for(int i=0; i<degree_u; i++){
      int v;
      fscanf(file, "%d", &v);
      
      if(u < v)
	add_edge(u, v, graph); 
    }
  }

  fclose(file);
  
  return graph;
}
