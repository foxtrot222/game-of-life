#ifndef FUNCS_H
#define FUNCS_H

void print_cell(bool alive);
bool update(int neighbours, bool status);
void wait(int delay);
int count_neighbours(bool** neighbourhood , int i, int j, int rows, int cols);
void clear_neighbourhood(bool** neighbourhood, int rows);
void draw(bool** neighbourhood, int rows, int cols);
void init_ncurses();
bool **create_neighbourhood(int rows, int cols);
void init_neighbourhood(bool **neighbourhood, int rows, int cols);
void simulate(bool **current_neigbourhood, bool** updated_neighbourhood, int rows, int cols);
void print_neighbourhood(bool **neighbourhood, int rows, int cols);
  
#endif
