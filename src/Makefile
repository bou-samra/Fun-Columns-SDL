#! /bin/make
# :vim: set noexpandtab:

CFLAGS = -lm -lSDL2_image `sdl2-config --cflags --libs` -lsodium -s

columns: main.c column.c research.c render.c backdrop.c sdl.c events.c column.h research.h render.h backdrop.c sdl.h events.h
	$(CC) main.c column.c research.c render.c backdrop.c sdl.c events.c -o columns $(CFLAGS)

clean:
	rm columns
