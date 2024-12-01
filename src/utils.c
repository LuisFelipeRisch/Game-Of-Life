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

      if(!cell_value) {
        instance->board[i][j] = DEAD;
        instance->dead_cells_count += 1;
      }
      else {
        instance->board[i][j] = ALIVED;
        instance->alived_cells_count += 1;
      }
    }
}

int outside_the_board_limits(int i, int j, int n, int m){
  return i < 0 || i >= n || j < 0 || j >= m; 
}

void update_neighborhood(Neighborhood* neighborhood, GameOfLifeInstance* instance, GlobalNeighborhoodIdentifiers* global_neighborhood_identifiers, int x, int y){
  int counter = -1;

  neighborhood->my_identifier = global_neighborhood_identifiers->identifiers[x + 1][y + 1];

  for (int i = x - 1; i <= x + 1; i++)
    for (int j = y - 1; j <= y + 1; j++)
    {
      if(i == x && j == y)
        continue;

      counter++;
      
      neighborhood->my_neighbors_identifiers[counter] = global_neighborhood_identifiers->identifiers[i + 1][j + 1];
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

void fill_bcnf_file_header(FILE* bcnf_file, int quantity_of_clauses, int quantity_of_literals, int top_weight){
  fprintf(bcnf_file, "p wcnf %d %d %d\n", quantity_of_clauses, quantity_of_literals, top_weight);
}

void get_identifier_positions_from_global_identifiers(GlobalNeighborhoodIdentifiers* global_identifiers, int desired_identifier, int* x, int* y) {
  int i, j, actual_desired_identifier, found;

  actual_desired_identifier = desired_identifier; 
  if (actual_desired_identifier < 0)
    actual_desired_identifier *= -1;

  found = 0;

  *x = -1; 
  *y = -1;

  for (i = 0; i < global_identifiers->n && !found; i++)
    for (j = 0; j < global_identifiers->m && !found; j++)
    {
      if (actual_desired_identifier == global_identifiers->identifiers[i][j]){
        found = 1; 
        *(x) = i; 
        *(y) = j;
      }
    }
}

void fill_bcnf_file_with_board_limit(FILE* bcnf_file, GlobalNeighborhoodIdentifiers* global_identifiers, int top_weight) {
  int i, n, m; 

  n = global_identifiers->n; 
  m = global_identifiers->m; 

  for (i = 0; i < m; i++){
    fprintf(bcnf_file, "%d -%d 0\n", top_weight, global_identifiers->identifiers[0][i]);
    fprintf(bcnf_file, "%d -%d 0\n", top_weight, global_identifiers->identifiers[n - 1][i]);
  }

  for (i = 0; i < n; i++){
    fprintf(bcnf_file, "%d -%d 0\n", top_weight, global_identifiers->identifiers[i][0]);
    fprintf(bcnf_file, "%d -%d 0\n", top_weight, global_identifiers->identifiers[i][m - 1]);
  }
}

int compute_total_amount_of_clauses(int alived_cells, int dead_cells, int quantity_of_literals) {
  int c_2 = C(NEIGHBORHOOD_SIZE, 2); 

  return (C(NEIGHBORHOOD_SIZE, 7) + c_2 + C(NEIGHBORHOOD_SIZE, 4)) * alived_cells +
         (c_2 + C(NEIGHBORHOOD_SIZE, 3)) * dead_cells + 
         quantity_of_literals + 4; // esse mais 4 é porque quando eu crio as cláusulas da borda do tabuleiro, eu estou computando duas vezes os cantos (0, 0), (0, m-1), (n-1, 0) e (n-1, m-1)
}


