# SPDX-FileCopyrightText: 2025 Tirth Kavathiya <tirthkavathiya@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later

game_of_life: ./src/game_of_life.c
	gcc -Wall -o game_of_life ./src/game_of_life.c -lncursesw

clean:
	rm -rf game_of_life
