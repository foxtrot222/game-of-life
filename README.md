<!--
SPDX-FileCopyrightText: 2025 Tirth Kavathiya <tirthkavathiya@gmail.com>

SPDX-License-Identifier: GPL-3.0-or-later
-->

# Conway's Game of Life in C

![Game of Life demo](assets/game_of_life.gif)

This is a terminal-based implementation of Conway's Game of Life written in C.
It uses the `ncurses` library to display the evolving grid using Unicode block characters.

## How to Play

- Compile the program by running the `make` command.
- Run the executable: `./game_of_life`
- Use the **arrow keys** to move the cursor.
- Press **`a`** to toggle cells (turn them alive).
- Press **`c`** to toggle cells (turn them dead).
- Once your pattern is ready, press **`Enter`** to start the simulation.
- Press **`q`** at any time to quit.

## Requirements

- `gcc` compiler
- `ncursesw` library (wide-character support)
