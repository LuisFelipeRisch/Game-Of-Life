#include "game_of_life.h"

GameOfLifeInstance* create_game_of_life_instance(int n, int m){
  GameOfLifeInstance* instance = (GameOfLifeInstance *) malloc(sizeof(GameOfLifeInstance)); 
  check_allocation(instance);

  instance->n = n; 
  instance->m = m;
  instance->alived_cells_count = 0; 
  instance->dead_cells_count = 0;

  instance->board = (CellStates **) malloc(n * sizeof(CellStates *)); 
  check_allocation(instance->board); 

  for (int i = 0; i < n; i++){
    instance->board[i] = (CellStates *) malloc(m * sizeof(CellStates));
    check_allocation(instance->board[i]);

    for (int j = 0; j < m; j++)
      instance->board[i][j] = UNKNOWN; 
  }
  
  return instance;
}

void print_game_of_life_instance(GameOfLifeInstance* instance){
  int n, m, i, j;

  n = instance->n; 
  m = instance->m;

  fprintf(stdout, "%d %d\n", n, m);
  fprintf(stdout, "Alived cells count: %d\n", instance->alived_cells_count);
  fprintf(stdout, "Dead cells count: %d\n", instance->dead_cells_count);
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < m - 1; j++)
      fprintf(stdout, "%d ", instance->board[i][j]);
    fprintf(stdout, "%d\n", instance->board[i][j]);
  }
}

void memory_free_game_of_life_instance(GameOfLifeInstance* instance) {
  for (int i = 0; i < instance->n; i++) free(instance->board[i]);
  free(instance->board);
  free(instance);
}

Neighborhood* create_neighborhood(){
  Neighborhood* neighborhood = (Neighborhood *) malloc(sizeof(Neighborhood));
  check_allocation(neighborhood); 

  return neighborhood; 
}

void memory_free_neighborhood(Neighborhood* neighborhood){
  free(neighborhood);
}

GlobalNeighborhoodIdentifiers* create_global_neighborhood_identifiers(int n, int m){
  GlobalNeighborhoodIdentifiers* neighborhood_identifiers = (GlobalNeighborhoodIdentifiers *) malloc(sizeof(GlobalNeighborhoodIdentifiers));
  check_allocation(neighborhood_identifiers); 

  neighborhood_identifiers->n = n; 
  neighborhood_identifiers->m = m;

  neighborhood_identifiers->identifiers = (int **) malloc(n * sizeof(int *));
  check_allocation(neighborhood_identifiers->identifiers);

  int current_identifier = 1; 
  for (int i = 0; i < n; i++){
    neighborhood_identifiers->identifiers[i] = (int *) malloc(m * sizeof(int));
    check_allocation(neighborhood_identifiers->identifiers[i]);

    for (int j = 0; j < m; j++)
      neighborhood_identifiers->identifiers[i][j] = current_identifier++; 
  }
  
  return neighborhood_identifiers;
}

void memory_free_global_neighborhood_identifiers(GlobalNeighborhoodIdentifiers* neighborhood_identifiers){
  for (int i = 0; i < neighborhood_identifiers->n; i++) free(neighborhood_identifiers->identifiers[i]);

  free(neighborhood_identifiers->identifiers); 
  free(neighborhood_identifiers);
}

void loneliness(FILE* bcnf_file, SetOfSubsets* set, Neighborhood* _neighborhoodm, int top_weight){
  int i, j, n, m; 

  n = set->subsets_count; 
  m = set->subsets_size;

  for (i = 0; i < n; i++)
  {
    fprintf(bcnf_file, "%d ", top_weight);
    for (j = 0; j < m - 1; j++)
      fprintf(bcnf_file, "%d ", set->subsets[i][j]);
    fprintf(bcnf_file, "%d 0\n", set->subsets[i][j]);
  }
}

