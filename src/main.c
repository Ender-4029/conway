#include "game.h"
#include <curses.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int endProgram() {
  endwin();
  freeGame();
  exit(0);
  return 0;
}

int drawBottomBar() {
  int x, y;
  getmaxyx(stdscr, y, x);
  for (int i = 0; i < x; i++) {
    move(y - 2, i);
    addch(ACS_BLOCK);
  }
  refresh();
  move(y - 1, 0);
  printw("Iteration Count: %ld", iterationCount);

  return 0;
}
// Macro to safely shift the cursor within bounds
int shiftCursor(int row, int col) {
  int xMax, yMax, x, y;
  getmaxyx(stdscr, yMax, xMax);
  getyx(stdscr, y, x);
  if (y + row > yMax || y + row < 0 || x + col > xMax || x + col < 0) {
    return -1;
  }
  move(y + row, x + col);
  return 0;
}
// Wrapped cursor function to handle cursor movement within simulation bounds,
// assumes row and column are [-1, 1]
void shiftCursorSim(int row, int col) {
  int rowMax, colMax, x, y;
  getmaxyx(stdscr, colMax, rowMax);
  getyx(stdscr, y, x);
  row += y;
  col += x;
  if (row < 0) {
    row = colMax - 3;
  } else if (col < 0) {
    col = rowMax - 1;
  } else if (col >= rowMax) {
    col = 0;
  }

  else if (row >= colMax - 2) {
    row = 0;
  }

  move(row, col);
}

int drawGame() {
  int x, y;
  getyx(stdscr, y, x);
  for (int i = 0; i < simulationBoundX; i++) {
    for (int j = 0; j < simulationBoundY; j++) {
      move(i, j);
      if (simulationBoard[i][j]) {
        addch(ACS_BLOCK);
      } else {
        addch(' ');
      }
    }
  }
  drawBottomBar();
  move(y, x);
  refresh();
  return 0;
}

void setCursorCell() {
  int y, x;
  getyx(stdscr, y, x);
  if (simulationBoard[y][x]) {
    setCell(y, x, false);
  } else {
    setCell(y, x, true);
  }
  drawGame();
}

int main() {
  /*WINDOW *simulationWindow =*/initscr();
  bool simActive = false;
  printw("Hello");
  cbreak();
  noecho();
  halfdelay(1);
  keypad(stdscr, TRUE);
  curs_set(1);
  int xMax, yMax;
  getmaxyx(stdscr, yMax, xMax);
  initalizeSimulation(xMax, yMax - 2);
  drawGame();
  while (true) {
    switch (getch()) {
    case 27:
    case 113:
      endProgram();
      break;
    case KEY_UP:
      shiftCursorSim(-1, 0);
      break;

    case KEY_DOWN:
      shiftCursorSim(1, 0);
      break;

    case KEY_LEFT:
      shiftCursorSim(0, -1);
      break;

    case KEY_RIGHT:
      shiftCursorSim(0, 1);
      break;

    case 32:
      setCursorCell();
      break;
    case KEY_ENTER:
    case '\n':
        simActive = !simActive;
      break;
    }
    if (simActive) {
      iterateSimulation();
      drawGame();
    }
  }
  endProgram();
  return 0;
}