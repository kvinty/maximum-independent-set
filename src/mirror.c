void get_mirrors(int v)
{
  push(v, pile);
  graph->mark[v] |= VISITED;
  
  int *adj_v = graph->adjacency[v];
  
  for(int j=0; j<graph->adj_size[v]; j++){
    int w = adj_v[j];

    if(OUT & graph->mark[w])
      continue;
      
    graph->mark[w] |= VISITED;
    push(w, pile);	
  }

  for(int j=0; j<graph->adj_size[v]; j++){
    int w = adj_v[j];
      
    if(OUT & graph->mark[w])
      continue;
      
    int *adj_w = graph->adjacency[w];
    for(int k=0; k<graph->adj_size[w]; k++){
      int u = adj_w[k];
  
      if((OUT | VISITED) & graph->mark[u])
	continue;
	  
      if(check_delta(v, u))
	push(u, to_delete);
	  
      graph->mark[u] |= VISITED;
      push(u, pile);
    }
  }

  while(pile->size != 0){
    int u = pop(pile);
    graph->mark[u] |= VISITED;
    graph->mark[u] ^= VISITED;
  }
}

char check_delta(int v, int u)
{
  int *adj_v = graph->adjacency[v];
  int *adj_u = graph->adjacency[u];

  for(int i=0; i<graph->adj_size[u]; i++){
    int x = adj_u[i];
    if(OUT & graph->mark[x])
      continue;
	
    graph->mark[x] |= MARKED;
  }

  char r = 1;
  for(int i=0; i<graph->adj_size[v] && r; i++){
    int x = adj_v[i];
      
    if((OUT | MARKED) & graph->mark[x])
      continue;

    for(int j=i+1; j<graph->adj_size[v] && r; j++){
      int y = adj_v[j];
      if((OUT | MARKED) & graph->mark[y])
	continue;

      r &= are_connected(x, y, graph);
    }
  }

  for(int i=0; i<graph->adj_size[u]; i++){
    int x = adj_u[i];
    graph->mark[x] |= MARKED;
    graph->mark[x] ^= MARKED;
  }
  
  return r;
}
