CC = clang
CFLAGS = -Wall -Wextra -pedantic -std=c++11
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer

run: game.exe
	./game.exe

game.exe: game.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f game game.o

