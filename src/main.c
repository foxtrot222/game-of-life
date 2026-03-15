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
  
  while ((opt = getopt(argc, argv, "s:th")) != -1) {
    switch (opt) {
      case 'h':
	printf("Usage: %s [-d delay] [-t] [-h]\n", argv[0]);
	printf(" -d DELAY    Simulation delay time in milliseconds. Default is 100\n");
	printf(" -t          To toggle Toroidal edges. Default is false\n");
        printf(" -h          Show this help message and exit\n");
	printf("How to Play:\n");
	printf("  Use the arrow keys to move the cursor.\n");
	printf("  Press a to toggle cells (make them alive).\n");
	printf("  Press d to toggle cells (make them dead).\n");
	printf("  Once your pattern is ready, press Enter to start the simulation.\n");
	printf("  Press q at any time to quit.\n");
        return 0;
      case 't':
        toroidal = true;
	break;
      case 's':
        delay_tmp = atoi(optarg);
        if (delay_tmp <= 0) {
	  fprintf(stderr, "Invalid Input\n");
	  return 1;
        }
	delay = delay_tmp;
        break;
      default:
        fprintf(stderr, "Unknown option\n");
	return 1;
    }
  }
  
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
