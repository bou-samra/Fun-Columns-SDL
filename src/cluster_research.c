/****************************************
 ** cluster detection research routine **
 ** jc 'al-khwarizmi' bou-samra        **
 ** paragonsoft 08/06/24               **
 ** this routine uses brute force to   **
 ** find cluster permutations and      **
 ** thus probably not very efficient   **
 ****************************************/

/********************
 * tile combos	    *
 * empty	= 0 *
 * green	= 1 *
 * purple	= 2 *
 * yellow	= 3 *
 * orange	= 4 *
 * cyan		= 5 *
 * pink		= 6 *
 * ******************/
#include <stdio.h>

int i, j, k, x, y, z, l;
int counter = 0;
int matches [100][7] = {};
int grid [18][8] = {
{0, 1, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 4, 5, 6, 7, 8},
{0, 1, 1, 1, 5, 6, 7, 8},
{0, 2, 1, 1, 5, 6, 7, 8},
{0, 5, 5, 1, 1, 5, 5, 5},
{0, 2, 1, 4, 1, 1, 7, 8},
{1, 1, 3, 4, 5, 1, 1, 8},
{1, 2, 3, 4, 5, 6, 1, 1},
{1, 1, 5, 4, 5, 6, 7, 1},
{1, 1, 1, 5, 5, 5, 7, 8},
{1, 1, 1, 1, 5, 5, 7, 1},
{1, 1, 1, 1, 1, 5, 1, 8},
{5, 5, 1, 1, 1, 1, 5, 5},
{1, 2, 3, 1, 1, 1, 1, 8},
{1, 2, 3, 1, 1, 1, 1, 1},
{1, 2, 1, 4, 5, 1, 1, 1},
{1, 1, 3, 4, 5, 6, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1},
};

int main (void) {

// horizontal match research
	for (k = 0; k < 18; k++) {
		for (i = 0; i < 6; i++) {
			int counter = 1;
				for (j = 0; j < 2; j++) {
					if (grid[k][i + j] == grid[k][i + j + 1] &&  grid[k][i + j + 1] != 0) {
						counter = counter + 1;
					}
				}
				if (counter == 3) {
					printf("h. match\n"/*add to cluster list*/);
				} else {
					printf("no h. match\n");
				}
			}
		}

// vertical match research

	for (k = 0; k < 8; k++) {
		for (i = 0; i < 16; i++) {
			counter = 1;
				for (j = 0; j < 2; j++) {
					if (grid[i + j][k] == grid[i + j + 1][k] && grid[i + j + 1][k] != 0) {
						counter = counter + 1;
					}
				}
				if (counter == 3) {
					printf("v. match\n"/*add to cluster list*/);
				} else {
					printf("no v. match\n");
				}
			}
		}

// diagonal south/east match research

	for (k = 0; k < 11; k++) {
		for (i = 0; i < 6; i++) {
			counter = 1;
				for (j = 0; j < 2; j++) {
					if (grid[i + j+k][i + j] == grid[i + j + 1+k][i + j + 1] && grid[i + j + 1+k][i + j + 1] != 0) {
						counter = counter + 1;
					}
				}
					if (counter == 3) {
						printf("dse. match\n"/*add to cluster list*/);
				} else {
					printf("no dse. match\n");
				}

	}

	}
// -- bottom left corner
	z = 5;
	for (k = 11; k < 16; k++) {
	for (i = 0; i < z; i++) {
		counter = 1;
						for (j = 0; j < 2; j++) {
					if (grid[i + j+k][i + j] == grid[i + j + 1+k][i + j + 1] && grid[i + j + 1+k][i + j + 1] != 0) {
						counter = counter + 1;
					}
				}
									if (counter == 3) {
						printf("dse. match\n"/*add to cluster list*/);
				} else {
					printf("no dse. match\n");
				}
	}
	z = z - 1;
}

// -- top right corner
	z = 5;
	for (k = 1; k < 6; k++) {
	for (i = 0; i < z; i++) {
		counter = 1;
						for (j = 0; j < 2; j++) {
					if (grid[i + j][i + j + k] == grid[i + j + 1][i + j + 1 + k] && grid[i + j + 1][i + j + 1 + k] != 0) {
						counter = counter + 1;
					}
				}
									if (counter == 3) {
						printf("dse. match\n"/*add to cluster list*/);
				} else {
					printf("no dse. match\n");
				}
	}
	z = z - 1;
}

// diagonal north/east match research

	for (k = 17; k > 6; k--) {
		for (i = 0; i < 6; i++) {
			counter = 1;
				for (j = 0; j < 2; j++) {
					if (grid[k - i - j][i + j] == grid[k - i - j - 1][i + j + 1] && grid[k - i - j - 1][i + j + 1] != 0) {
						counter = counter + 1;
					}
				}
					if (counter == 3) {
						printf("dne. match\n"/*add to cluster list*/);
				} else {
					printf("no dne. match\n");
				}

	}

	}
// -- top left left corner
	z = 5;
	for (k = 6; k > 0; k--) {
	for (i = 0; i < z; i++) {
		counter = 1;
						for (j = 0; j < 2; j++) {
					if (grid[k - i - j][i + j] == grid[k - i - j - 1][i + j + 1] && grid[k - i - j - 1][i + j + 1] != 0) {
						counter = counter + 1;
					}
				}
									if (counter == 3) {
						printf("dne. match\n"/*add to cluster list*/);
				} else {
					printf("no dne. match\n");
				}
	}
	z = z - 1;
}

// -- bottom right corner
	z = 5;
	k = 0;
	l = 0;
	for (j = 17; j > 11; j--) {
	for (i = 0; i < z; i++) {
		counter = 1;
						for (l = 0; l < 2; l++) {
					if (grid[17 - i - l][i + k + 1 + l] == grid[17 - i - 1 - l][i + k + 2 + l] && grid[17 - i -1 - l][i + k + 2 + l] != 0) {
						counter = counter + 1;
					}
				}
									if (counter == 3) {
						printf("dne. match\n"/*add to cluster list*/);
				} else {
					printf("no dne. match\n");
				}
	}
	z = z - 1;
	k++;
}

}
