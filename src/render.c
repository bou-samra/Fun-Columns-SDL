#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "text.h"
#include "ascii.h"
#include "column.h"
#include "backdrop.h"
#include "events.h"
#include "sdl.h"

extern int spr_x[5][6];
extern int grid[2][18][8];
extern SDL_Renderer *sr;
extern SDL_Texture * texture;
extern int tile_pos;
extern bool next_p;	// next piece flag

int tile_shp = 1;
int tilesrc_x, tilesrc_y, tiledst_x, tiledst_y;
int row = 0, col = 0;
int tile_c;
int last_time, current_time, deltatime, score;

///////////////// SPRITE SHEET TOP LEFT COORDINATES /////////////////
// pink, green, purple, yellow, orange,cyan
int spr_x[5][6] = {
{0, 12, 24, 36, 48, 60},	// ball 1
{72, 84, 96, 108, 120, 132},	// square 1
{144, 156, 168, 180, 192, 204},	// square 2
{216, 228, 240, 252, 264, 276}, // square 3
{288, 300, 312, 324, 336, 348}, // ball 2
};

///////////////// RECTANGLE COORDS /////////////////
SDL_Rect logo_src	= { 384, 0, 78, 54 };
SDL_Rect logo_dst	= { 230, 136, 78, 54 };
//SDL_Rect char_src	= {463, 0 , 7 , 5};
//SDL_Rect char_dst	= {22, 11 , 7 , 5};
SDL_Rect main_back	= {110, 0, 100, 200};
SDL_Rect main_trim	= {111, 0, 98, 200};
SDL_Rect level_back	= {231, 7, 76, 66};
SDL_Rect level_trim	= {230, 6, 78, 68};
SDL_Rect next_back	= {257, 86, 18, 37};
SDL_Rect next_trim	= {256, 85, 20, 39};
SDL_Rect next_tile	= {260, 88, 12, 11};
SDL_Rect high_back	= {13, 7, 76, 186};
SDL_Rect high_trim	= {12, 6, 78, 188};
SDL_Rect tile_src	= {72, 0, 12, 11};
SDL_Rect tile_dst	= {112, 1, 12, 11};
SDL_Rect gameo_back	= {119, 93, 82, 13};

///////////////// ASCII LINE READER /////////////////
// api: text, x, y, line num, line len, col
int Ren_line(char line[], int char_x, int char_y, int ln, int ll, bool col ) {

	int cc;			// char col
	int j = 0;

	if (col) {
		cc = 2;		// white char
	} else {
		cc = 0;		// black char
	}
	for (int i = 0; i < ll; i++) {
		SDL_Rect char_dst = {char_x + j, char_y, 8, 5};
		SDL_Rect char_src = {ascii[line[i + ln]][cc], ascii[line[i + ln]][cc + 1], 8, 5};
		SDL_RenderCopy(sr, texture, &char_src, &char_dst);	// render char
		j = j + 8;						// character height
	}
	return 0;
}
///////////////// DISPLAY STATUS /////////////////
int Ren_level(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &level_back);			// background
	SDL_SetRenderDrawColor (sr, 0x00, 0x00, 0x00, 255);
	SDL_RenderDrawRect(sr, &level_trim);			// trim
	SDL_RenderDrawLine (sr, 234, 74, 308, 74);		// level shadow
	SDL_RenderDrawLine (sr, 234, 75, 309, 75);
	SDL_RenderDrawLine (sr, 308, 75, 308, 10);
	SDL_RenderDrawLine (sr, 309, 74, 309, 10);
	for (int z = 0; z < 6; z++) {                                      // 6 lines of text
		Ren_line(status, statusl[z][0], statusl[z][1], z * 7, 7, 1);
	}

return 0;
}

