#include <SDL2/SDL.h>
#include <sodium.h>
#include <stdio.h>
#include <stdbool.h>
#include "events.h"
#include "render.h"
#include "text.h"
#include "research.h"
#include "hiscore.h"
#include "backdrop.h"

/********************
 * TILE COLOURS	    *
 * empty	= 0 *
 * pink		= 1 *
 * green	= 2 *
 * purple	= 3 *
 * yellow	= 4 *
 * orange	= 5 *
 * cyan		= 6 *
 * ******************/

int tile_current[3];
int tile_next[3];
int tile_initial[3];
int colcnt[8]		= {0, 0, 0, 0, 0, 0, 0, 0};			// number of empty spaces in each column

//////////////////////////////// GAME BOARD ARRAY //////////////////////////
// central to game

int grid [2][18][8] = {
	{
		{0, 0, 0, 0, 0, 0, 0, 0},				// colours
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
	},
	{
		{0, 0, 0, 0, 0, 0, 0, 0},				// matches
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

///////////////////////////// COUNT COLUMNS ////////////////////////////////
// count available rows in each column

int count_col(void) {
for (int i = 0; i < 8; i++) {
colcnt[i] = 0;
}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 18; j++) {
			if (grid[0][j][i] == 0) { colcnt[i]++;}		// count empty rows in each column
		}
	}
}

////////////////////////////////  NEW COLUMN //////////////////////////
// randomly choose from remaining available columns to drop next brick into

int new_column(void) {
	int avl;							// general counter
	int actual_col		= -1;					// actual absolute column in game panel
	int totcol_avail	= 0;					// keep track of available columns
	int randc;							// random column number

	//totcol_avail = 0;
	count_col();
	for (int i = 0; i < 8; i++) {
		if (colcnt[i] > 3) {totcol_avail++;}			// count total available columns
	}
	if (totcol_avail == 0) {
		game_end = 2;						// game over
		} else {						// no more columns available
			randc = randombytes_uniform(totcol_avail) + 0;	// choose random number from available columns
			avl = -1;
			for (int i = 0; randc != avl; i++) {		// translate random num from avail column to actual column
				if (colcnt[i] > 3) {
					avl++;
				}
				actual_col = i;				// might need to move this down to next brace
			}
		}
	return actual_col;						// return the random column
}

//////////////////////////////// DISPLAY COLUMN //////////////////////////
//  display brick in relevant row/column of board array

	int disp_column(int row, int col) {
	for (int i = -1; i < 3; i++) {
		grid[0][row + i][col] = tile_current[i];
	}
	return 0;
}

//////////////////////////////// NEW BRICK //////////////////////////
// generate random 3 tile bricks for initial, current and preview

	int next_brick(void) {
	for (int i = 0; i < 3; i++) {
		tile_next[i] = randombytes_uniform(6) + 1;		// next brick preview
	}
	return 0;
}

	int current_brick(void) {
	for (int i = 0; i < 3; i++) {
		tile_current[i] = tile_next[i];				// brick in play (current brick)
	}
	next_brick();
	return 0;
}

	int initial_brick(void) {
	for (int i = 0; i < 3; i++) {
		tile_current[i] = randombytes_uniform(6) + 1;		// initial brick
	}
	return 0;
}

//////////////////////////////// ROTATE COLUMN //////////////////////////
// rotate (cycle) tiles in brick by 1

	int rotate_col(void) {
	int temp = tile_current[0];
	tile_current[0] = tile_current[1];
	tile_current[1] = tile_current[2];
	tile_current[2] = temp;
	return 0;
}

//////////////////////////////// MOVE HORIZONTALLY //////////////////////////
// move brick left & right using cursor keys

int move_horiz(void) {
return 0;
}

////////////////////////////////  MOVE VERTICALLY //////////////////////////
// move brick down one place at a time

int move_down(void) {
return 0;
}

///////////////////////// RESET GAME VARS ///////////////////////
int reset(void) {
// clear grid
	for (int i = 0; i < 2; i++) {
		for (int k = 0; k < 18; k++) {
			for (int j = 0; j < 8; j++) {
			grid[i][k][j] = 0;
			}
		}
	}
// reset column count
	for (int i = 0; i < 7; i++) {
		colcnt[i] = 0;
	}

// reset row/column
 	row = -1;
 	next_brick();
	initial_brick();
 	col = new_column();

// reset status panel
//char r_matched[7]	= "      0";
//char r_score[7]		= "      0";
//char r_level[7]		= "1E    1";
//char r_high[7]		= ".......";

//	for (int i = 0; i < 7; i++) {
//		status[35 + i] = r_matched[i];
//		status[7 + i] = r_score[i];
//		status[21 + i] = r_level[i];
//	}

	total		= 0x00;				// reset total
	score		= 0x00;				// reset score
	level_r		= 0x00;				// reset level ramaining
	level_c 	= 0x01;				// reset level completed
	game_end	= 0;				// reset game end status
	pause_f		= false;
	quit		= false;
	colour		= 0;

	return 0;
}
