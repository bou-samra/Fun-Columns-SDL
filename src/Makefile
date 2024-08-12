#! /bin/make
# :vim: set noexpandtab:

CFLAGS = -lm -lSDL2_image `sdl2-config --cflags --libs` -lsodium

columns: main.c
	$(CC) main.c column.c research.c render.c backdrop.c sdl.c events.c -o columns $(CFLAGS)

clean:
	rm columns
