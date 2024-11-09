#include <stdio.h>
#include <stdlib.h>
#include "src/definitions.h"
#include "src/game_of_life.h"

int main(){
  uint n, m;
  GameOfLifeInstance* initial_instance;

  read_board_dimensions(&n, &m);

  initial_instance = create_game_of_life_instance(n, m);

  print_game_of_life_instance(initial_instance);

  read_board_entirely(initial_instance); 

  print_game_of_life_instance(initial_instance);

  memory_free_game_of_life_instance(initial_instance);
  
  return 0;
}