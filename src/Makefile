#! /bin/make
# :vim: set noexpandtab:

CFLAGS = -lm -lSDL2_image `sdl2-config --cflags --libs` -lsodium -s

columns: main.c column.c research.c render.c backdrop.c sdl.c events.c hiscore.c text.c column.h research.h render.h backdrop.h sdl.h events.h hiscore.h text.h sprite_sheet.h
	$(CC) main.c column.c research.c render.c backdrop.c sdl.c events.c hiscore.c text.c -o columns $(CFLAGS)

clean:
	rm columns
