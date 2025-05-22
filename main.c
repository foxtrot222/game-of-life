#include <wchar.h>
#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

void print_cell(bool alive);
bool update(int neighbours, bool status);
void wait();
int count_neighbours(bool** neighbourhood , int i, int j, int rows, int cols);

int main() {
  setlocale(LC_ALL, "");
  initscr();
  nodelay(stdscr, TRUE);
  noecho();
  curs_set(1);
  keypad(stdscr, TRUE);
  clear();
  int ch;
  int y = 0 , x = 0;
  
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

  while (1) {
    ch = getch();
    if ( ch == KEY_UP) {
      if (y > 0) y--;
    }
    if ( ch == KEY_DOWN) {
      y++;
    }
    if ( ch == KEY_LEFT) {
      if (x > 0) x--;
    }
    if ( ch == KEY_RIGHT) {
      x++;
    }
    if ( ch == 'a' ) {
      current_neighbourhood[y][x] = true;
      print_cell(true);
    }
    if ( ch == '\n' ) {
      break;
    }
    if ( ch == 'q' ) {
      break;
    }
    move(y,x);
  }

  curs_set(0);
  while (1) {
    wait();
    
    for ( i = 0 ; i < rows ; i++ ) {
      for ( j = 0 ; j < cols ; j++) {
	neighbours = count_neighbours(current_neighbourhood, i, j, rows, cols);
	updated_neighbourhood[i][j] = update(neighbours, current_neighbourhood[i][j]);
      }
    }

    bool **temp = current_neighbourhood;
    current_neighbourhood = updated_neighbourhood;
    updated_neighbourhood = temp;
    
    for ( i = 0 ; i < rows ; i++ ) {
      for ( j = 0 ; j < cols ; j++ ) {
	move(i,j);
	print_cell(current_neighbourhood[i][j]);
      }
    }
    ch = getch();
    if ( ch == 'q') {
        break;
    }
   
  }

  for ( i = 0 ; i < rows ; i++ ) {
    free(current_neighbourhood[i]);
    free(updated_neighbourhood[i]);
  }
  free(current_neighbourhood);
  free(updated_neighbourhood);
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

int count_neighbours(bool** neighbour , int i, int j, int rows, int cols) {
  int neighbours = 0;
  if (i < rows - 1 && neighbour[i+1][j]) neighbours++;
  if (j < cols - 1 && neighbour[i][j+1]) neighbours++;
  if (i > 0 && neighbour[i-1][j]) neighbours++;
  if (j > 0 && neighbour[i][j-1]) neighbours++;
  if (i < rows - 1 && j < cols - 1 && neighbour[i+1][j+1]) neighbours++;
  if (i < rows - 1 && j > 0 && neighbour[i+1][j-1]) neighbours++;
  if (i > 0 && j < cols - 1 && neighbour[i-1][j+1]) neighbours++;
  if (i > 0 && j > 0 && neighbour[i-1][j-1]) neighbours++;
  return neighbours;
}
