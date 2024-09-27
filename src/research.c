/****************************************
 ** cluster detection research routine **
 ** jc 'al-khwarizmi' bou-samra        **
 ** paragonsoft 08/06/24               **
 ** this routine uses brute force to   **
 ** detect cluster permutations and    **
 ** thus probably not very efficient   **
 ****************************************/
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "column.h"
#include "sdl.h"

#define DEBUG 0
//////////////////// DETECT CLUSTERS //////////////////////

bool research(void) {
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
					for (int m = 0; m < 3; m++) {
						grid[1][k][i + m] = 1;
					}
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
					for (int m = 0; m < 3; m++) {
						grid[1][i + m][k] = 1;
					}
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
					for (int m = 0; m < 3; m++) {
						grid[1][i + k + m][i + m] = 1;
					}
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
					for (int m = 0; m < 3; m++) {
						grid[1][i + k + m][i + m] = 1;
					}
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
					for (int m = 0; m < 3; m++) {
					grid[1][i + m][i + k + m] = 1;
					}
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
					for (int m = 0; m < 3; m++) {
					grid[1][k - i - m][i + m] = 1;
					}
					matched = true;
				}
		}

	}
// top left corner
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
					for (int m = 0; m < 3; m++) {
					grid[1][k - i - m][i + m] = 1;
					}
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
					for (int m = 1; m < 4; m++) {
					grid[1][18 - m - i][m + i + k] = 1;
					}
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

///////////////////// ELIMINATE CLUSTERS ////////////////////////
int eliminate_c(void) {
int mask;

if (tile_shp == 1 || tile_shp == 2 || tile_shp == 3) {mask = 360;} else {mask = 372;} // round or square mask
// shrink (colour to black)
	for (int k = 0; k < 7; k++) {
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 8; j++) {
				if (grid[1][i][j] == 1) {
					tile_src.y = 11 * k;
					tile_src.x = spr_x[tile_shp][grid[0][i][j]-1];
					tile_dst.x = tiledst_x + 112 + (j * 12);
					tile_dst.y = tiledst_y + 1 + (i * 11);
					SDL_RenderCopy(sr, texture, &tile_src, &tile_dst); // draw colour tile
				}
			}
		}
		SDL_RenderPresent(sr);
	}
// stretch (black to white)
	for (int k = 5; k > -1; k--) {
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 8; j++) {
				if (grid[1][i][j] == 1) {
					tile_src.y = 11 * k;
					tile_src.x = mask;
					tile_dst.x = tiledst_x + 112 + (j * 12);
					tile_dst.y = tiledst_y + 1 + (i * 11);
					SDL_RenderCopy(sr, texture, &tile_src, &tile_dst); // draw colour tile
				}
			}
		}
		SDL_RenderPresent(sr);
	}
// shrink (white to black)
	for (int k = 0; k < 7; k++) {
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 8; j++) {
				if (grid[1][i][j] == 1) {
					tile_src.y = 11 * k;
					tile_src.x = mask;
					tile_dst.x = tiledst_x + 112 + (j * 12);
					tile_dst.y = tiledst_y + 1 + (i * 11);
					SDL_RenderCopy(sr, texture, &tile_src, &tile_dst); // draw colour tile
				}
			}
		}
		SDL_RenderPresent(sr);
	}
// replace exploded tile with empty tile (0)
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 8; x++) {
			if (grid[1][y][x] == 1) {
			grid[0][y][x] = 0;
			}
		}
	}SDL_RenderPresent(sr);
	return 0;
}

///////////////////// CASCADE  ////////////////////////
int cascade(void) {
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
	}SDL_RenderPresent(sr);
}

///////////////////// CLEAR MATCHED ////////////////////////
// clear matched 3rd dimension array (this should be easy)
int clear_mat(void) {
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 18; i++) {
			grid[1][i][j] = 0;
		}
	}
}
