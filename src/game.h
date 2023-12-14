#ifndef GAME_H
#define GAME_H
#include <stdbool.h>
#include <stdlib.h>

enum life { dead, alive };


// While conway's game of life is a endless simulation, we will loop the bounds
extern int simulationBoundX, simulationBoundY;
extern bool **simulationBoard;
extern long iterationCount;
// Initalizes the simulation bounds and board
int initalizeSimulation(int x, int y);
// Resize the simulation bounds, this is left unimplemented for now as I am NOT
// dealing with that headache yet
int resizeSimulationBounds(int x, int y);

void iterateSimulation();
int countCell(int x, int y);
bool accessCellWrap(int x, int y);

void setCell(int x, int y, bool life);
int freeGame();

#endif
