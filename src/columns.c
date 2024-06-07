/*************************************
 ** FUN COLUMNS  - SDL              **
 ** clone of FTA version from 1991  **
 ** JC 'Al-Khwarizmi' Bou-Samra     **
 ** Paragon Software 04/05/2024  -  **
 *************************************/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdbool.h>
#include "sprite_sheet.h"
#include "text.h"
#include "ascii.h"
#include "game.h"

enum gradient {Blue = 0, Green = 10, Red = 20, Yellow = 30, Magenta = 40, Cyan = 50, Grey = 60} colour = 0;

int backdrop (enum gradient colour);
int check_key(void);
int Ren_restart(void);		// game over/restart
int Ren_pause(void);		// pause
int Ren_game(void);		// render game
int Ren_logo (void);		// display logo
int Ren_about (void);		// display about
int Ren_info (void);		// info screen
int Ren_menu (void);		// main menu
int Ren_level (void);		// display level / current score
int Ren_next (void);		// display next block/brick/piece
int Ren_high (void);		// display high scores
int Ren_line (char line[], int char_x, int char_y, int ln, int ll, bool col ); // parameter names in function prototypes not necessary 
int initSDL (void);		// initialise SDL
int shutdownSDL (void);		// shutdown SDL
int render (void);		// render output
int init_gfx (void);		// create texture
int i, j, k, x, y, z, l;  	// index variables
int gamep = 0;
int tile_c;
int tile_pos = 112;

bool next_p = false;		// next piece flag
bool quit = false;		// quit flag
bool main_m = false;
bool pause_f = 0;

SDL_Window *window = NULL;
SDL_Renderer *sr;
SDL_Event event;
SDL_RWops* rwops_new;
SDL_Surface* image;
SDL_Texture * texture;
SDL_Rect logo_src = { 384, 0, 78, 54 };
SDL_Rect logo_dst = { 230, 136, 78, 54 };
//SDL_Rect char_src = {463, 0 , 7 , 5};
//SDL_Rect char_dst = {22, 11 , 7 , 5};
SDL_Rect main_back = {110, 0, 100, 200};
SDL_Rect main_trim = {111, 0, 98, 200};
SDL_Rect level_back = {231, 7, 76, 66};
SDL_Rect level_trim = {230, 6, 78, 68};
SDL_Rect next_back = {257, 86, 18, 37};
SDL_Rect next_trim = {256, 85, 20, 39};
SDL_Rect high_back = {13, 7, 76, 186};
SDL_Rect high_trim = {12, 6, 78, 188};
SDL_Rect tile_src = {132, 0, 12, 11};
SDL_Rect tile_dst = {112, 1, 12, 11};
SDL_Rect gameo_back = {119, 93, 82, 13};

/* window paramaters */
#define WIDTH 1280		// pixels
#define HEIGHT 800		// pixels
#define TITLE "FUN COLUMNS"	// window title

/** board background colours **/
int grad_tab[] = {

	0x0000cc, 0x0000bb, 0x0000aa, 0x000099, 0x000088, 0x000077, 0x000066, 0x000055, 0x000044, 0x000033, // blue
	0x00cc00, 0x00bb00, 0x00aa00, 0x009900, 0x008800, 0x007700, 0x006600, 0x005500, 0x004400, 0x003300, // green
	0xcc0000, 0xbb0000, 0xaa0000, 0x990000, 0x880000, 0x770000, 0x660000, 0x550000, 0x440000, 0x330000, // red
	0xcccc00, 0xbbbb00, 0xaaaa00, 0x999900, 0x888800, 0x777700, 0x666600, 0x555500, 0x444400, 0x333300, // yellow
	0xcc00cc, 0xbb00bb, 0xaa00aa, 0x990099, 0x880088, 0x770077, 0x660066, 0x550055, 0x440044, 0x330033, // magenta
	0x00cccc, 0x00bbbb, 0x00aaaa, 0x009999, 0x008888, 0x007777, 0x006666, 0x005555, 0x004444, 0x003333, // cyan
	0xcccccc, 0xbbbbbb, 0xaaaaaa, 0x999999, 0x888888, 0x777777, 0x666666, 0x555555, 0x444444, 0x333333  // grey
};

