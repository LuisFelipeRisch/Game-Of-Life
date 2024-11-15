#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "utils.h"

GameOfLifeInstance* create_game_of_life_instance(int n, int m);
void print_game_of_life_instance(GameOfLifeInstance* instance);
void memory_free_game_of_life_instance(GameOfLifeInstance* instance);
GameOfLifeInstance* compute_immediately_previous_sate(GameOfLifeInstance* instance);
void memory_free_set_of_subsets(SetOfSubsets *set); 
SetOfSubsets* create_set_of_subsets(int subsets_count, int subsets_size);
void compute_subsets(int* entry_set, int entry_set_size, int* subset, int subset_size, int start, int desired_subset_size, SetOfSubsets* set, int* subset_count);
int valid_previous_game_of_life_instance(GameOfLifeInstance* previous_instance, GameOfLifeInstance* current_instance);

#endif