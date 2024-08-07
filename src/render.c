#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
//#include "render.h"
#include "text.h"
#include "ascii.h"

extern int spr_x[5][6];
extern int grid[2][18][8];
extern SDL_Renderer *sr;
extern SDL_Texture * texture;
extern int tile_c;
extern int tile_pos;
extern bool next_p;	// next piece flag
int tile_shp, tilesrc_x, tilesrc_y, tiledst_x, tiledst_y;

// =============== sprite sheet top left coordinates
// pink, green, purple, yellow, orange,cyan
int spr_x[5][6] = {
{0, 12, 24, 36, 48, 60},	// ball 1
{72, 84, 96, 108, 120, 132},	// square 1
{144, 156, 168, 180, 192, 204},	// square 2
{216, 228, 240, 252, 264, 276}, // square 3
{288, 300, 312, 324, 336, 348}, // ball 2
};

// =============== rectangle coords 
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
SDL_Rect high_back	= {13, 7, 76, 186};
SDL_Rect high_trim	= {12, 6, 78, 188};
SDL_Rect tile_src	= {72, 0, 12, 11};
SDL_Rect tile_dst	= {112, 1, 12, 11};
SDL_Rect gameo_back	= {119, 93, 82, 13};

// ============= ASCII Line Render =============
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

// ============= About =============
int Ren_about(void) {
	SDL_SetRenderDrawColor(sr, 0x0 , 0x0 , 0x0, 0xff);
	SDL_RenderFillRect(sr, &main_back);			// background
	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
	SDL_RenderDrawRect(sr, &main_trim);			// trim
	for (int z = 0; z < 13; z++) {				// 13 lines of text
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
	for (int z = 0; z < 11; z++) {					// 11 lines of text
		Ren_line(info, infol[z][0], infol[z][1], z * 11, 11, 0);
	}
	return 0;
}

// ============= Game Over =============
int Ren_restart(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &gameo_back);			// background
	for (int z = 0; z < 1; z++) {					// 1 line of text
		Ren_line(gameo, gameol[z][0], gameol[z][1], z * 9, 9, 1);
	}

	return 0;
}

// ============= Pause =============
int Ren_pause(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &gameo_back);			// background
	for (int z = 0; z < 1; z++) {					// 1 line of text
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
	for (int z = 0; z < 10; z++) {					// 10 lines of text
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
	for (int z = 0; z < 6; z++) {                                      // 6 lines of text
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
	for (int z = 0; z < 18; z++) {					// 18 lines of text
		Ren_line(high, highl[z][0], highl[z][1], z * 7, 7, 1);
	}
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
	for (int i = 0; i < 18; i++) {
		tiledst_x = 112;
		for  (int j = 0; j < 8; j++) {
			int k = grid[0][i][j];
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

	for (int i = 0; i < 1; i++) {
		tile_dst.x = tile_pos;
		tile_dst.y = 11 * tile_c + 1;
		SDL_RenderCopy(sr, texture, &tile_src, &tile_dst);
		tile_c++;
		}
	return 0;
}
