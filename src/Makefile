#! /bin/make
# :vim: set noexpandtab:

CFLAGS = -lm -lSDL2_image `sdl2-config --cflags --libs` -lsodium

columns: columns.c
	$(CC) -o columns columns.c $(CFLAGS)

clean:
	rm columns
