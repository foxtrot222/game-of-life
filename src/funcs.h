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

bool **create_neighbourhood(config cfg);

void init_neighbourhood(bool **neighbourhood, config cfg);

void clear_neighbourhood(bool **neighbourhood, int rows);

void wait(int delay);

void print_cell(bool alive);

bool update(int neighbours, bool status);

void draw(bool **neighbourhood, config cfg);

int count_neighbours(bool **neighbourhood, int i, int j, config cfg);

void simulate(bool **current_neigbourhood, bool **updated_neighbourhood,config cfg);

void print_neighbourhood(bool **neighbourhood, config cfg);

#endif
