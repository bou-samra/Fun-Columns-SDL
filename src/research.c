/****************************************
 ** cluster detection research routine **
 ** jc 'al-khwarizmi' bou-samra        **
 ** paragonsoft 08/06/24               **
 ** this routine uses brute force to   **
 ** find cluster permutations and      **
 ** thus probably not very efficient   **
 ****************************************/
#include <stdio.h>
#include <stdbool.h>
extern int grid [2][18][8];

#define DEBUG 0
//////////////////// Detect clusters //////////////////////

bool research (void) {
	int z;
	int counter;
	bool matched = false;
// horizontal research
	for (int k = 0; k < 18; k++) {
		for (int i = 0; i < 6; i++) {
			int counter = 1;
				for (int j = 0; j < 2; j++) {
					if (grid[0][k][i + j] == grid[0][k][i + j + 1] &&  grid[0][k][i + j + 1] != 0) {
						counter = counter + 1;
					}
				}
				if (counter == 3) {
					grid[1][k][i] = 1;
					grid[1][k][i + 1] = 1;
					grid[1][k][i + 2] = 1;
					matched = true;
				}
			}
		}

// vertical research
	for (int k = 0; k < 8; k++) {
		for (int i = 0; i < 16; i++) {
			counter = 1;
				for (int j = 0; j < 2; j++) {
					if (grid[0][i + j][k] == grid[0][i + j + 1][k] && grid[0][i + j + 1][k] != 0) {
						counter = counter + 1;
					}
				}
				if (counter == 3) {
					grid[1][i][k] = 1;
					grid[1][i + 1][k] = 1;
					grid[1][i + 2][k] = 1;
					matched = true;
				}
		}
	}

// diagonal south/east  research
	for (int k = 0; k < 11; k++) {
		for (int i = 0; i < 6; i++) {
			counter = 1;
				for (int j = 0; j < 2; j++) {
					if (grid[0][i + j + k][i + j] == grid[0][i + j + k + 1][i + j + 1] && grid[0][i + j + k + 1][i + j + 1] != 0) {
						counter = counter + 1;
					}
				}
					if (counter == 3) {
					grid[1][i + k][i] = 1;
					grid[1][i + k + 1][i + 1] = 1;
					grid[1][i + k + 2][i + 2] = 1;
					matched = true;
				}

		}
	}
// bottom left corner
	z = 5;
	for (int k = 11; k < 16; k++) {
		for (int i = 0; i < z; i++) {
			counter = 1;
				for (int j = 0; j < 2; j++) {
					if (grid[0][i + j + k][i + j] == grid[0][i + j + k + 1][i + j + 1] && grid[0][i + j + k + 1][i + j + 1] != 0) {
						counter = counter + 1;
					}
				}
				if (counter == 3) {
					grid[1][i + k][i] = 1;
					grid[1][i + k + 1][i + 1] = 1;
					grid[1][i + k + 2][i + 2] = 1;
					matched = true;
				}
		}
		z = z - 1;
	}

// top right corner
	z = 5;
	for (int k = 1; k < 6; k++) {
		for (int i = 0; i < z; i++) {
			counter = 1;
				for (int j = 0; j < 2; j++) {
					if (grid[0][i + j][i + j + k] == grid[0][i + j + 1][i + j + 1 + k] && grid[0][i + j + 1][i + j + 1 + k] != 0) {
						counter = counter + 1;
					}
				}
				if (counter == 3) {
					grid[1][i][i + k] = 1;
					grid[1][i + 1][i + k + 1] = 1;
					grid[1][i + 2][i + k + 2] = 1;
					matched = true;
				}
		}
		z = z - 1;
	}

// diagonal north/east match research
	for (int k = 17; k > 6; k--) {
		for (int i = 0; i < 6; i++) {
			counter = 1;
				for (int j = 0; j < 2; j++) {
					if (grid[0][k - i - j][i + j] == grid[0][k - i - j - 1][i + j + 1] && grid[0][k - i - j - 1][i + j + 1] != 0) {
						counter = counter + 1;
					}
				}
				if (counter == 3) {
					grid[1][k - i][i] = 1;
					grid[1][k - i - 1][i + 1] = 1;
					grid[1][k - i - 2][i + 2] = 1;
					matched = true;
				}
		}

	}
// top left left corner
	z = 5;
	for (int k = 6; k > 0; k--) {
		for (int i = 0; i < z; i++) {
			counter = 1;
			for (int j = 0; j < 2; j++) {
				if (grid[0][k - i - j][i + j] == grid[0][k - i - j - 1][i + j + 1] && grid[0][k - i - j - 1][i + j + 1] != 0) {
					counter = counter + 1;
				}
			}
			if (counter == 3) {
					grid[1][k - i][i] = 1;
					grid[1][k - i - 1][i + 1] = 1;
					grid[1][k - i - 2][i + 2] = 1;
					matched = true;
			}
		}
		z = z - 1;
	}

// bottom right corner
	z = 5;
	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < z; i++) {
			counter = 1;
			for (int j = 0; j < 2; j++) {
				if (grid[0][17 - j - i][j + i + k + 1] == grid[0][16 - j - i][j + i + k + 2] && grid[0][16 - j - i][j + i + k + 2] != 0) {
					counter = counter + 1;
				}
			}
			if (counter == 3) {
					grid[1][17 - i][1 + i + k] = 1;
					grid[1][16 - i][2 + i + k] = 1;
					grid[1][15 - i][3 + i + k] = 1;
					matched = true;
			}
		}
		z = z - 1;
	}

// for test purposes
#if DEBUG
	for (int y = 0;y < 18; y++) {
		for (int x = 0; x < 8; x++) {
			if (grid[1][y][x] == 1) printf("match: %i, %i\n", y, x);
		}
	}
#endif
return matched;
}

///////////////////// Eliminate clusters ////////////////////////
int eliminate_c () {
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 8; x++) {
			if (grid[1][y][x] == 1) {
			grid[0][y][x] = 0;
			}
		}
	}
	return 0;
}

///////////////////// cascade ////////////////////////
int cascade() {
int floor, ceiling, num_tiles;

	for (int j = 0; j < 8; j++) {
	num_tiles = floor = ceiling = 0;
		for (int i = 17; i > -1; i--) {
			if (grid[1][i][j] == 1) {num_tiles++;}
		}				// find total number of tiles to drop
		for (int i = 17; i > -1; i--) {
			if (grid[1][i][j] == 1) {floor = i; break;}
			}					// find floor
			ceiling = floor - num_tiles;		// find ceiling
		for (int i = 0; i < ceiling; i++) {
			grid[0][floor - i][j] = grid[0][ceiling - i][j];
			}					// actual drop routine
	}
}

///////////////////// clear matched ////////////////////////
// clear matched 3rd dimension array (this should be easy)
int clear() {
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 18; i++) {
			grid[1][i][j] = 0;
		}
	}
}