void stagnation(FILE* bcnf_file, SetOfSubsets* set, Neighborhood* neighborhood, int top_weight){
  int difference_set[NEIGHBORHOOD_SIZE];
  int difference_set_size, i, j, n, m; 

  n = set->subsets_count; 
  m = set->subsets_size;

  for (i = 0; i < n; i++)
  {
    fprintf(bcnf_file, "%d %d ", top_weight, neighborhood->my_identifier);
    for (j = 0; j < m; j++)
      fprintf(bcnf_file, "-%d ", set->subsets[i][j]);
    
    compute_difference_set(neighborhood->my_neighbors_identifiers, NEIGHBORHOOD_SIZE, set->subsets[i], m, difference_set, &difference_set_size);
    for (j = 0; j < difference_set_size - 1; j++)
      fprintf(bcnf_file, "%d ", difference_set[j]);
    fprintf(bcnf_file, "%d 0\n", difference_set[j]);
  }
}

void overcrowding(FILE* bcnf_file, SetOfSubsets* set, Neighborhood* _neighborhood, int top_weight){
  int i, j, n, m; 

  n = set->subsets_count; 
  m = set->subsets_size;

  for (i = 0; i < n; i++)
  {
    fprintf(bcnf_file, "%d ", top_weight);
    for (j = 0; j < m - 1; j++)
      fprintf(bcnf_file, "-%d ", set->subsets[i][j]);
    fprintf(bcnf_file, "-%d 0\n", set->subsets[i][j]);
  }
}

void preservation(FILE* bcnf_file, SetOfSubsets* set, Neighborhood* neighborhood, int top_weight){
  int difference_set[NEIGHBORHOOD_SIZE];
  int difference_set_size, i, j, n, m; 

  n = set->subsets_count; 
  m = set->subsets_size;

  for (i = 0; i < n; i++)
  {
    fprintf(bcnf_file, "%d -%d ", top_weight, neighborhood->my_identifier);
    for (j = 0; j < m; j++)
      fprintf(bcnf_file, "-%d ", set->subsets[i][j]);
    
    compute_difference_set(neighborhood->my_neighbors_identifiers, NEIGHBORHOOD_SIZE, set->subsets[i], m, difference_set, &difference_set_size);
    for (j = 0; j < difference_set_size - 1; j++)
      fprintf(bcnf_file, "%d ", difference_set[j]);
    fprintf(bcnf_file, "%d 0\n", difference_set[j]);
  }
}

void life(FILE* bcnf_file, SetOfSubsets* set, Neighborhood* neighborhood, int top_weight){
  int difference_set[NEIGHBORHOOD_SIZE];
  int difference_set_size, i, j, n, m; 

  n = set->subsets_count; 
  m = set->subsets_size;

  for (i = 0; i < n; i++)
  {
    fprintf(bcnf_file, "%d ", top_weight);
    for (j = 0; j < m; j++)
      fprintf(bcnf_file, "-%d ", set->subsets[i][j]);
    
    compute_difference_set(neighborhood->my_neighbors_identifiers, NEIGHBORHOOD_SIZE, set->subsets[i], m, difference_set, &difference_set_size);
    for (j = 0; j < difference_set_size - 1; j++)
      fprintf(bcnf_file, "%d ", difference_set[j]);
    fprintf(bcnf_file, "%d 0\n", difference_set[j]);
  }
} 

