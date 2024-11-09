#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

void check_allocation(void* ptr);
void read_board_dimensions(uint* n, uint* m);
void read_board_entirely(GameOfLifeInstance* instance);

#endif