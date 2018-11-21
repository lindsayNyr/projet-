SRC=main.c
BIN=main

$(BIN): $(SRC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs ` -lSDL_ttf -lm -o $(BIN)

clean:
	rm -f $(BIN)

