#ifndef _def_array
#define _def_array

#include "stdlib.h"
#include "stdio.h"

typedef struct Array{
  int *t;
  int size, capacity;
} Array;

Array* new_array();
void push(int, Array*);
int pop(Array*);
void free_array(Array*);
void conc(Array*, Array*);
int compare_int(const void*, const void*);
void sort_array(Array*);
void write_array(Array*, char*);

#endif
