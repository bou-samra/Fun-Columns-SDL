#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "text.h"
#include "column.h"
#include "render.h"
#include "backdrop.h"
#include "events.h"
#include "research.h"
#include "hiscore.h"
#include "sdl.h"
#include "level.h"

int tile_shp = 1;
int tilesrc_x, tilesrc_y, tiledst_x, tiledst_y;
int row = -1, col = 0;
int last_time, current_time, deltatime, speed;
bool wait = true;
char str[8];

///////////////// SPRITE SHEET TOP LEFT COORDINATES /////////////////
// pink, green, purple, yellow, orange, cyan
int spr_x[5][6] = {
{0, 12, 24, 36, 48, 60},	// ball 1
{72, 84, 96, 108, 120, 132},	// square 1
{144, 156, 168, 180, 192, 204},	// square 2
{216, 228, 240, 252, 264, 276}, // square 3
{288, 300, 312, 324, 336, 348}, // ball 2
};

int spr_y[6]		= {0, 11, 22, 33, 44, 55};

///////////////// RECTANGLE COORDS /////////////////
SDL_Rect logo_src	= { 384, 0, 78, 54 };		// Logo Source
SDL_Rect logo_dst	= { 230, 136, 78, 54 };		// Logo Destination
SDL_Rect main_back	= {110, 0, 100, 200};		// Main game board Background
SDL_Rect main_trim	= {111, 0, 98, 200};		// Main game board Trim
SDL_Rect level_back	= {231, 7, 76, 66};		// Level panel Background
SDL_Rect level_trim	= {230, 6, 78, 68};		// Level panel Trim
SDL_Rect next_back	= {257, 86, 18, 37};		// Next piece Background
SDL_Rect next_trim	= {256, 85, 20, 39};		// Next piece Trim
SDL_Rect next_tile	= {260, 88, 12, 11};		// Next Tile
SDL_Rect high_back	= {13, 7, 76, 186};		// High score panel Background
SDL_Rect high_trim	= {12, 6, 78, 188};		// High score panel Trim
SDL_Rect tile_src	= {72, 0, 12, 11};		// Tile Source
SDL_Rect tile_dst	= {112, 1, 12, 11};		// Tile Destination

///////////////// DISPLAY STATUS /////////////////
int Ren_level(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &level_back);					// background
	SDL_SetRenderDrawColor(sr, 0x00, 0x00, 0x00, 255);
	SDL_RenderDrawRect(sr, &level_trim);					// trim
	SDL_RenderDrawLine(sr, 234, 74, 308, 74);				// level shadow
	SDL_RenderDrawLine(sr, 234, 75, 309, 75);
	SDL_RenderDrawLine(sr, 308, 75, 308, 10);
	SDL_RenderDrawLine(sr, 309, 74, 309, 10);

// update status panel
	its(score, str, 0x20);			// score
	for (int i = 0; i < 7; i++) {
		status[7 + i] = str[i];
	}
	hts(level_r, str);			// levels remaining
	for (int i = 0; i < 2; i++) {
		status[21 + i] = str[i];
	}
	its(level_c, str, 0x20);			// level current
	for (int i = 0; i < 2; i++) {
		status[26 + i] = str[5 + i];
	}
	its(total, str, 0x20);			// total bricks smashed
	for (int i = 0; i < 7; i++) {
		status[35 + i] = str[i];
	}

	for (int z = 0; z < 6; z++) {						// 6 lines of text
		Ren_line(status, statusl[z][0], statusl[z][1], z * 7, 7, 1);
	}

return 0;
}

