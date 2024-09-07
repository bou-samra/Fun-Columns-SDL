#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "backdrop.h"
#include "render.h"
#include "column.h"
#include "sdl.h"

bool next_p		= false;	// next piece flag
bool restart		= false;	// restart flag
bool pause_f		= false;	// pause flag
bool quit		= false;	// quit flag
bool gradient_d		= false;	// gradient direction flag

int handle_events(void) {

////////////////////////////// EVENT LOOP //////////////////////////

	while (restart == false) {
		SDL_PollEvent (&event);
		switch (event.type) {
			case SDL_KEYDOWN:

			// gradient colour cycle
			if(event.key.keysym.sym == SDLK_c
			&& (event.key.keysym.mod & KMOD_CTRL) != 0 ) {
				colour = colour + 10;
				if (colour >= 69) {colour = 0;}
				backdrop(colour);
				break;
			}

			// invert gradient
			if( event.key.keysym.sym == SDLK_x
			&& (event.key.keysym.mod & KMOD_CTRL) != 0 ) {
				gradient_d = !gradient_d;
				break;
			}

			// left arrow
			if (event.key.keysym.sym == SDLK_LEFT) {
				if (col == 0 | grid[0][row + 2][col - 1] != 0) {break;}
					for (int i = -1; i < 3; i++) {
						grid[0][row + i][col] = 0; // zero out old column
					}
				col--;
				disp_column(row, col);
				break;
			}

			// right arrow
 			if (event.key.keysym.sym == SDLK_RIGHT) {
 				if (col == 7 | grid[0][row + 2][col + 1] != 0) {break;}
 					for (int i = -1; i < 3; i++) {
						grid[0][row + i][col] = 0; // zero out old column
					}
 				col++;
 				disp_column(row, col);
 				break;
 			}

			// next piece (brick/block) preview
			if (event.key.keysym.sym == SDLK_n) {
				next_p = !next_p;
				break;
			}

			// restart
			if( event.key.keysym.sym == SDLK_r
				&& (event.key.keysym.mod & KMOD_CTRL) != 0 ) {
				restart = true;
				break;
			}

			// rotate tiles
			if(event.key.keysym.sym == SDLK_r
			&& (event.key.keysym.mod & KMOD_SHIFT) != 0 ) {
				rotate_col();
				disp_column(row, col);
				break;
			}

			// drop/fall block/piece/brick
			if (event.key.keysym.sym == SDLK_SPACE) {
			for (int i = -1; i < 3; i++) {
				grid[0][row + i][col] = 0;  		// zero out old column
				}
				row = 18 - (18-colcnt[col]);
				disp_column(row, col);
				break;
			}

			// change tile design/pattern
			if( event.key.keysym.sym == SDLK_s
				&& (event.key.keysym.mod & KMOD_CTRL) != 0 ) {
				tile_shp++;
				if (tile_shp > 4) {
					tile_shp = 0;
				}
				break;
			}

			// pause
			if (event.key.keysym.sym == SDLK_p) {
				pause_f = !pause_f;
				break;
			}
		}
				Ren_game();
	}
}
