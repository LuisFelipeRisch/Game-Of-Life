#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define NEIGHBORHOOD_SIZE 8
#define SATISFIABLE "SATISFIABLE"
#define UNSATISFIABLE "UNSATISFIABLE"
#define OPTIMUM_FOUND "OPTIMUM FOUND"

typedef enum CellStates CellStates;
typedef struct GameOfLifeInstance GameOfLifeInstance;
typedef struct Neighborhood Neighborhood;
typedef struct SetOfSubsets SetOfSubsets;
typedef struct GlobalNeighborhoodIdentifiers GlobalNeighborhoodIdentifiers;

enum CellStates {
  UNKNOWN = -1,
  DEAD    = 0, 
  ALIVED  = 1,
};

struct GameOfLifeInstance {
  int n; // lines
  int m; // columns

  CellStates** board;
};

struct Neighborhood{
  int my_x; 
  int my_y;
  int my_identifier;

  int my_neighbors_identifiers[NEIGHBORHOOD_SIZE];
  CellStates* my_neighbors_state;
};

struct SetOfSubsets{
  int subsets_count;
  int subsets_size;

  int** subsets;
};

struct GlobalNeighborhoodIdentifiers
{
  int n; // lines 
  int m; // columns

  int** identifiers;
};


#endif