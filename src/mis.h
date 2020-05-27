#ifndef _def_mis
#define _def_mis

#include "graph.h"
#include "array.h"

// mis.c
Array *mis(Graph *);

Array *core();

Array *check();

Array *apply_to_components();

void vertex_out();

// fold.c
char is_folding(int);

void fold(int);

void add_tild(int, int, int);

void unfold(int, int);

// mirror.c
void get_mirrors(int);

char check_delta(int, int);

#endif
