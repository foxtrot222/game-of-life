/*
 * SPDX-FileCopyrightText: 2025 Tirth Kavathiya <tirthkavathiya@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>
#include "funcs.h"

int main(int argc, char **argv) {
  int opt,delay_tmp;
  int delay = 100;
  bool toroidal = true;
  
  init_ncurses();
  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  bool **current_neighbourhood = create_neighbourhood(rows, cols);
  bool **updated_neighbourhood = create_neighbourhood(rows, cols);

  init_neighbourhood(current_neighbourhood, rows, cols);
  draw(current_neighbourhood, rows, cols);
  
  while (1) {
    wait(delay);

    simulate(current_neighbourhood, updated_neighbourhood, rows, cols, toroidal);
    
    bool** temp = current_neighbourhood;
    current_neighbourhood = updated_neighbourhood;
    updated_neighbourhood = temp;

    print_neighbourhood(current_neighbourhood, rows, cols);
    
    int ch = getch();
    if ( ch == 'q') {
        break;
    }
  }

  clear_neighbourhood(current_neighbourhood, rows);
  clear_neighbourhood(updated_neighbourhood, rows);
  refresh();
  endwin();
  return 0;
}
