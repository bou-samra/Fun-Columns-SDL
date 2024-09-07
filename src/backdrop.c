#include <SDL2/SDL.h>
#include <stdbool.h>
#include "sdl.h"
#include "events.h"

enum gradient {Blue = 0, Green = 10, Red = 20, Yellow = 30, Magenta = 40, Cyan = 50, Grey = 60} colour = 0;

////////////////// BOARD BACKDROP COLOURS //////////////////
int backdrop(int colour) {
int k, l;
int grad_tab[] = {
	0x0000cc, 0x0000bb, 0x0000aa, 0x000099, 0x000088, 0x000077, 0x000066, 0x000055, 0x000044, 0x000033, // blue
	0x00cc00, 0x00bb00, 0x00aa00, 0x009900, 0x008800, 0x007700, 0x006600, 0x005500, 0x004400, 0x003300, // green
	0xcc0000, 0xbb0000, 0xaa0000, 0x990000, 0x880000, 0x770000, 0x660000, 0x550000, 0x440000, 0x330000, // red
	0xcccc00, 0xbbbb00, 0xaaaa00, 0x999900, 0x888800, 0x777700, 0x666600, 0x555500, 0x444400, 0x333300, // yellow
	0xcc00cc, 0xbb00bb, 0xaa00aa, 0x990099, 0x880088, 0x770077, 0x660066, 0x550055, 0x440044, 0x330033, // magenta
	0x00cccc, 0x00bbbb, 0x00aaaa, 0x009999, 0x008888, 0x007777, 0x006666, 0x005555, 0x004444, 0x003333, // cyan
	0xcccccc, 0xbbbbbb, 0xaaaaaa, 0x999999, 0x888888, 0x777777, 0x666666, 0x555555, 0x444444, 0x333333  // grey
};

	k = 0;				// gradient fill
	if (gradient_d == false) {
		for (int j = 0; j < 10; j++) {
			SDL_SetRenderDrawColor(sr, (grad_tab[j + colour] & 0x00ff0000) >> 16, (grad_tab[j + colour] & 0x0000ff00) >> 8, grad_tab[j + colour] & 0x000000ff, 255);
			for (int i = 0; i < 20; i++) {
				SDL_RenderDrawLine(sr, 0, k, 319, k);
				k = k + 1;
			}
		}
	} else {			// invert gradient
		for (int j = 9; j > -1; j--) {
			SDL_SetRenderDrawColor(sr, (grad_tab[j + colour] & 0x00ff0000) >> 16, (grad_tab[j + colour] & 0x0000ff00) >> 8, grad_tab[j + colour] & 0x000000ff, 255);
			for (int i = 0; i < 20; i++) {
				SDL_RenderDrawLine(sr, 0, k, 319, k);
				k = k + 1;
			}
		}
	}

	k = 0;				// horizontal edge light
	SDL_SetRenderDrawColor(sr, 0x99, 0x99, 0x99, 255);
	for (int i = 0; i < 16; i++) {
		SDL_RenderDrawLine(sr, k, 0, k, 199);
		k = k + 20;
	}

	k = 0;				// vertical edge light
//	SDL_SetRenderDrawColor (sr, 0x99, 0x99, 0x99, 255);
	for (int i = 0; i < 10; i++) {
		SDL_RenderDrawLine(sr, 0, k, 319, k);
		k = k + 20;
	}

	k = 19;				// horizontal edge dark
	SDL_SetRenderDrawColor(sr, 0x0, 0x0, 0x0, 255);
	for (int i = 0; i < 16; i++) {
		SDL_RenderDrawLine(sr, k, 0, k, 199);
		k = k + 20;
	}

	k = 19;				// vertical edge dark
//	SDL_SetRenderDrawColor (sr, 0x0, 0x0, 0x0, 255);
	for (int i = 0; i < 10; i++) {
			SDL_RenderDrawLine(sr, 0, k, 319, k);
	k = k + 20;
	}

	l = 0;				// corner highlight
	SDL_SetRenderDrawColor(sr, 0xff, 0xff, 0xff, 255);
	for (int j = 0; j < 10; j++) {
		k = 0;
		for (int i = 0; i < 16; i++) {
			SDL_RenderDrawPoint(sr, k, l);
			k = k + 20;
		}
		l = l + 20;
	}

return 0;
}
