# SPDX-FileCopyrightText: 2026 Tirth Kavathiya <tirthkavathiya@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later

CFLAGS = -Wall -Wextra -fdiagnostics-color=auto -lncursesw
DIAG = -g -O0 -fanalyzer -fsanitize=address,undefined
TARGET = gol
SOURCE = src/main.c src/funcs.c

.PHONY: clean diag

main: $(SOURCE)
	gcc $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -rf gol

diag: $(SOURCE)
	gcc $(CFLAGS) $(DIAG) -o $(TARGET) $(SOURCE)
