#! /bin/make
# :vim: set noexpandtab:

CFLAGS = -lm -lSDL2_image `sdl2-config --cflags --libs` -lsodium

columns: main.c
	$(CC) -o columns main.c $(CFLAGS)

clean:
	rm columns
