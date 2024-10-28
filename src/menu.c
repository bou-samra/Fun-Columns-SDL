#include <SDL2/SDL.h>
#include <stdbool.h>
#include "render.h"
#include "events.h"
#include "hiscore.h"
#include "sdl.h"
#include "level.h"

///////////////// MAIN MENU ////////////////////////////
int menu(void) {
	quit = false;
	Ren_menu();

	while (quit == false) {
//		SDL_Delay(20);
		SDL_PollEvent(&event);
		switch (event.type)  {
			case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_q) {
				quit = true;				// quit
			}
			if (event.key.keysym.sym == SDLK_a) {
				Ren_about();				// about
				check_key();
				Ren_menu();
			}
			if (event.key.keysym.sym == SDLK_i) {
				Ren_info();				// info (instructions)
				check_key();
				Ren_menu();
			}
			if (event.key.keysym.sym > SDLK_0 && event.key.keysym.sym < SDLK_7) {
				if (event.key.keysym.sym == SDLK_1) {speed = levels[0][3]; level_r = levels[0][0]; level_c = levels[0][1];}
					if (event.key.keysym.sym == SDLK_2) {speed = levels[5][3]; level_r = levels[5][0]; level_c = levels[5][1];}
						if (event.key.keysym.sym == SDLK_3) {speed = levels[10][3]; level_r = levels[10][0]; level_c = levels[10][1];}
							if (event.key.keysym.sym == SDLK_4) {speed = levels[15][3]; level_r = levels[15][0]; level_c = levels[15][1];}
								if (event.key.keysym.sym == SDLK_5) {speed = levels[20][3]; level_r = levels[20][0]; level_c = levels[20][1];}
									if (event.key.keysym.sym == SDLK_6) {speed = levels[25][3]; level_r = levels[25][0]; level_c = levels[25][1];}
				handle_events();			// game levels
				end_game();
				Ren_menu();
			}
		}
	}
}
