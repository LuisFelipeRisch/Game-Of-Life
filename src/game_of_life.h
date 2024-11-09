#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "utils.h"

GameOfLifeInstance* create_game_of_life_instance(uint n, uint m);
void print_game_of_life_instance(GameOfLifeInstance* instance);
void memory_free_game_of_life_instance(GameOfLifeInstance* instance);
GameOfLifeInstance* compute_immediately_previous_sate(GameOfLifeInstance* instance);

#endif