///////////////// DISPLAY NEXT PIECE /////////////////
int Ren_next(void) {
	if (next_p == 0) {
	} else {
		SDL_SetRenderDrawColor(sr, 0x00 , 0x00 , 0x00, 0xff);
		SDL_RenderFillRect(sr, &next_back);			// background
		SDL_RenderDrawLine (sr, 259, 124, 276, 124);		// next shadow
		SDL_RenderDrawLine (sr, 259, 125, 277, 125);
		SDL_RenderDrawLine (sr, 276, 124, 276, 89);
		SDL_RenderDrawLine (sr, 277, 125, 277, 89);
		SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderDrawRect(sr, &next_trim);			// trim
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
	SDL_RenderFillRect(sr, &high_back);			// background
	SDL_SetRenderDrawColor (sr, 0x00, 0x00, 0x00, 255);
	SDL_RenderDrawRect(sr, &high_trim);			// trim
	SDL_RenderDrawLine (sr, 17, 194, 90, 194);		// next shadow
	SDL_RenderDrawLine (sr, 17, 195, 91, 195);
	SDL_RenderDrawLine (sr, 90, 194, 90, 10);
	SDL_RenderDrawLine (sr, 91, 195, 91, 10);
	for (int z = 0; z < 18; z++) {					// 18 lines of text
		Ren_line(high, highl[z][0], highl[z][1], z * 7, 7, 1);
	}
	return 0;
}

///////////////// DISPLAY LOGO /////////////////
int Ren_logo(void) {
	SDL_RenderCopy(sr, texture, &logo_src, &logo_dst);
	SDL_SetRenderDrawColor (sr, 0x0, 0x0, 0x0, 255);		// shadow
	SDL_RenderDrawLine (sr, 234, 190, 308, 190);
	SDL_RenderDrawLine (sr, 234, 191, 309, 191);
	SDL_RenderDrawLine (sr, 308, 190, 308, 140);
	SDL_RenderDrawLine (sr, 309, 191, 309, 140);
	return 0;
}

///////////////// DISPLAY ABOUT /////////////////
int Ren_about(void) {
	backdrop(colour);
	Ren_logo();			// logo
	Ren_level();			// render current level/score
	Ren_next();			// render next brick/block/piece
	Ren_high();			// render high scores
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);			// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);			// trim
	for (int z = 0; z < 13; z++) {				// 13 lines of text
		Ren_line(about, aboutl[z][0], aboutl[z][1], z * 11, 11, 0);
	}
	SDL_RenderPresent (sr);
	return 0;
}

///////////////// DISPLAY INFO /////////////////
int Ren_info(void) {
	backdrop(colour);
	Ren_logo();			// logo
	Ren_level();			// render current level/score
	Ren_next();			// render next brick/block/piece
	Ren_high();			// render high scores
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);			// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);			// trim
	for (int z = 0; z < 11; z++) {				// 11 lines of text
		Ren_line(info, infol[z][0], infol[z][1], z * 11, 11, 0);
	}
	SDL_RenderPresent (sr);
	return 0;
}

///////////////// DISPLAY GAME OVER /////////////////
int Ren_restart(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &gameo_back);			// background
	for (int z = 0; z < 1; z++) {				// 1 line of text
		Ren_line(gameo, gameol[z][0], gameol[z][1], z * 9, 9, 1);
	}
			SDL_RenderPresent (sr);
	return 0;
}

///////////////// DISPLAY PAUSE /////////////////
int Ren_pause(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &gameo_back);			// background
	for (int z = 0; z < 1; z++) {				// 1 line of text
		Ren_line(pause, pausel[z][0], pausel[z][1], z * 9, 9, 1);
	}
		SDL_RenderPresent (sr);
	return 0;
}

///////////////// DISPLAY MAIN MENU /////////////////
int Ren_menu(void) {
	backdrop(colour);
	Ren_logo();						// logo
	Ren_level();					// render current level/score
	Ren_next();						// render next brick/block/piece
	Ren_high();						// render high scores
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);			// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);			// trim
	for (int z = 0; z < 10; z++) {				// 10 lines of text
		Ren_line(m_menu, m_menul[z][0], m_menul[z][1], z * 11, 11, 0);
	}
	SDL_RenderPresent (sr);
	return 0;
}

///////////////// DISPLAY GAME BOARD/////////////////
int display_grid() {
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
				SDL_RenderCopy(sr, texture, &tile_src, &tile_dst);	// draw colour tile
			} else {
				tile_dst.x = tiledst_x + 112 + (j * 12);
				tile_dst.y = tiledst_y + 1 + (i * 11);
				SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
				SDL_RenderFillRect(sr, &tile_dst);			// draw empty tile
			}
		}
	}
	return 0;
}

///////////////// UPDATE GAME /////////////////
int Ren_game(void) {
	if (pause_f == true) {
		Ren_pause();
		return 0;
	}
	backdrop(colour);
	Ren_logo();					// logo
	Ren_level();					// render current level/score
	Ren_next();					// render next brick/block/piece
	Ren_high();					// render high scores
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);			// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);			// trim
	display_grid();
	if(row > 15) {
		grid[0][15][col] = 0;
		grid[0][16][col] = 0;
		grid[0][17][col] = 0;
		row = 0;
	}

	for (int i = 0; i < 1; i++) {
 		current_time = SDL_GetTicks();
		deltatime = current_time - last_time;
		if (deltatime > 500) {				// deltatime > 500 - (score * 10)
			last_time = current_time;
			deltatime = 0;
			disp_column (row, col);
			row++;
			grid[0][row - 2][col] = 0;
		}
		SDL_RenderPresent (sr);
		return 0;
	}
}