// ============= Main =============

int main (void) {

	initSDL ();
	init_gfx();

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

// ============= Backdrop =============
int backdrop (enum gradient colour) {

	k = 0;				// gradient fill
	for (j = 0; j < 10; j++) {
		SDL_SetRenderDrawColor (sr, (grad_tab[j + colour] & 0x00ff0000) >> 16, (grad_tab[j + colour] & 0x0000ff00) >> 8, grad_tab[j + colour] & 0x000000ff, 255);
		for (i = 0; i < 20; i++) {
			SDL_RenderDrawLine (sr, 0, k, 319, k);
			k = k + 1;
		}
	}

	k = 0;				// horizontal edge light
		SDL_SetRenderDrawColor (sr, 0x99, 0x99, 0x99, 255);
		for (i = 0; i < 16; i++) {
		SDL_RenderDrawLine (sr, k, 0, k, 199);
		k = k + 20;
	}

	k = 0;				// vertical edge light
//	SDL_SetRenderDrawColor (sr, 0x99, 0x99, 0x99, 255);
	for (i = 0; i < 10; i++) {
		SDL_RenderDrawLine (sr, 0, k, 319, k);
		k = k + 20;
	}

	k = 19;				// horizontal edge dark
	SDL_SetRenderDrawColor (sr, 0x0, 0x0, 0x0, 255);
	for (i = 0; i < 16; i++) {
		SDL_RenderDrawLine (sr, k, 0, k, 199);
		k = k + 20;
	}

	k = 19;				// vertical edge dark
//	SDL_SetRenderDrawColor (sr, 0x0, 0x0, 0x0, 255);
	for (i = 0; i < 10; i++) {
    		SDL_RenderDrawLine (sr, 0, k, 319, k);
	k = k + 20;
	}

	l = 0;				// corner highlight
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	for (j = 0; j < 10; j++) {
		k = 0;
		for (i = 0; i < 16; i++) {
			SDL_RenderDrawPoint(sr, k, l);
			k = k + 20;
		}
		l = l + 20;
	}

return 0;
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
// ============= Logo =============
int Ren_logo(void) {
	SDL_RenderCopy(sr, texture, &logo_src, &logo_dst);
	SDL_SetRenderDrawColor (sr, 0x0, 0x0, 0x0, 255);	// shadow
	SDL_RenderDrawLine (sr, 234, 190, 308, 190);
	SDL_RenderDrawLine (sr, 234, 191, 309, 191);
	SDL_RenderDrawLine (sr, 308, 190, 308, 140);
	SDL_RenderDrawLine (sr, 309, 191, 309, 140);
	return 0;
}

// ============= Game =============
int Ren_game(void) {
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);			// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);			// trim
	if(tile_c > 17) {
	    tile_c = 0;
	}

	for (i = 0; i < 1; i++) {
		tile_dst.x = tile_pos;
		tile_dst.y = 11 * tile_c + 1;
		SDL_RenderCopy(sr, texture, &tile_src, &tile_dst);
		tile_c++;
		}
	return 0;
}

// ============= About =============
int Ren_about(void) {
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);			// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);			// trim
	for (z = 0; z < 13; z++) {				// 13 lines of text
		Ren_line(about, aboutl[z][0], aboutl[z][1], z * 11, 11, 0);
	}
	return 0;
}

// ============= Info =============
int Ren_info(void) {
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);			// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);			// trim
	for (z = 0; z < 11; z++) {					// 11 lines of text
		Ren_line(info, infol[z][0], infol[z][1], z * 11, 11, 0);
	}

	return 0;
}

