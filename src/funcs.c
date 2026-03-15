#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

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

void clear_neighbourhood(bool** neighbourhood, int rows) {
  for ( int i = 0 ; i < rows ; i++ ) {
    free(neighbourhood[i]);
  }
  free(neighbourhood);
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
    if ( ch == 'd' ) {
      neighbourhood[y][x] = false;
      print_cell(false);
    }
    if ( ch == '\n' ) {
      break;
    }
    if ( ch == 'q' ) {
      clear_neighbourhood(neighbourhood, rows);
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

bool **create_neighbourhood(int rows, int cols) {
  bool **neighbourhood = malloc(rows * sizeof(bool*));
  if (!neighbourhood) {
    endwin();
    fprintf(stderr, "Memory allocation failed.\n");
    exit(1);
  }
  
  for (int i = 0; i < rows; i++) {
    neighbourhood[i] = malloc(cols * sizeof(bool));
    if (!neighbourhood[i]) {
      endwin();
      fprintf(stderr, "Memory allocation failed.\n");
      exit(1);
    }
  }
  
  return neighbourhood;
}

void init_neighbourhood(bool **neighbourhood, int rows, int cols) {
  for (int i = 0 ; i < rows ; i++ ) {
    for (int j = 0 ; j < cols ; j++) {
      neighbourhood[i][j] = false;
    }
  }
}

void simulate(bool **current_neighbourhood, bool** updated_neighbourhood, int rows, int cols) {
  for (int i = 0 ; i < rows ; i++ ) {
    for (int j = 0 ; j < cols ; j++) {
      int neighbours = count_neighbours(current_neighbourhood, i, j, rows, cols);
      updated_neighbourhood[i][j] = update(neighbours, current_neighbourhood[i][j]);
    }
  }
}

void print_neighbourhood(bool **neighbourhood, int rows, int cols) {
  for (int i = 0 ; i < rows ; i++ ) {
    for (int j = 0 ; j < cols ; j++ ) {
      move(i,j);
      print_cell(neighbourhood[i][j]);
    }
  }
}
