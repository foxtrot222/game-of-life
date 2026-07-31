/*
 * SPDX-FileCopyrightText: 2026 Tirth Kavathiya <tirthkavathiya@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef FUNCS_H
#define FUNCS_H

typedef struct {
  int rows;
  int cols;
  int delay;
  bool toroidal;
} config;

void init_ncurses();

bool **create_grid(config cfg);

void init_grid(bool **grid, config cfg);

void clear_grid(bool **grid, int rows);

void wait(int delay);

void print_cell(bool alive);

bool update(int adjacent_cells, bool status);

void draw(bool **grid, config cfg);

int count_adjacent_cells(bool **grid, int i, int j, config cfg);

void simulate(bool **current_grid, bool **updated_grid,config cfg);

void print_grid(bool **grid, config cfg);

#endif