// ============= Game Over =============
int Ren_restart(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &gameo_back);			// background
	for (z = 0; z < 1; z++) {					// 1 line of text
		Ren_line(gameo, gameol[z][0], gameol[z][1], z * 9, 9, 1);
	}

	return 0;
}

// ============= Pause =============
int Ren_pause(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &gameo_back);			// background
	for (z = 0; z < 1; z++) {					// 1 line of text
		Ren_line(pause, pausel[z][0], pausel[z][1], z * 9, 9, 1);
	}

	return 0;
}

// ============= Main Menu =============
int Ren_menu(void) {
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);			// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);			// trim
	for (z = 0; z < 10; z++) {					// 10 lines of text
		Ren_line(m_menu, m_menul[z][0], m_menul[z][1], z * 11, 11, 0);
	}

	return 0;
}

// ============= Status =============
int Ren_level(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &level_back);			// background
	SDL_SetRenderDrawColor (sr, 0x00, 0x00, 0x00, 255);
	SDL_RenderDrawRect(sr, &level_trim);			// trim
	SDL_RenderDrawLine (sr, 234, 74, 308, 74);		// level shadow
	SDL_RenderDrawLine (sr, 234, 75, 309, 75);
	SDL_RenderDrawLine (sr, 308, 75, 308, 10);
	SDL_RenderDrawLine (sr, 309, 74, 309, 10);
	for (z = 0; z < 6; z++) {                                      // 6 lines of text
		Ren_line(status, statusl[z][0], statusl[z][1], z * 7, 7, 1);
	}

return 0;
}

// ============= Next Piece =============
int Ren_next(void) {
	if (next_p == 0) {
	} else {
		SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
		SDL_RenderFillRect(sr, &next_back);			// background
		SDL_SetRenderDrawColor (sr, 0x00, 0x00, 0x00, 255);
		SDL_RenderDrawRect(sr, &next_trim);			// trim
		SDL_RenderDrawLine (sr, 259, 124, 276, 124);		// next shadow
		SDL_RenderDrawLine (sr, 259, 125, 277, 125);
		SDL_RenderDrawLine (sr, 276, 124, 276, 89);
		SDL_RenderDrawLine (sr, 277, 125, 277, 89);
		}
	return 0;
}

// ============= High Scores =============
int Ren_high(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &high_back);			// background
	SDL_SetRenderDrawColor (sr, 0x00, 0x00, 0x00, 255);
	SDL_RenderDrawRect(sr, &high_trim);			// trim
	SDL_RenderDrawLine (sr, 17, 194, 90, 194);		// next shadow
	SDL_RenderDrawLine (sr, 17, 195, 91, 195);
	SDL_RenderDrawLine (sr, 90, 194, 90, 10);
	SDL_RenderDrawLine (sr, 91, 195, 91, 10);
	for (z = 0; z < 18; z++) {					// 18 lines of text
		Ren_line(high, highl[z][0], highl[z][1], z * 7, 7, 1);
	}
	return 0;
}

// ============= ASCII Line Render =============
// api: text, x, y, line num, line len, col
int Ren_line(char line[], int char_x, int char_y, int ln, int ll, bool col ) {

	int cc;			// char col
	j = 0;

	if (col) {
		cc = 2;		// white char
	} else {
		cc = 0;		// black char
	}
	for (i = 0; i < ll; i++) {
		SDL_Rect char_dst = {char_x + j, char_y, 8, 5};
		SDL_Rect char_src = {ascii[line[i + ln]][cc], ascii[line[i + ln]][cc + 1], 8, 5};
		SDL_RenderCopy(sr, texture, &char_src, &char_dst);	// render char
		j = j + 8;						// character height
	}
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

// ============= Hidden message =============
char author[] = { "copyright (c)1991 FTA, (c)2024 Jason Bou-Samra" };
const char* title = "FUN COLUMNS - SDL";
const char* descr = "clone of FTA 1991 version";
