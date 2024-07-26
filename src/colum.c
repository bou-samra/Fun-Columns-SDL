// randomly choose from remaining available columns to drop next brick into
int new_column() {
	totcol_avail = 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 18; j++) {
			if (grid[0][j][i] == 0) { colcnt[i]++;}		// count empty spaces in each column
		}
	}
	for (i = 0; i < 8; i++) {
		if (colcnt[i] > 2) {totcol_avail++;}			// count total available columns
	}
	if (totcol_avail == 0) {
		printf("game over\n");} else {				// no more columns available
			randc = randombytes_uniform(totcol_avail) + 0;	// choose random number from available columns
			int avl = -1;
			for (i = 0; randc != avl; i++) {		// translate random num from avail column to actual column
				if (colcnt[i] > 2) {avl++;}
			actual_col = i;					// might need to move this down to next brace
			}
		}
	return actual_col;						// return the random column
}


//  display brick in relevant row/column of board array
int disp_column(int row, int col) {
	for (i = 0; i < 3; i++) {
		grid[0][row + i][col] = tile_current[i];
		return 0;
	}
}

// generate random 3 tile bricks for current and preview
int new_brick () {
	for (i = 0; i < 3; i++) {
		tile_current[i] = randombytes_uniform(5) + 1;	// brick in play
		tile_next[i] = randombytes_uniform(5) + 1;	// next brick preview
	}
	return 0;
}

// rotate (cycle) tiles in brick by 1
int rotate_col (void)
{
	int temp;
	temp = tile_current[0];
	tile_current[0] = tile_current[1];
	tile_current[1] = tile_current[2];
	tile_current[2] = temp;
	return 0;
}
