/*************************************
 ** FUN COLUMNS  - SDL              **
 ** clone of FTA version from 1991  **
 ** JC 'Al-Khwarizmi' Bou-Samra     **
 ** Paragon Software 04/05/2024  -  **
 *************************************/
#include "game.h"
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


// ============= display play field =============

int display_grid()
{
	tiledst_y = 1;
	for (i = 0; i < 18; i++) {
		tiledst_x = 112;
		for  (j = 0; j < 8; j++) {
			k = grid[0][i][j];
			tile_shp = 1; // tile shape
			tilesrc_y = 0;
			if (k > 0) {
				k--;
				tilesrc_x = spr_x[tile_shp][k];
				tile_src.x = tilesrc_x;
				tile_src.y = tilesrc_y;
				tile_dst.x = tiledst_x;
				tile_dst.y = tiledst_y;
				SDL_RenderCopy(sr, texture, &tile_src, &tile_dst);		// draw colour tile
			} else {
				tile_dst.x = tiledst_x;
				tile_dst.y = tiledst_y;
				SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
				SDL_RenderFillRect(sr, &tile_dst);		// draw empty tile
			}
			tiledst_x = tiledst_x + 12;		// next column
		}
		tiledst_y = tiledst_y + 11;		// next row
	}
	return 0;
}

// ============= Game =============
int Ren_game(void) {
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);			// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);			// trim
	display_grid();
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
