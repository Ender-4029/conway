#include "game.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int simulationBoundX, simulationBoundY;
bool **simulationBoard;
bool **newSimBoard;
long iterationCount = 0;


int initalizeSimulation(int y, int x) {
  simulationBoundX = x;
  simulationBoundY = y;
  simulationBoard = (bool **)malloc(x * sizeof(bool *));
  for (int i = 0; i < x; i++) {
    simulationBoard[i] = (bool *)malloc(y * sizeof(bool));
  }

  newSimBoard = (bool **)malloc(simulationBoundX * sizeof(bool *));
  for (int i = 0; i < simulationBoundX; i++) {
    newSimBoard[i] = (bool *)malloc(simulationBoundY * sizeof(bool));
  }

  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      simulationBoard[i][j] = false;
  return 0;
}

void iterateSimulation() {
  iterationCount += 1;

  for (int i = 0; i < simulationBoundX; i++)
    for (int j = 0; j < simulationBoundY; j++)
      newSimBoard[i][j] = false;
  //
  for (int i = 0; i < simulationBoundX; i++) {
    for (int j = 0; j < simulationBoundY; j++) {
      int cellCount = countCell(i, j);
      if (simulationBoard[i][j]) {
        if (cellCount < 2) {
          newSimBoard[i][j] = false;
        } else if (cellCount > 3) {
          newSimBoard[i][j] = false;
        } else {
          newSimBoard[i][j] = true;
        }
      } else if (cellCount == 3) {
        newSimBoard[i][j] = true;
      }
    }
  }
  for (int i = 0; i < simulationBoundX; i++) {
    for (int j = 0; j < simulationBoundY; j++) {
      simulationBoard[i][j] = newSimBoard[i][j];
    }
  }
}

int countCell(int x, int y) {
  int cellCount = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (i != 0 || j != 0) {
        if (accessCellWrap(x + i, y + j)) {
          cellCount += 1;
        }
      }
    }
  }
  return cellCount;
}
bool accessCellWrap(int x, int y) {
  while (x < 0) {
    x += simulationBoundX;
  }

  while (y < 0) {
    y += simulationBoundY;
  }

  while (x >= simulationBoundX) {
    x -= simulationBoundX;
  }

  while (y >= simulationBoundY) {
    y -= simulationBoundY;
  }

  return simulationBoard[x][y];
}
void setCell(int x, int y, bool life) { simulationBoard[x][y] = life; }

int freeGame() {
  for (int i = 0; i < simulationBoundX; i++) {
    free(newSimBoard[i]);
  }
  free(newSimBoard);
  for (int i = 0; i < simulationBoundX; i++) {
    free(simulationBoard[i]);
  }
  free(simulationBoard);
  return 0;
}
