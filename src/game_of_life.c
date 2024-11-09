#include "game_of_life.h"

GameOfLifeInstance* create_game_of_life_instance(uint n, uint m){
  GameOfLifeInstance* instance = (GameOfLifeInstance *) malloc(sizeof(GameOfLifeInstance)); 
  check_allocation(instance);

  instance->n = n; 
  instance->m = m; 

  instance->board = (CellStates **) malloc(n * sizeof(CellStates *)); 
  check_allocation(instance->board); 

  for (uint i = 0; i < n; i++){
    instance->board[i] = (CellStates *) malloc(m * sizeof(CellStates));
    check_allocation(instance->board[i]);

    for (uint j = 0; j < m; j++)
      instance->board[i][j] = UNKNOWN; 
  }
  
  return instance;
}

void print_game_of_life_instance(GameOfLifeInstance* instance){
  uint n, m, i, j;

  n = instance->n; 
  m = instance->m;

  fprintf(stdout, "%d %d\n", n, m);
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < m - 1; j++)
      fprintf(stdout, "%d ", instance->board[i][j]);
    fprintf(stdout, "%d\n", instance->board[i][j]);
  }
}

void memory_free_game_of_life_instance(GameOfLifeInstance* instance) {
  for (uint i = 0; i < instance->n; i++) free(instance->board[i]);
  free(instance->board);
  free(instance);
}

GameOfLifeInstance* compute_immediately_previous_sate(GameOfLifeInstance* instance){
  GameOfLifeInstance* previous_instance_state;
  uint n, m; 

  n = instance->n; 
  m = instance->m;

  previous_instance_state = create_game_of_life_instance(n, m);
  check_allocation(previous_instance_state); 

  return previous_instance_state;
}

