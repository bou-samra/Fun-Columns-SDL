/*************************************
 ** FUN COLUMNS  - SDL              **
 ** clone of FTA version from 1991  **
 ** JC 'Al-Khwarizmi' Bou-Samra     **
 ** Paragon Software 04/05/2024  -  **
 *************************************/
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <sodium.h>
#include <math.h>
#include <stdint.h>
#include "render.h"
#include "backdrop.h"
#include "column.h"
#include "research.h"
#include "sprite_sheet.h"

// =============== window parms
#define WIDTH 1280		// pixels
#define HEIGHT 800		// pixels
#define TITLE "FUN COLUMNS"	// window title

// ============== SDL structures
SDL_Window *window	= NULL;
SDL_Renderer *sr;
SDL_Event event;
SDL_RWops* rwops_new;
SDL_Surface* image;
SDL_Texture * texture;

// ============== Global Variables
int gamep		= 0;
int tile_c;
int tile_pos		= 112;
bool next_p		= false;	// next piece flag

// ============= Initialize SDL =============
int initSDL () {
	SDL_Init (SDL_INIT_EVERYTHING);

/* new window */
	window = SDL_CreateWindow (	TITLE,			/* title */
					SDL_WINDOWPOS_CENTERED,/* x pos */
					SDL_WINDOWPOS_CENTERED,/* w pos */
					WIDTH,			/* width */
					HEIGHT,			/* height */
					SDL_WINDOW_BORDERLESS);			/* Additional flag(s) */

  /* deal with error */
if (window == NULL) {
	fprintf (stderr, "SDL window failed to initialise: %s\n",
	SDL_GetError ());
	return 1;
	}

/* create renderer */
	sr = SDL_CreateRenderer (window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetScale (sr, 4.0, 4.0);              // scale x2 x4 options on cli
}

// =============  Shutdown =============
int shutdownSDL () {
	SDL_DestroyWindow (window);	// free memory
	SDL_Quit ();			// shutdown entire sdl sub-systems
	return 0;
}

// ============= Render =============
int render () {

	backdrop(colour);	// backdrop
	//Ren_menu();
	switch (gamep) {

	case 0:
	Ren_menu();
	break;

	case 1:
	Ren_about();
	break;

	case 2:
	Ren_info();
	break;

	case 3:
	Ren_game();
	break;

	case 4:
	Ren_game();
	Ren_restart();
	break;

	case 5:
	Ren_game();
	Ren_pause();
	break;
	}

	Ren_logo();			// logo
	Ren_level();			// render current level/score
	Ren_next();			// render next brick/block/piece
	Ren_high();			// render high scores
	SDL_RenderPresent (sr);
}

// ============= init_gfx =============
int init_gfx(void) {
	rwops_new = SDL_RWFromMem(byn, sizeof(byn));
	image = IMG_LoadPNG_RW(rwops_new);
	texture = SDL_CreateTextureFromSurface(sr, image);
	SDL_FreeSurface( image );
	image = NULL;
	return 0;
}

// ============= wait for key =============
int check_key(void) {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
		return 0;
  		}
	}
}

// ============= Main =============
int main (void) {

bool quit		= false;	// quit flag
bool main_m		= false;
bool pause_f		= 0;

	if (sodium_init() < 0) {			// initialise sodium
		printf("error\n");			// -1 = failure
	}

	initSDL ();
	init_gfx();
	
	tile_current[0] = 1; tile_current[1] = 2; tile_current[2] = 3;
	disp_column(0, 3);
	
	while (quit == false) {
		SDL_Delay(50);
		while (SDL_PollEvent (&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			quit = true;
			}

		switch (event.type)  {
			case SDL_KEYDOWN:
			gamep = 0;
			if (event.key.keysym.sym == SDLK_q) {
				quit = true;
			}	// quit
			if (event.key.keysym.sym == SDLK_a) {
				printf("about\n");
				gamep = 1;
			}	// about
			if (event.key.keysym.sym == SDLK_i) {
				printf("info\n");
				gamep = 2;
			}	// info
			else if (event.key.keysym.sym > SDLK_0 && event.key.keysym.sym < SDLK_7) { // level
				main_m = false;
				gamep = 3;
				while (main_m == false) {
				//	SDL_Delay(150);
					render ();
					SDL_PollEvent (&event);

					switch (event.type) {
						case SDL_KEYDOWN:
						gamep = 3;
						if(event.key.keysym.sym == SDLK_c
						&& (event.key.keysym.mod & KMOD_CTRL) != 0 ) {
							colour = colour + 10;
							if (colour >= 69) {colour = 0;}
							backdrop(colour);
							pause_f = 0;
							break;
						}				// gradient colour cycle

 						else if (event.key.keysym.sym == SDLK_LEFT) {

 							pause_f = 0;
 							if (tile_pos == 112) {break;}
 							tile_pos = tile_pos - 12;
 							break;
 						}				// left arrow

 						else if (event.key.keysym.sym == SDLK_RIGHT) {
 							pause_f = 0;
 							if (tile_pos == 196) {break;}
 							tile_pos = tile_pos + 12;
 							break;
 						}				// right arrow

						else if (event.key.keysym.sym == SDLK_n) {
							printf("next brick preview\n");
							next_p = !next_p;
							pause_f = 0;
							break;
						}				// next piece (brick/block) preview

						else  if( event.key.keysym.sym == SDLK_r
							&& (event.key.keysym.mod & KMOD_CTRL) != 0 ) {
							printf("restart\n");
							main_m = true;
							gamep = 4;
							pause_f = 0;
							//check_key();
							break;
						}				// restart

						else if (event.key.keysym.sym == SDLK_r) {
							printf("rotate\n");
							pause_f = 0;
							break;
						}				// rotate tiles

						else if (event.key.keysym.sym == SDLK_SPACE) {
							printf("drop/fall\n");
							pause_f = 0;
							break;
						}				// drop/fall block/piece/brick

						else  if( event.key.keysym.sym == SDLK_s
							&& (event.key.keysym.mod & KMOD_CTRL) != 0 ) {
							printf("change tile pattern\n");
							pause_f = 0;
							break;
						}				// change tile design/pattern

						else if (event.key.keysym.sym == SDLK_p) {
						if (!pause_f){
							printf("pause\n");
							gamep = 5;
							pause_f = 1;}
							else {
							pause_f = 0;
							gamep = 3;}
						//	check_key();
							break;
                   				}				// pause
					}
				}
			}
		}
		}

	if (quit) {
	    break;
	}

    render ();
	}

  shutdownSDL ();
return 0;
}
// ============= Hidden message =============
char author[] = { "copyright (c)1991 FTA, (c)2024 Jason Bou-Samra" };
const char* title = "FUN COLUMNS - SDL";
const char* descr = "clone of FTA 1991 version";
