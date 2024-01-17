CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer

run: game.exe
	./game.exe

game.exe: game.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f game game.o

