#! /bin/make
# :vim: set noexpandtab:

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif

$(info Detected OS: $(detected_OS))
ifeq ($(detected_OS),Darwin)

# brew install libsodium
# brew install sdl2
# brew install sdl2_image

CFLAGS = -lm `sdl2-config --cflags --libs`  -lsodium -lsdl2 -lsdl2_image -I/opt/homebrew/include  -L/opt/homebrew/lib
else
CFLAGS = -lm -lSDL2_image `sdl2-config --cflags --libs` -lsodium -s
endif


columns: main.c column.c research.c render.c backdrop.c sdl.c events.c hiscore.c text.c menu.c level.c column.h research.h render.h backdrop.h sdl.h events.h hiscore.h text.h menu.h sprite_sheet.h level.h
	$(CC) main.c column.c research.c render.c backdrop.c sdl.c events.c hiscore.c text.c menu.c level.c -o columns $(CFLAGS)

clean:
	rm columns
