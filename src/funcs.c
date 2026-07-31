/*
 * SPDX-FileCopyrightText: 2026 Tirth Kavathiya <tirthkavathiya@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include "funcs.h"

void print_cell(bool status) {
  if (status) {
    printw("\u2588");
  }
  else {
    printw(" ");
  }
}

bool update(int adjacent_cells, bool status) {
  if ( !status && adjacent_cells == 3 ) {
    return true;
  }
  else if ( status && (adjacent_cells == 2 || adjacent_cells == 3) ) {
    return true;
  }
  else {
    return false;
  }
}

void wait(int delay) {
  refresh();
  napms(delay);
}

int count_adjacent_cells(bool** grid , int i, int j, config cfg) {
  int adjacent_cells = 0;
  int offsets[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                       {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  for (int k = 0; k < 8; k++) {
    int ni = i + offsets[k][0];
    int nj = j + offsets[k][1];
    if (cfg.toroidal) {
      ni = (ni + cfg.rows) % cfg.rows;
      nj = (nj + cfg.cols) % cfg.cols;
    } else if (ni < 0 || nj < 0 || ni >= cfg.rows || nj >= cfg.cols) {
      continue;
    }
    if (grid[ni][nj])
      adjacent_cells++;
  }

  return adjacent_cells;
}

void clear_grid(bool** grid, int rows) {
  for ( int i = 0 ; i < rows ; i++ ) {
    free(grid[i]);
  }
  free(grid);
}

void draw(bool** grid, config cfg) {
  curs_set(1);
  int y = 0 , x = 0;
  int ch;
  while (1) {
    ch = getch();
    if ( ch == KEY_UP) {
      if (y > 0) y--;
    }
    if ( ch == KEY_DOWN) {
      if (y < cfg.rows - 1) y++;
    }
    if ( ch == KEY_LEFT) {
      if (x > 0) x--;
    }
    if ( ch == KEY_RIGHT) {
      if (x < cfg.cols - 1) x++;
    }
    if ( ch == 'a' ) {
      grid[y][x] = true;
      print_cell(true);
    }
    if ( ch == 'd' ) {
      grid[y][x] = false;
      print_cell(false);
    }
    if ( ch == '\n' ) {
      break;
    }
    if ( ch == 'q' ) {
      clear_grid(grid, cfg.rows);
      refresh();
      endwin();
      exit(0);
    }
    move(y,x);
    napms(10);
  }
  curs_set(0);
}

void init_ncurses() {
  setlocale(LC_ALL, "");

  if (initscr() == NULL) {
    fprintf(stderr, "Error initializing ncurses.\n");
    exit(1);
  }

  nodelay(stdscr, TRUE);
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  clear();
}

bool **create_grid(config cfg) {
  bool **grid = malloc(cfg.rows * sizeof(bool*));
  if (!grid) {
    endwin();
    fprintf(stderr, "Memory allocation failed.\n");
    exit(1);
  }

  for (int i = 0; i < cfg.rows; i++) {
    grid[i] = malloc(cfg.cols * sizeof(bool));
    if (!grid[i]) {
      endwin();
      fprintf(stderr, "Memory allocation failed.\n");
      exit(1);
    }
  }

  return grid;
}

void init_grid(bool **grid, config cfg) {
  for (int i = 0 ; i < cfg.rows ; i++ ) {
    for (int j = 0 ; j < cfg.cols ; j++) {
      grid[i][j] = false;
    }
  }
}

void simulate(bool **current_grid, bool** updated_grid, config cfg) {
  for (int i = 0 ; i < cfg.rows ; i++ ) {
    for (int j = 0 ; j < cfg.cols ; j++) {
      int adjacent_cells = count_adjacent_cells(current_grid, i, j, cfg);
      updated_grid[i][j] = update(adjacent_cells, current_grid[i][j]);
    }
  }
}

void print_grid(bool **grid, config cfg) {
  for (int i = 0 ; i < cfg.rows ; i++ ) {
    for (int j = 0 ; j < cfg.cols ; j++ ) {
      move(i,j);
      print_cell(grid[i][j]);
    }
  }
}
