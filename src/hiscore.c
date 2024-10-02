#include <SDL2/SDL.h>
#include <stdbool.h>
#include "text.h"
#include "render.h"
#include "sdl.h"
#include "events.h"
#include "column.h"
#include "backdrop.h"

SDL_Rect gameo_back		= {119, 93, 82, 13};	// Game Over Background
SDL_Rect gameo_trim		= {118, 92, 84, 15};	// Game Over Trim
SDL_Rect entern_back	= {115, 131, 90, 29};	// Enter Name Background
SDL_Rect entern_trim	= {114, 130, 92, 31};	// Enter Name Trim
SDL_Rect cursor			= {128, 146, 7, 5};		// Name entry cursor
char pen1				= 0xff;

int score				= 0;

///////////////// DISPLAY RESTART /////////////////
int Ren_restart(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &gameo_back);				// restart background
	for (int z = 0; z < 1; z++) {						// 1 line of text
		Ren_line(gameo, gameol[z][0], gameol[z][1], z * 9, 9, 1);
	}
	SDL_RenderPresent(sr);
	return 0;
}

/////////////////// RENDER NAME ////////////////////
int Ren_name(void){
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);	// white pen
	SDL_RenderFillRect(sr, &entern_back);					// enter name background
	SDL_RenderFillRect(sr, &gameo_back);					// game over background
	SDL_SetRenderDrawColor(sr, 0x00 , 0x00 , 0x00, 0xff);	// black pen
	SDL_RenderDrawRect(sr, &entern_trim);					// enter name trim
	SDL_RenderDrawRect(sr, &gameo_trim);					// enter name trim
	SDL_RenderDrawLine(sr, 118, 161, 207, 161);				// enter name shadow
	SDL_RenderDrawLine(sr, 118, 162, 207, 162);
	SDL_RenderDrawLine(sr, 206, 134, 206, 162);
	SDL_RenderDrawLine(sr, 207, 134, 207, 162);				// enter name shadow
	SDL_RenderDrawLine(sr, 122, 107, 203, 107);
	SDL_RenderDrawLine(sr, 122, 108, 203, 108);
	SDL_RenderDrawLine(sr, 202, 96, 202, 108);
	SDL_RenderDrawLine(sr, 203, 96, 203, 108);				// game over shadow


	for (int z = 0; z < 1; z++) {						// 1 line of text
		Ren_line(gameo, gameol[z][0], gameol[z][1], z * 9, 9, 1);
	}

	for (int z = 0; z < 2; z++) {						// 2 lines of text
		Ren_line(name, namel[z][0], namel[z][1], z * 10, 10, 1);
	}
//		SDL_RenderPresent(sr);
}

////////////////// RENDER CURSOR /////////////////////
int Ren_cursor(void) {
	current_time = SDL_GetTicks();
	deltatime = current_time - last_time;
	if (deltatime > 250) {
		last_time = current_time;
		deltatime = 0;
		SDL_SetRenderDrawColor(sr, pen1, pen1, pen1, 0xff);			// black pen
		pen1 = ~pen1;
		SDL_RenderFillRect(sr, &cursor);					// enter name cursor
		SDL_RenderPresent(sr);
	}
//	backdrop(colour);
//	Ren_logo();								// logo
//	Ren_level();								// render current level/score
//	Ren_next();								// render next brick/block/piece
//	Ren_high();								// render high scores
//	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
//	SDL_RenderDrawRect(sr, &main_trim);					// trim
//	display_grid();
	Ren_name();
	SDL_Delay(20);
	return 0;
}

///////////////// DISPLAY GAME OVER /////////////
int Ren_gameover(void) {

		while (event.key.keysym.sym != SDLK_RETURN) {
			Ren_cursor();
			SDL_PollEvent (&event);
			if (event.type == SDL_KEYDOWN) {
				if ((event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) || (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) || (event.key.keysym.sym == SDLK_SPACE) || (event.key.keysym.sym == SDLK_BACKSPACE) || (event.key.keysym.sym == SDLK_RETURN)) {
					printf("event.key.keysym.sym: %02x\n", event.key.keysym.sym);
					cursor.x = cursor.x + 8;
					if (cursor.x == 192) {
						cursor.x = 128;
					}
				}
			}
		}
		return 0;
}

////////////////// HANDLE END GAME /////////////////////////
int end_game(void) {
	if (game_end == 1) {			// restart
		Ren_restart();				// 	Ren_restart();
	} else if (game_end == 2) {		// game over
		Ren_gameover();
	}
	check_key();
	reset();
	return 0;
}