///////////////// DISPLAY NEXT PIECE /////////////////
int Ren_next(void) {
	if (next_p == 0) {
	} else {
		SDL_SetRenderDrawColor(sr, 0x00 , 0x00 , 0x00, 0xff);
		SDL_RenderFillRect(sr, &next_back);				// background
		SDL_RenderDrawLine(sr, 259, 124, 276, 124);			// next shadow
		SDL_RenderDrawLine(sr, 259, 125, 277, 125);
		SDL_RenderDrawLine(sr, 276, 124, 276, 89);
		SDL_RenderDrawLine(sr, 277, 125, 277, 89);
		SDL_SetRenderDrawColor(sr, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderDrawRect(sr, &next_trim);				// trim
		for (int i = 0; i < 3; i++) {
			tile_src.x = spr_x[tile_shp][tile_next[i] - 1];		// source x position in sprite map depends on tile shape and colour
			tile_src.y = 0;						// source y position in sprite map = 0
			tile_dst.x = 260;					// tile destination x position = 260
			tile_dst.y = 88 + (i * 11);				// add 11 pixels to move to next tile destination y location
			SDL_RenderCopy(sr, texture, &tile_src, &tile_dst);
		}
	}
	return 0;
}

///////////////// DISPLAY HIGH SCORES /////////////////
int Ren_high(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &high_back);					// background
	SDL_SetRenderDrawColor(sr, 0x00, 0x00, 0x00, 255);
	SDL_RenderDrawRect(sr, &high_trim);					// trim
	SDL_RenderDrawLine(sr, 17, 194, 90, 194);				// next shadow
	SDL_RenderDrawLine(sr, 17, 195, 91, 195);
	SDL_RenderDrawLine(sr, 90, 194, 90, 10);
	SDL_RenderDrawLine(sr, 91, 195, 91, 10);

// update status panel
//	for (int i = 0; i < 7; i++) {
//		high[14 + i] = name_temp[i];
//	}
//	its(score, str);			// score
//	for (int i = 0; i < 7; i++) {
//		high[21 + i] = str[i];
//	}


// print hscores
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {
			high[21 + (i * 14) + j] = hscores[i][j];
		}
	}


// print hall of fame names
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {
			high[14 + (i * 14) + j] = names[i][j];
		}
	}


	for (int z = 0; z < 18; z++) {						// 18 lines of text
		Ren_line(high, highl[z][0], highl[z][1], z * 7, 7, 1);
	}
	return 0;
}

///////////////// DISPLAY LOGO /////////////////
int Ren_logo(void) {
	SDL_RenderCopy(sr, texture, &logo_src, &logo_dst);
	SDL_SetRenderDrawColor(sr, 0x0, 0x0, 0x0, 255);				// shadow
	SDL_RenderDrawLine(sr, 234, 190, 308, 190);
	SDL_RenderDrawLine(sr, 234, 191, 309, 191);
	SDL_RenderDrawLine(sr, 308, 190, 308, 140);
	SDL_RenderDrawLine(sr, 309, 191, 309, 140);
	return 0;
}

///////////////// DISPLAY ABOUT /////////////////
int Ren_about(void) {
	backdrop(colour);
	Ren_logo();								// logo
	Ren_level();								// render current level/score
	Ren_next();								// render next brick/block/piece
	Ren_high();								// render high scores
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);					// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);					// trim
	for (int z = 0; z < 13; z++) {						// 13 lines of text
		Ren_line(about, aboutl[z][0], aboutl[z][1], z * 11, 11, 0);
	}
	SDL_RenderPresent(sr);
	return 0;
}

///////////////// DISPLAY ABOUT /////////////////
int Ren_saving(void) {
	backdrop(colour);
	Ren_logo();								// logo
	Ren_level();								// render current level/score
	Ren_next();								// render next brick/block/piece
	Ren_high();								// render high scores
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);					// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);					// trim
	for (int z = 0; z < 2; z++) {						// 2 lines of text
		Ren_line(saving, savingl[z][0], savingl[z][1], z * 11, 11, 0);
	}
	SDL_RenderPresent(sr);
	SDL_Delay(1000);
	return 0;
}

