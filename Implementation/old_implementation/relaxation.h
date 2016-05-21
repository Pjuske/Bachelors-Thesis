#ifndef RELAXATION_H
#define RELAXATION_H

#include "dijkstra.h"

void initialize_single_source(vertex graph[], vertex source);
void relax(vertex u, vertex v, int weight);
void print_path(vertex graph[], vertex source, vertex target);
#endif
