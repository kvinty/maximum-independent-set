#include "mis.h"

Graph *graph;
Array *to_delete;
Array *deleted;
Array *pile;

#include "fold.c"
#include "mirror.c"

Array* mis(Graph *input)
{
  graph = input;
  
  to_delete = new_array();
  deleted = new_array();
  pile = new_array();
  
  for(int u=0; u<graph->size; u++){
    graph->mark[u] |= TO_CHECK;
    push(u, pile);
  }

  Array *l = check(graph);

  while(deleted->size != 0)
    graph->mark[pop(deleted)] ^= OUT;
  
  free_array(to_delete);
  free_array(deleted);
  free_array(pile);
  
  return l;
}

Array* core()
{
  int d_max = -1, v;
  for(int w=0; w<graph->size; w++){
    if(OUT & graph->mark[w])
      continue;
      
    int degree_w = get_degree(w, graph);
    if(d_max < degree_w){
      d_max = degree_w;
      v = w;
    }
  }

  int mem = deleted->size;
  
  get_mirrors(v);
  push(v, to_delete);
  vertex_out();

  Array *l1 = check();

  while(deleted->size != mem)
    graph->mark[pop(deleted)] ^= OUT;

  int *adj_v = graph->adjacency[v];
  push(v, to_delete);
  for(int i=0; i<graph->adj_size[v]; i++)
    push(adj_v[i], to_delete);
  vertex_out();

  Array *l2 = check();
  push(v, l2);

  while(deleted->size != mem)
    graph->mark[pop(deleted)] ^= OUT;

  if(l1->size < l2->size){
    free_array(l1);
    return l2;
  }
  else{
    free_array(l2);
    return l1;
  }
}

Array* check()
{
  while(pile->size != 0){
    int v = pop(pile);
    
    if(OUT & graph->mark[v]){
      graph->mark[v] ^= TO_CHECK;
      continue;
    }
      
    if(is_folding(v)){
      graph->mark[v] ^= TO_CHECK;
      int mem = deleted->size;
      fold(v);
      Array *l = check();
      unfold(v, mem);

      for(int i=0; i<l->size; i++){
	int u = l->t[i];
 
	if(graph->v[u] == v){
	  l->t[i] = graph->x[u];
	  push(graph->y[u], l);
	  return l;
	}
      }
      push(v, l);
      return l;
    }
    
    int *adj_v = graph->adjacency[v];
    int degree_v = 0;
    for(int j=0; j<graph->adj_size[v]; j++){
      int u = adj_v[j];
	  
      if(OUT & graph->mark[u])
	continue;

      degree_v++;
      graph->mark[u] |= MARKED;
    }
    graph->mark[v] |= MARKED;

    for(int j=0; j<graph->adj_size[v]; j++) {
      int u = adj_v[j];

      if(OUT & graph->mark[u])
	continue;

      int *adj_u = graph->adjacency[u];

      int degree_uv = 0;
      for(int i=0; i<graph->adj_size[u]; i++){
	if(MARKED & graph->mark[adj_u[i]])
	  degree_uv++;
      }
	  
      if(degree_v == degree_uv){
	graph->mark[u] |= OUT;
	graph->mark[u] |= MARKED;
	graph->mark[u] ^= MARKED;
	push(u, deleted);

	for(int i=0; i<graph->adj_size[u]; i++){
	  int x = adj_u[i];
	  if((OUT | TO_CHECK) & graph->mark[x])
	    continue;
	  graph->mark[x] |= TO_CHECK;
	  push(x, pile);
	}
	      
	degree_v--;
	j = -1;
      }
    }
      
    for(int j=0; j<graph->adj_size[v]; j++){
      int u = adj_v[j];
      graph->mark[u] |= MARKED;
      graph->mark[u] ^= MARKED;
    }
    graph->mark[v] ^= MARKED;
    graph->mark[v] ^= TO_CHECK;
  }

  return apply_to_components();
}

Array* apply_to_components()
{
  int mem = deleted->size;
  
  for(int u0=0; u0<graph->size; u0++){
    if(OUT & graph->mark[u0])
      continue;
      
    push(-1, deleted);
      
    graph->mark[u0] |= OUT;
    push(u0, deleted);
    push(u0, pile);
    while(pile->size != 0){
      int u = pop(pile);

      int *adj_u = graph->adjacency[u];
      for(int i=0; i<graph->adj_size[u]; i++){
	int v = adj_u[i];

	if(OUT & graph->mark[v])
	  continue;
		
	graph->mark[v] |= OUT;
	push(v, deleted);
	push(v, pile);
      }
    }
  }

  Array *l = new_array();

  int i = deleted->size-1;
  while(mem <= i){
    for(int j=i; deleted->t[j] != -1; j--){
      graph->mark[deleted->t[j]] ^= OUT;
    }

    conc(core(), l);
      
    while(deleted->t[i] != -1){
      graph->mark[deleted->t[i]] |= OUT;
      i--;
    }
    i--;
  }

  while(deleted->size != mem){
    int u = pop(deleted);
    if(u != -1)
      graph->mark[u] ^= OUT;
  }
  
  return l;
}

void vertex_out()
{
  while(to_delete->size != 0){
    int u = pop(to_delete);

    if(OUT & graph->mark[u])
      continue;
      
    graph->mark[u] |= OUT;
    push(u, deleted);
      
    int *adj_u = graph->adjacency[u];
    for(int i=0; i<graph->adj_size[u]; i++){
      int v = adj_u[i];
      if((OUT | TO_CHECK) & graph->mark[v])
	continue;
      graph->mark[v] |= TO_CHECK;
      push(v, pile);
    }
  }
}
