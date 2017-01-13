#include "mis.h"

int main(int argc, char *argv[])
{
  if(argc < 2 || argc > 3){
    printf("Error: invalid argument.\n");
    return 1;
  }
  
  Graph *graph = read_graph(argv[1]);

  Array *l = mis(graph);
  free_graph(graph);
  printf("Size of maximum independent set: %d\n", l->size);
  
  if(argc == 3)
    write_array(l, argv[2]);
  
  free_array(l);
  
  return 0;
}