///////////////// DISPLAY INFO /////////////////
int Ren_info(void) {
	backdrop(colour);
	Ren_logo();								// logo
	Ren_level();								// render current level/score
	Ren_next();								// render next brick/block/piece
	Ren_high();								// render high scores
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);					// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);					// trim
	for (int z = 0; z < 11; z++) {						// 11 lines of text
		Ren_line(info, infol[z][0], infol[z][1], z * 11, 11, 0);
	}
	SDL_RenderPresent(sr);
	return 0;
}

///////////////// DISPLAY PAUSE /////////////////
int Ren_pause(void) {
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);					// clear background
	SDL_SetRenderDrawColor(sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);					// trim
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &gameo_back);					// background
	for (int z = 0; z < 1; z++) {						// 1 line of text
		Ren_line(pause, pausel[z][0], pausel[z][1], z * 9, 9, 1);
	}
		SDL_RenderPresent(sr);
		check_key();
		pause_f = false;
	return 0;
}

///////////////// DISPLAY MAIN MENU /////////////////
int Ren_menu(void) {
	backdrop(colour);
	Ren_logo();								// logo
	Ren_level();								// render current level/score
	Ren_next();								// render next brick/block/piece
	Ren_high();								// render high scores
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);					// background
	SDL_SetRenderDrawColor(sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);					// trim
	for (int z = 0; z < 10; z++) {						// 10 lines of text
		Ren_line(m_menu, m_menul[z][0], m_menul[z][1], z * 11, 11, 0);
	}
	SDL_RenderPresent (sr);
	return 0;
}

///////////////// DISPLAY GAME BOARD /////////////////
int display_grid(void) {
	for (int i = 0; i < 18; i++) {
		for  (int j = 0; j < 8; j++) {
			int k = grid[0][i][j];
			tilesrc_y = 0;
			if (k > 0) {
				k--;
				tilesrc_x = spr_x[tile_shp][k];
				tile_src.x = tilesrc_x;
				tile_src.y = tilesrc_y;
				tile_dst.x = tiledst_x + 112 + (j * 12);
				tile_dst.y = tiledst_y + 1 + (i * 11);
				SDL_RenderCopy(sr, texture, &tile_src, &tile_dst); // draw colour tile
			} else {
				tile_dst.x = tiledst_x + 112 + (j * 12);
				tile_dst.y = tiledst_y + 1 + (i * 11);
				SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
				SDL_RenderFillRect(sr, &tile_dst);		// draw empty tile
			}
		}
	}
	return 0;
}

//////////////// GAME LOGIC ////////////////
int game_logic(void) {
	count_col();								// count number of empty spaces in each column
//	printf("colcnt[%i]: %i, row: %i\n", col, colcnt[col], row);
	if(row == colcnt[col]) {
		row = -1;
		while (research()) {
			eliminate_c();
			cascade();
			clear_mat();				// clear matched
//			level_current();
			SDL_Delay(500);
			display_grid();
			SDL_RenderPresent (sr);
		}
		score = score + 5;
		col = new_column();
		if (col == -1) {
			return 0;
		}

// next column preview here
		current_brick();
	}
	row++;
	disp_column (row, col);							// update column in grid
	return 0;
}

///////////////// RENDER FRAME //////////////
int Ren_frame(void) {
	level_current();
	backdrop(colour);
	Ren_logo();								// logo
	Ren_level();								// render current level/score
	Ren_next();								// render next brick/block/piece
	Ren_high();								// render high scores
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);					// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);					// trim
	display_grid();
	SDL_RenderPresent (sr);
	return 0;
}

///////////////// UPDATE GAME /////////////////
int Ren_game(void) {
	while (pause_f != true)
	{
		current_time = SDL_GetTicks();
		deltatime = current_time - last_time;
		if (deltatime > 500 / speed) {
			last_time = current_time;
			deltatime = 0;
			game_logic();
		}

		Ren_frame();
		return 0;
	}
	Ren_pause();
	return 0;
}
