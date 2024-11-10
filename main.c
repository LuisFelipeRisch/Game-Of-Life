#include <stdio.h>
#include <stdlib.h>
#include "src/definitions.h"
#include "src/game_of_life.h"

int main(){
  int n, m;
  GameOfLifeInstance* initial_instance, *immediately_previous_sate;

  fprintf(stdout, "Reading the board dimensions...\n");
  read_board_dimensions(&n, &m);

  initial_instance = create_game_of_life_instance(n, m);

  fprintf(stdout, "Reading the board entirely...\n");
  read_board_entirely(initial_instance);

  fprintf(stdout, "Here it's the given board...\n");
  print_game_of_life_instance(initial_instance);

  immediately_previous_sate = compute_immediately_previous_sate(initial_instance);

  memory_free_game_of_life_instance(initial_instance);
  memory_free_game_of_life_instance(immediately_previous_sate);

  return 0;
}