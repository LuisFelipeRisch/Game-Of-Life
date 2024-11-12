#include "utils.h"

void check_allocation(void* ptr){
  if (ptr) return; 
  
  fprintf(stderr, "Failed to allocate memory!\n"); 
  exit(EXIT_FAILURE);
}

void read_board_dimensions(int* n, int* m){
  if (scanf("%d %d", n, m) != 2) {
    fprintf(stderr, "Could't read the board dimensions! Please, check the given entry file!\n");
    exit(EXIT_FAILURE);
  }
};

void read_board_entirely(GameOfLifeInstance* instance){
  int cell_value;
  for (int i = 0; i < instance->n; i++)
    for (int j = 0; j < instance->m; j++){
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

int outside_the_board_limits(int i, int j, int n, int m){
  return i < 0 || i >= n || j < 0 || j >= m; 
}

void update_neighborhood(Neighborhood* neighborhood, GameOfLifeInstance* instance, GlobalNeighborhoodIdentifiers* global_neighborhood_identifiers, int x, int y){
  int counter = -1;

  neighborhood->my_x = x; 
  neighborhood->my_y = y;
  neighborhood->my_identifier = global_neighborhood_identifiers->identifiers[x + 1][y + 1];

  for (int i = x - 1; i <= x + 1; i++)
    for (int j = y - 1; j <= y + 1; j++)
    {
      if(i == x && j == y)
        continue;

      counter++;
      
      neighborhood->my_neighbors_identifiers[counter] = global_neighborhood_identifiers->identifiers[i + 1][j + 1];

      if(outside_the_board_limits(i, j, instance->n, instance->m)){
        neighborhood->my_neighbors_state[counter] = DEAD; 
        continue;
      }

      neighborhood->my_neighbors_state[counter] = instance->board[i][j];
    }
}

int fat(int n){
  if (n == 0 || n == 1) return 1; 
  return n * fat(n - 1);
}

int C(int n, int x){
  return fat(n) / (fat(x) * fat(n - x));
}

SetOfSubsets* compute_set_of_subsets_of_cardinality_x(int* entry_set, int entry_set_size, int subsets_size){
  int subsets_count = C(entry_set_size, subsets_size);

  SetOfSubsets* set = create_set_of_subsets(subsets_count, subsets_size);
  check_allocation(set);

  int aux_subset[subsets_size]; 
  int aux_subset_count = 0;

  compute_subsets(entry_set, entry_set_size, aux_subset, 0, 0, subsets_size, set, &aux_subset_count);

  return set;
}

int set_includes_element(int element, int* set, int set_size){
  int includes = 0;

  for (int i = 0; i < set_size && !includes; i++)
    if (set[i] == element)
      includes = 1;
  
  return includes;
}

void compute_difference_set(int* set_a, int set_a_size, int* set_b, int set_b_size, int* result_set, int* result_set_size){
  *result_set_size = 0; 

  for (int i = 0; i < set_a_size; i++)
    if (!set_includes_element(set_a[i], set_b, set_b_size)){
      result_set[*result_set_size] = set_a[i]; 
      (*result_set_size)++;
    }
}

void fill_bcnf_file_with_neighborhood_values(FILE* bcnf_file, Neighborhood* neighborhood, int* quantity_of_clauses){
  CellStates neighborhood_state;

  for (int i = 0; i < NEIGHBORHOOD_SIZE; i++){
    neighborhood_state = neighborhood->my_neighbors_state[i];
    if (neighborhood_state == UNKNOWN)
      continue;
    
    if (neighborhood_state == ALIVED)
      fprintf(bcnf_file, "%d 0\n", neighborhood->my_neighbors_identifiers[i]); 
    else if (neighborhood_state == DEAD)
      fprintf(bcnf_file, "-%d 0\n", neighborhood->my_neighbors_identifiers[i]);

    (*quantity_of_clauses)++;
  }
}

void fill_bcnf_file_header(FILE* bcnf_file, int quantity_of_literals, int quantity_of_clauses){
  fseek(bcnf_file, 0, SEEK_SET);

  fprintf(bcnf_file, "p cnf %d %d\n", quantity_of_literals, quantity_of_clauses);
}


