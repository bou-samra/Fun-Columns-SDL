#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdbool.h>
#include <sodium.h>
#include <stdint.h>
#include "sprite_sheet.h"
#include "text.h"
#include "ascii.h"

#define DEBUG 1
#define MAX 216
#define SIZE 100
#define NUMS_TO_GENERATE 10

enum gradient {Blue = 0, Green = 10, Red = 20, Yellow = 30, Magenta = 40, Cyan = 50, Grey = 60} colour = 0;

// ============= funcs
int display_grid ();
int backdrop (enum gradient colour);
int check_key (void);
int Ren_restart (void);		// game over/restart
int Ren_pause (void);		// pause
int Ren_game (void);		// render game
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
int new_column ();		// select random column to drop brick into
int disp_column (int row, int col);	// update column board
int new_brick (void);		// choose current/preview random brick
int research (void);		// cluster detection

// ============== vars
int i, j, k, x, y, z, l;  	// index variables
int gamep		= 0;
int tile_c;
int tile_pos		= 112;

bool next_p		= false;	// next piece flag
bool quit		= false;	// quit flag
bool main_m		= false;
bool pause_f		= 0;
int colcnt[8]		= {0, 0, 0, 0, 0, 0, 0, 0}; // number of empty spaces in each column
int totcol_avail	= 0;		// count bits in which column
int actual_col		= 0;		// actual column in game panel
int randc		= 0;

// =====================================

SDL_Window *window = NULL;
SDL_Renderer *sr;
SDL_Event event;
SDL_RWops* rwops_new;
SDL_Surface* image;
SDL_Texture * texture;
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

uint32_t tile_1, tile_2;
int i, j, k, x, y, z;
int counter		= 0;
int col, row;
int tile_shp, tilesrc_x, tilesrc_y, tiledst_x, tiledst_y;

int display_tile();

int grid [2][18][8]= {
	{
		{0, 0, 0, 0, 0, 0, 0, 0},		// colours
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 5, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 6, 0, 0, 0, 0, 0},
		{0, 0, 3, 0, 4, 0, 0, 0},
		{0, 0, 5, 0, 3, 0, 0, 0},
		{3, 0, 1, 0, 5, 0, 0, 0},
		{5, 0, 4, 0, 0, 0, 0, 0},
		{6, 0, 3, 0, 2, 0, 0, 6},
		{3, 0, 5, 3, 2, 0, 0, 3},
		{6, 0, 4, 1, 6, 1, 4, 2},
		{4, 0, 5, 2, 4, 2, 3, 2},
		{1, 1, 2, 4, 3, 2, 5, 6},
		{5, 6, 2, 2, 4, 5, 3, 2},
		{4, 1, 4, 4, 1, 1, 4, 1},
		{6, 4, 6, 1, 3, 3, 6, 3},
		{5, 4, 6, 5, 6, 1, 1, 6},
	},
	{
		{0, 0, 0, 0, 0, 0, 0, 0},		// matches
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
	}
};

// sprite sheet top left coordinates (pink, green, purple, yellow, orange,cyan)
int spr_x[5][6] = {
{0, 12, 24, 36, 48, 60},	// ball 1
{72, 84, 96, 108, 120, 132},	// square 1
{144, 156, 168, 180, 192, 204},	// square 2
{216, 228, 240, 252, 264, 276}, // square 3
{288, 300, 312, 324, 336, 348}, // ball 2
};

int mask[2] = {360, 372};
int spr_y[6] = {0, 11, 22, 33, 44, 55};
 
/********************
 * tile colours	    *
 * empty	= 0 *
 * pink		= 1 *
 * green	= 2 *
 * purple	= 3 *
 * yellow	= 4 *
 * orange	= 5 *
 * cyan		= 6 *
 * ******************/
int tile_current[3] = {0};
int tile_next[3] = {0};
