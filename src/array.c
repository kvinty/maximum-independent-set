#include "array.h"

Array* new_array()
{
  Array *array = (struct Array*) malloc(sizeof(struct Array));
  array->t = (int*) malloc(sizeof(int));
  array->size = 0;
  array->capacity = 1;
  return array;
}

void push(int x, Array* array)
{
  if(array->size == array->capacity){
    int *t = array->t;
    int *new_t = (int*) malloc((array->capacity<<1)*sizeof(int));
    for(int i=0; i<array->size; i++)
      new_t[i] = t[i];
    free(t);
    array->t = new_t;
    array->capacity <<= 1;
  }
  array->t[array->size] = x;
  array->size++;
}

int pop(Array* array)
{
  array->size--;
  return array->t[array->size];
}

void free_array(Array* array)
{
  free(array->t);
  free(array);
}

void conc(Array* a, Array* b)
{
  int new_capacity = b->capacity;
  while(new_capacity < a->size + b->size)
    new_capacity <<= 1;

  if(new_capacity != b->capacity){
    int *t = b->t;
    int *new_t = (int*) malloc(new_capacity*sizeof(int));
    for(int i=0; i<b->size; i++){
      new_t[i] = t[i];
    }
    free(t);
    b->t = new_t;
    b->capacity = new_capacity;
  }
  
  while(a->size != 0)
    push(pop(a), b);
  
  free_array(a);
}

int compare_int(const void* a, const void* b)
{
  const int *c = (const int*) a;
  const int *d = (const int*) b;
  return (*c > *d) - (*c < *d);
}

void sort_array(Array* array)
{
  int *t = array->t;
  int size = array->size;
  
  qsort(t, size, sizeof(int), compare_int);
}

void write_array(Array* l, char* filename)
{ 
  FILE *file = fopen(filename, "w+");
  if(file == NULL){
    printf("Error: unable to write to output file\n");
    exit(1);
  }

  sort_array(l);
  for(int i=0; i<l->size; i++)
    fprintf(file, "%d\n", l->t[i]);

  fclose(file);
}
