#include <stdio.h>
#include <stdlib.h>
#include "src/definitions.h"
#include "src/game_of_life.h"

int main(){
  int n, m;
  GameOfLifeInstance* current_instance, *immediately_previous_sate;

  fprintf(stdout, "Reading the board dimensions...\n");
  read_board_dimensions(&n, &m);

  current_instance = create_game_of_life_instance(n, m);

  fprintf(stdout, "Reading the board entirely...\n");
  read_board_entirely(current_instance);

  fprintf(stdout, "Here it's the given board...\n");
  print_game_of_life_instance(current_instance);

  immediately_previous_sate = compute_immediately_previous_sate(current_instance);

  print_game_of_life_instance(immediately_previous_sate);

  if (valid_previous_game_of_life_instance(immediately_previous_sate, current_instance))
    fprintf(stdout, "VALID!\n");
  else
    fprintf(stdout, "INAVLID!\n");  

  memory_free_game_of_life_instance(current_instance);
  memory_free_game_of_life_instance(immediately_previous_sate);

  return 0;
}