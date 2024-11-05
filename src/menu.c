#include <SDL2/SDL.h>
#include <stdbool.h>
#include "render.h"
#include "events.h"
#include "hiscore.h"
#include "sdl.h"
#include "level.h"
#include "column.h"

///////////////// MAIN MENU ////////////////////////////
int menu(void) {
		reset();
//	quit = false;
	Ren_menu();

	while (quit == false) {
		SDL_Delay(20);
		SDL_PollEvent(&event);
		switch (event.type)  {
			case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_q) {					// quit
				quit = true;
			}
			if (event.key.keysym.sym == SDLK_a) {					// about
				Ren_about();
				check_key();
				Ren_menu();
			}
			if (event.key.keysym.sym == SDLK_i) {					// info (instructions)
				Ren_info();
				check_key();
				Ren_menu();
			}
			if (event.key.keysym.sym > SDLK_0 && event.key.keysym.sym < SDLK_7) {	// game levels
				reset();
				if (event.key.keysym.sym == SDLK_1) {
					speed = levels[0][3];
					level_r = levels[0][0];
					level_c = levels[0][1];
				}
					if (event.key.keysym.sym == SDLK_2) {
						speed = levels[5][3];
						level_r = levels[5][0];
						level_c = levels[4][1];
					}
						if (event.key.keysym.sym == SDLK_3) {
							speed = levels[10][3];
							level_r = levels[10][0];
							level_c = levels[9][1];
						}
							if (event.key.keysym.sym == SDLK_4) {
								speed = levels[15][3];
								level_r = levels[15][0];
								level_c = levels[14][1];
							}
								if (event.key.keysym.sym == SDLK_5) {
									speed = levels[20][3];
									level_r = levels[20][0];
									level_c = levels[19][1];
								}
									if (event.key.keysym.sym == SDLK_6) {
										speed = levels[25][3];
										level_r = levels[25][0];
										level_c = levels[24][1];
									}
				handle_events();
				end_game();
				Ren_menu();
			}
		}
	}
}
