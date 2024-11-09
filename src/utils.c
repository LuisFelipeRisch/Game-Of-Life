#include "utils.h"

void check_allocation(void* ptr){
  if (ptr) return; 
  
  fprintf(stderr, "Failed to allocate memory!\n"); 
  exit(EXIT_FAILURE);
}

void read_board_dimensions(uint* n, uint* m){
  if (scanf("%d %d", n, m) != 2) {
    fprintf(stderr, "Could't read the board dimensions! Please, check the given entry file!\n");
    exit(EXIT_FAILURE);
  }
};

void read_board_entirely(GameOfLifeInstance* instance){
  uint cell_value;
  for (uint i = 0; i < instance->n; i++)
    for (uint j = 0; j < instance->m; j++){
      if (scanf("%d", &cell_value) != 1) {
        fprintf(stderr, "Could't read the value in the following position (%d, %d).\n", i, j);
        exit(EXIT_FAILURE);
      }

      if(!cell_value)
        instance->board[i][j] = DEAD;
      else 
        instance->board[i][j] = ALIVED;
    }
}