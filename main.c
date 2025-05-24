#include <wchar.h>
#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

void print_cell(bool alive);
bool update(int neighbours, bool status);
void wait();
int count_neighbours(bool** neighbourhood , int i, int j, int rows, int cols);
void clear_neighbourhood(bool** current, bool** updated, int rows, int cols);
void draw(bool** neighbourhood, int rows, int cols);

int main() {
  
  setlocale(LC_ALL, "");
  initscr();
  nodelay(stdscr, TRUE);
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  clear();
  
  int rows, cols, i, j;
  getmaxyx(stdscr, rows, cols);
  int neighbours;
  bool **current_neighbourhood = malloc( rows * sizeof(bool*));
  for ( i = 0 ; i < rows ; i++ ) {
    current_neighbourhood[i] = malloc( cols * sizeof(bool));
  }
  bool **updated_neighbourhood = malloc( rows * sizeof(bool*));
  for ( i = 0 ; i < rows ; i++ ) {
    updated_neighbourhood[i] = malloc( cols * sizeof(bool));
  }
  for ( i = 0 ; i < rows ; i++ ) {
    for ( j = 0 ; j < cols ; j++) {
      current_neighbourhood[i][j] = false;
    }
  }
  
  draw(current_neighbourhood, rows, cols);
  
  while (1) {
    wait();
   
    for ( i = 0 ; i < rows ; i++ ) {
      for ( j = 0 ; j < cols ; j++) {
	neighbours = count_neighbours(current_neighbourhood, i, j, rows, cols);
	updated_neighbourhood[i][j] = update(neighbours, current_neighbourhood[i][j]);
      }
    }

    bool** temp = current_neighbourhood;
    current_neighbourhood = updated_neighbourhood;
    updated_neighbourhood = temp;
    
    for ( i = 0 ; i < rows ; i++ ) {
      for ( j = 0 ; j < cols ; j++ ) {
	move(i,j);
	print_cell(current_neighbourhood[i][j]);
      }
    }
    int ch = getch();
    if ( ch == 'q') {
        break;
    }
   
  }

  clear_neighbourhood(current_neighbourhood, updated_neighbourhood, rows, cols);
  refresh();
  endwin();
  return 0;
}

void print_cell(bool alive) {
  if (alive) {
    printw("\u2588"); 
  }
  else {
    printw(" ");
  }
}

bool update(int neighbours, bool status) {
  if ( !status && neighbours == 3 ) {
    return true;
  }
  else if ( status && (neighbours == 2 || neighbours == 3) ) {
    return true;
  }
  else {
    return false;
  }
}

void wait() {
  refresh();
  napms(100);
}

int count_neighbours(bool** neighbourhood , int i, int j, int rows, int cols) {
  int neighbours = 0;
  if (i < rows - 1 && neighbourhood[i+1][j]) neighbours++;
  if (j < cols - 1 && neighbourhood[i][j+1]) neighbours++;
  if (i > 0 && neighbourhood[i-1][j]) neighbours++;
  if (j > 0 && neighbourhood[i][j-1]) neighbours++;
  if (i < rows - 1 && j < cols - 1 && neighbourhood[i+1][j+1]) neighbours++;
  if (i < rows - 1 && j > 0 && neighbourhood[i+1][j-1]) neighbours++;
  if (i > 0 && j < cols - 1 && neighbourhood[i-1][j+1]) neighbours++;
  if (i > 0 && j > 0 && neighbourhood[i-1][j-1]) neighbours++;
  return neighbours;
}

void clear_neighbourhood(bool** current, bool** updated, int rows, int cols) {
  for ( int i = 0 ; i < rows ; i++ ) {
    free(current[i]);
    free(updated[i]);
  }
  free(current);
  free(updated);
}

void draw(bool** neighbourhood, int rows, int cols) {
  curs_set(1);
  int y = 0 , x = 0;
  int ch;
  while (1) {
    ch = getch();
    if ( ch == KEY_UP) {
      if (y > 0) y--;
    }
    if ( ch == KEY_DOWN) {
      if (y < rows - 1) y++;
    }
    if ( ch == KEY_LEFT) {
      if (x > 0) x--;
    }
    if ( ch == KEY_RIGHT) {
      if (x < cols - 1) x++;
    }
    if ( ch == 'a' ) {
      neighbourhood[y][x] = true;
      print_cell(true);
    }
    if ( ch == 'c' ) {
      neighbourhood[y][x] = false;
      print_cell(false);
    }
    if ( ch == '\n' ) {
      break;
    }
    if ( ch == 'q' ) {
      break;
    }
    move(y,x);
    napms(10);
  }
  curs_set(0);
}