GameOfLifeInstance* compute_immediately_previous_sate(GameOfLifeInstance* instance){
  GameOfLifeInstance* previous_instance_state;
  Neighborhood* neighborhood;
  FILE *bcnf_file, *sat_solver_output;
  GlobalNeighborhoodIdentifiers* global_neighborhood_identifiers;
  SetOfSubsets *set_of_subsets_of_cardinality_7, *set_of_subsets_of_cardinality_2, 
               *set_of_subsets_of_cardinality_4, *set_of_subsets_of_cardinality_3;
  int i, j, n, m;
  int quantity_of_literals, top_weight;

  n = instance->n;
  m = instance->m;

  quantity_of_literals = (n + 2) * (m + 2);
  top_weight = (n + 2) * (m + 2);

  bcnf_file = fopen("bcnf.txt", "w");
  check_allocation(bcnf_file);

  previous_instance_state = create_game_of_life_instance(n, m);
  neighborhood = create_neighborhood();
  global_neighborhood_identifiers = create_global_neighborhood_identifiers(n + 2, m + 2);

  fill_bcnf_file_header(bcnf_file, 
                        compute_total_amount_of_clauses(instance->alived_cells_count, instance->dead_cells_count, quantity_of_literals), 
                        quantity_of_literals, 
                        top_weight);
  fill_bcnf_file_with_board_limit(bcnf_file, 
                                  global_neighborhood_identifiers, 
                                  top_weight);

  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
    {
      update_neighborhood(neighborhood, previous_instance_state, global_neighborhood_identifiers, i, j);

      set_of_subsets_of_cardinality_2 = compute_set_of_subsets_of_cardinality_x(neighborhood->my_neighbors_identifiers, NEIGHBORHOOD_SIZE, 2);

      if (instance->board[i][j] == ALIVED){
        set_of_subsets_of_cardinality_7 = compute_set_of_subsets_of_cardinality_x(neighborhood->my_neighbors_identifiers, NEIGHBORHOOD_SIZE, 7);
        set_of_subsets_of_cardinality_4 = compute_set_of_subsets_of_cardinality_x(neighborhood->my_neighbors_identifiers, NEIGHBORHOOD_SIZE, 4);

        loneliness(bcnf_file, set_of_subsets_of_cardinality_7, neighborhood, top_weight);
        stagnation(bcnf_file, set_of_subsets_of_cardinality_2, neighborhood, top_weight);
        overcrowding(bcnf_file, set_of_subsets_of_cardinality_4, neighborhood, top_weight);

        memory_free_set_of_subsets(set_of_subsets_of_cardinality_7);
        memory_free_set_of_subsets(set_of_subsets_of_cardinality_4);
      } else if (instance->board[i][j] == DEAD){
        set_of_subsets_of_cardinality_3 = compute_set_of_subsets_of_cardinality_x(neighborhood->my_neighbors_identifiers, NEIGHBORHOOD_SIZE, 3);

        preservation(bcnf_file, set_of_subsets_of_cardinality_2, neighborhood, top_weight);
        life(bcnf_file, set_of_subsets_of_cardinality_3, neighborhood, top_weight);

        memory_free_set_of_subsets(set_of_subsets_of_cardinality_3);
      }

      fprintf(bcnf_file, "1 -%d 0\n", global_neighborhood_identifiers->identifiers[i + 1][j + 1]);
      memory_free_set_of_subsets(set_of_subsets_of_cardinality_2);
    }
  
  fclose(bcnf_file);

  char buffer[4024];

  system("./open-wbo/open-wbo bcnf.txt > out.txt");

  sat_solver_output = fopen("out.txt", "r"); 
  check_allocation(sat_solver_output);

  while (fgets(buffer, sizeof(buffer), sat_solver_output)) {
    if (buffer[0] == 's') {
      if (strstr(buffer, UNSATISFIABLE) != NULL){
        fprintf(stderr, "\nThe given board is %s\n\n", UNSATISFIABLE);
        exit(EXIT_FAILURE);
      } else if (strstr(buffer, SATISFIABLE) != NULL)
          fprintf(stdout, "\nThe given board is %s, but the solution found was not optimality proven\n\n", SATISFIABLE);
        else if (strstr(buffer, OPTIMUM_FOUND) != NULL) 
          fprintf(stdout, "\nThe given board is %s and an optimum solution was found!\n\n", SATISFIABLE);
    } else if (buffer[0] == 'v') {
      char *token; 
      int x, y, literal_value;

      token = strtok(buffer + 1, " \t\n");

      while (token != NULL) {
        literal_value = atoi(token);

        get_identifier_positions_from_global_identifiers(global_neighborhood_identifiers, literal_value, &x, &y); 

        if(x == -1 || y == -1){
          fprintf(stderr, "Unknown Literal! %d", literal_value); 
          exit(EXIT_FAILURE);
        }

        x--; 
        y--;

        if (outside_the_board_limits(x, y, n, m)){
          token = strtok(NULL, " \t\n");
          continue;
        }
        
        if (literal_value < 0) {
          previous_instance_state->board[x][y] = DEAD; 
          previous_instance_state->dead_cells_count += 1;
        } else {
          previous_instance_state->board[x][y] = ALIVED; 
          previous_instance_state->alived_cells_count += 1;
        }


        token = strtok(NULL, " \t\n");
      }
    }
  }

  fclose(sat_solver_output);

  memory_free_neighborhood(neighborhood);
  memory_free_global_neighborhood_identifiers(global_neighborhood_identifiers);

  return previous_instance_state;
}

