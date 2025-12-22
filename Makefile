# SPDX-FileCopyrightText: 2025 Tirth Kavathiya <tirthkavathiya@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later

gol: ./src/gol.c
	gcc -Wall -o gol ./src/gol.c -lncursesw

clean:
	rm -rf gol
