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
  move(y-1, 0);
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
  int xMax, yMax, x, y;
  getmaxyx(stdscr, yMax, xMax);
  yMax -= 2;
  getyx(stdscr, y, x);
  if (y + row > yMax) {
    y = 0;
  }
  if (y + row < 0) {
    y = yMax;
  }
  if (x + col > xMax) {
    x = 0;
  }
  if (x + col < 0) {
    x = xMax;
  }
  move(y + row, x + col);
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

  printw("Hello");
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(1);
  int xMax, yMax;
  getmaxyx(stdscr, yMax, xMax);
  initalizeSimulation(xMax, yMax);
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
        iterateSimulation();
        drawGame();
      break;
    }
  }
  endProgram();
  return 0;
}