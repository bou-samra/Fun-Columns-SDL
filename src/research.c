/****************************************
 ** cluster detection research routine **
 ** jc 'al-khwarizmi' bou-samra        **
 ** paragonsoft 08/06/24               **
 ** this routine uses brute force to   **
 ** find cluster permutations and      **
 ** thus probably not very efficient   **
 ****************************************/
#include <stdio.h>
extern int grid [2][18][8];

#define DEBUG 0
//////////////////// Detect clusters //////////////////////

int research (void) {
	int z;
	int counter;
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
return 0;
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
