#include <sodium.h>
#include <stdio.h>
#include <stdbool.h>
#include "events.h"

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
int tile_current[3]	= {1, 2, 3};
int tile_next[3]	= {5, 5, 5};
int colcnt[8]		= {0, 0, 0, 0, 0, 0, 0, 0}; // number of empty spaces in each column

//////////////////////////////// GAME BOARD ARRAY //////////////////////////
int grid [2][18][8] = {
	{
		{0, 0, 0, 0, 0, 0, 0, 0},		// colours
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

///////////////////////////// COUNT COLUMNS ////////////////////////////////
int count_col(void) {
for (int i=0; i < 8; i++) {
colcnt[i] = 0;
}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 18; j++) {
			if (grid[0][j][i] == 0) { colcnt[i]++;}		// count empty spaces in each column
		}
	}
}

////////////////////////////////  NEW COLUMN //////////////////////////
// randomly choose from remaining available columns to drop next brick into
int new_column(void) {
	int avl;				// general counter
	int actual_col		= 0;		// actual absolute column in game panel
	int totcol_avail	= 0;		// keep track of available columns
	int randc;				// random column number

	//totcol_avail = 0;
	count_col();
	for (int i = 0; i < 8; i++) {
		if (colcnt[i] > 3) {totcol_avail++;}			// count total available columns
	}
	if (totcol_avail == 0) {
		printf("game over\n"); restart=true;} else {				// no more columns available
			randc = randombytes_uniform(totcol_avail) + 0;	// choose random number from available columns
			avl = -1;
			for (int i = 0; randc != avl; i++) {		// translate random num from avail column to actual column
				if (colcnt[i] > 3) {avl++;}
			actual_col = i;					// might need to move this down to next brace
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
// generate random 3 tile bricks for current and preview
	int new_brick(void) {
	for (int i = 0; i < 3; i++) {
		tile_current[i] = randombytes_uniform(6) + 1;	// brick in play
		tile_next[i] = randombytes_uniform(6) + 1;	// next brick preview
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

////////////////////////////////  MOVE VERTICALLY//////////////////////////
// move brick down one place at a time
int move_down(void) {
return 0;
}
