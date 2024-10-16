#include <SDL2/SDL.h>
#include <stdbool.h>
#include "render.h"
#include "events.h"
#include "hiscore.h"
#include "sdl.h"

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
				if (event.key.keysym.sym == SDLK_1) {speed = 1.0; level_r = 0x1E; level_c = 1;}
					if (event.key.keysym.sym == SDLK_2) {speed = 1.5;  level_r = 0x19; level_c = 5;}
						if (event.key.keysym.sym == SDLK_3) {speed = 2.0;  level_r = 0x14; level_c = 10;}
							if (event.key.keysym.sym == SDLK_4) {speed = 2.5;  level_r = 0x0F; level_c = 15;}
								if (event.key.keysym.sym == SDLK_5) {speed = 3.0;  level_r = 0x0A; level_c = 20;}
									if (event.key.keysym.sym == SDLK_6) {speed = 3.5;  level_r = 0x05; level_c = 25;}
				handle_events();			// game levels
				end_game();
				Ren_menu();
			}
		}
	}
}
