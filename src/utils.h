#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "game_of_life.h"

void check_allocation(void* ptr);
void read_board_dimensions(int* n, int* m);
void read_board_entirely(GameOfLifeInstance* instance);
void update_neighborhood(Neighborhood* neighborhood, GameOfLifeInstance* instance, GlobalNeighborhoodIdentifiers* global_neighborhood_identifiers, int x, int y);
int C(int n, int x);
SetOfSubsets* compute_set_of_subsets_of_cardinality_x(int* entry_set, int entry_set_size, int subsets_size);
void fill_bcnf_file_with_neighborhood_values(FILE* bcnf_file, Neighborhood* neighborhood);
void compute_difference_set(int* set_a, int set_a_size, int* set_b, int set_b_size, int* result_set, int* result_set_size);

#endif