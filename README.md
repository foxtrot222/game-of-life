<!--
SPDX-FileCopyrightText: 2025 Tirth Kavathiya <tirthkavathiya@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
-->

# Conway's Game of Life in Terminal

![](https://files.catbox.moe/c0yvr6.gif)

A terminal-based implementation of Conway's Game of Life written in C.

It uses the **ncurses** library to display the evolving grid using Unicode block characters.

Wikipedia has [a wonderful page](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) about Conway's Game of Life.

## Usage

```text
Usage: ./gol [-d delay] [-t] [-h]

Options:
  -d DELAY    Simulation delay time in milliseconds (default: 100)
  -t          Toggle toroidal edges (default: disabled)
  -h          Show this help message and exit

How to Play:
  Use the arrow keys to move the cursor.
  Press a to toggle cells (make them alive).
  Press d to toggle cells (make them dead).
  Once your pattern is ready, press Enter to start the simulation.
  Press q at any time to quit.
```

## Requirements

- GCC
- Make
- ncursesw
- A terminal that supports ncurses and Unicode characters
- Linux, Unix, or macOS

## Building

Clone the repository, build the project using `make`, and run the program:

```sh
cd game-of-life
make
./gol
```

## License

This project is licensed under the GNU General Public License v3.0 or later.

See the full license text in [LICENSES/GPL-3.0-or-later.txt](LICENSES/GPL-3.0-or-later.txt).
