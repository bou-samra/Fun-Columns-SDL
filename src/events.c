#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "backdrop.h"
#include "render.h"
#include "column.h"
#include "sdl.h"

extern int tile_pos;

bool next_p		= false;	// next piece flag
bool restart		= false;	// restart flag
bool pause_f		= false;
bool quit		= false;	// quit flag

int handle_events () {

//////////////////////////////// GAME LOOP //////////////////////////
				
	while (restart == false) {
		Ren_game (); 
		SDL_PollEvent (&event);
		switch (event.type) {
			case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_c
			&& (event.key.keysym.mod & KMOD_CTRL) != 0 ) {
				colour = colour + 10;
				if (colour >= 69) {colour = 0;}
				backdrop(colour);
				break;
			}				// gradient colour cycle
			
				if( event.key.keysym.sym == SDLK_x
				&& (event.key.keysym.mod & KMOD_CTRL) != 0 ) {
				break;
			}				// invert gradient

			 if (event.key.keysym.sym == SDLK_LEFT) {

				if (col == 0) {break;}
				grid[0][row + 1][col] = 0;
				grid[0][row + 0][col] = 0;
				grid[0][row + 2][col] = 0;
				grid[0][row - 1][col] = 0;
				col--;
				disp_column (row, col);
				break;
			}				// left arrow

 			if (event.key.keysym.sym == SDLK_RIGHT) {
 				if (col == 7) {break;}
				grid[0][row + 1][col] = 0;
				grid[0][row + 0][col] = 0;
				grid[0][row + 2][col] = 0;
				grid[0][row - 1][col] = 0;
 				col++;
 				disp_column (row, col);
 				break;
 			}				// right arrow

			if (event.key.keysym.sym == SDLK_n) {
				next_p = !next_p;
				break;
			}				// next piece (brick/block) preview

			if( event.key.keysym.sym == SDLK_r
				&& (event.key.keysym.mod & KMOD_CTRL) != 0 ) {
				restart = true;
				break;
			}				// restart

			if(event.key.keysym.sym == SDLK_r
			&& (event.key.keysym.mod & KMOD_SHIFT) != 0 ) {
				rotate_col();
				disp_column (row, col);
				break;
			}				// rotate tiles

			if (event.key.keysym.sym == SDLK_SPACE) {
				break;
			}				// drop/fall block/piece/brick

			if( event.key.keysym.sym == SDLK_s
				&& (event.key.keysym.mod & KMOD_CTRL) != 0 ) {
				break;
			}				// change tile design/pattern

			if (event.key.keysym.sym == SDLK_p) {
				if (pause_f == false){
					pause_f = 1;
				} else {
					pause_f = 0;
				}
				break;
                   	}				// pause
		}
	}	
}