SetOfSubsets* create_set_of_subsets(int subsets_count, int subsets_size){
  SetOfSubsets* set = (SetOfSubsets *) malloc(sizeof(SetOfSubsets));
  check_allocation(set);

  set->subsets_count = subsets_count; 
  set->subsets_size = subsets_size;

  set->subsets = (int **) malloc(subsets_count * sizeof(int *));
  check_allocation(set->subsets);

  for (int i = 0; i < subsets_count; i++)
  {
    set->subsets[i] = (int *) malloc(subsets_size * sizeof(int));
    check_allocation(set->subsets[i]);
  }
  
  return set;
}

void memory_free_set_of_subsets(SetOfSubsets *set){
  for (int i = 0; i < set->subsets_count; i++) free(set->subsets[i]);
  free(set->subsets);
  free(set);
}

void compute_subsets(int* entry_set, int entry_set_size, int* subset, int subset_size, int start, int desired_subset_size, SetOfSubsets* set, int* subset_count) {
  if (subset_size == desired_subset_size) {
    for (int i = 0; i < desired_subset_size; i++)
      set->subsets[*subset_count][i] = subset[i];

    (*subset_count)++;
    return;
  }

  for (int i = start; i < entry_set_size; i++) {
    subset[subset_size] = entry_set[i];
    compute_subsets(entry_set, entry_set_size, subset, subset_size + 1, i + 1, desired_subset_size, set, subset_count);
  }
}

int count_living_neighbors(GameOfLifeInstance *instance, int x, int y){
  int i, j, n, m, count;

  count = 0; 
  n = instance->n; 
  m = instance->m; 

  for (i = x - 1; i <= x + 1; i++)
    for (j = y - 1; j <= y + 1; j++)
    {
      if (i == x && j == y)
        continue;

      if (outside_the_board_limits(i, j, n, m))
        continue;
      
      if (instance->board[i][j] == ALIVED)
        count++;
    }

  return count;
}

int valid_previous_game_of_life_instance(GameOfLifeInstance* previous_instance, GameOfLifeInstance* current_instance) {
  int i, j, n, m, valid, current_living_neighbors_count; 

  n = previous_instance->n; 
  m = previous_instance->m; 
  valid = 1;

  for (i = 0; i < n && valid; i++)
    for (j = 0; j < m && valid; j++)
    {
      current_living_neighbors_count = count_living_neighbors(previous_instance, i, j);

      if (previous_instance->board[i][j] == ALIVED) {
        if ((current_living_neighbors_count < 2 || current_living_neighbors_count > 3) && current_instance->board[i][j] == ALIVED)
          valid = 0;
        else if ((current_living_neighbors_count == 2 || current_living_neighbors_count == 3) && current_instance->board[i][j] == DEAD)
          valid = 0;
      } else if (previous_instance->board[i][j] == DEAD){
        if (current_living_neighbors_count == 3 && current_instance->board[i][j] == DEAD)
          valid = 0;
      }
    }
  
  return valid;
}

