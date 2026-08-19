CFLAGS = -Wall -Wextra -lncursesw
DIAG = -g
TARGET = gol
SOURCE = src/main.c src/funcs.c

.PHONY: clean diag

main: $(SOURCE)
	gcc $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -rf gol

diag: $(SOURCE)
	gcc $(CFLAGS) $(DIAG) -o $(TARGET) $(SOURCE)
