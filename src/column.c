#include <sodium.h>
#include <stdio.h>

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
int tile_current[3]	= {0};
int tile_next[3]	= {0};
int mask[2]		= {360, 372};
int spr_y[6]		= {0, 11, 22, 33, 44, 55};

// =============== game board array
int grid [2][18][8] = {
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
	
// randomly choose from remaining available columns to drop next brick into
int new_column(void) {
	int colcnt[8]		= {0, 0, 0, 0, 0, 0, 0, 0}; // number of empty spaces in each column
	int avl;				// general counter
	int actual_col		= 0;		// actual absolute column in game panel
	int totcol_avail	= 0;		// keep track of available columns
	int randc;				// random column number

	//totcol_avail = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 18; j++) {
			if (grid[0][j][i] == 0) { colcnt[i]++;}		// count empty spaces in each column
		}
	}
	for (int i = 0; i < 8; i++) {
		if (colcnt[i] > 2) {totcol_avail++;}			// count total available columns
	}
	if (totcol_avail == 0) {
		printf("game over\n");} else {				// no more columns available
			randc = randombytes_uniform(totcol_avail) + 0;	// choose random number from available columns
			avl = -1;
			for (int i = 0; randc != avl; i++) {		// translate random num from avail column to actual column
				if (colcnt[i] > 2) {avl++;}
			actual_col = i;					// might need to move this down to next brace
			}
		}
	return actual_col;						// return the random column
}

//  display brick in relevant row/column of board array
	int disp_column(int row, int col) {
	for (int i = 0; i < 3; i++) {
		grid[0][row + i][col] = tile_current[i];
	}
	return 0;
}

// generate random 3 tile bricks for current and preview
	int new_brick (void) {
	for (int i = 0; i < 3; i++) {
		tile_current[i] = randombytes_uniform(5) + 1;	// brick in play
		tile_next[i] = randombytes_uniform(5) + 1;	// next brick preview
	}
	return 0;
}

// rotate (cycle) tiles in brick by 1
int rotate_col (void)
{
	int temp = tile_current[0];
	tile_current[0] = tile_current[1];
	tile_current[1] = tile_current[2];
	tile_current[2] = temp;
	return 0;
}

// move brick left & right using cursor keys
int move_horiz (void)
{
return 0;
}

// move brick down one place at a time
int move_down (void)
{
return 0;
}
