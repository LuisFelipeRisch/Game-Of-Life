#ifndef DEFINITIONS_H
#define DEFINITIONS_H

typedef unsigned int uint;
typedef enum CellStates CellStates;
typedef struct GameOfLifeInstance GameOfLifeInstance;

enum CellStates {
  UNKNOWN = -1,
  DEAD    = 0, 
  ALIVED  = 1,
};

struct GameOfLifeInstance {
  uint n; // lines
  uint m; // columns

  CellStates** board;
};

#endif