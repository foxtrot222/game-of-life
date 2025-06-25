game_of_life: ./src/game_of_life.c
	gcc -Wall -o game_of_life ./src/game_of_life.c -lncursesw

clean:
	rm -rf game_of_life
