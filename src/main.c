/*************************************
 ** FUN COLUMNS  - SDL              **
 ** clone of FTA version from 1991  **
 ** JC 'Al-Khwarizmi' Bou-Samra     **
 ** Paragon Software 04/05/2024  -  **
 *************************************/
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <sodium.h>
#include <math.h>
#include <stdint.h>
#include "research.h"
#include "render.h"
#include "column.h"
#include "sdl.h"
#include "events.h"

///////////////// MAIN MENU ////////////////////////////
int menu(void) {
	quit = false;
	Ren_menu();
	while (quit == false) {
		SDL_Delay(20);
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
				if (event.key.keysym.sym == SDLK_1) {speed = 1.0;}
					if (event.key.keysym.sym == SDLK_2) {speed = 1.5;}
						if (event.key.keysym.sym == SDLK_3) {speed = 2.0;}
							if (event.key.keysym.sym == SDLK_4) {speed = 2.5;}
								if (event.key.keysym.sym == SDLK_5) {speed = 3.0;}
									if (event.key.keysym.sym == SDLK_6) {speed = 3.5;}
				handle_events();			// game levels
				reset();
				Ren_restart();
				check_key();
				restart = false;
				Ren_menu();
			}
		}
	}
}

///////////////////// MAIN ROUTINE /////////////////////////
int main(void) {

	if (sodium_init() < 0) {			// initialise sodium
		printf("error\n");			// -1 = failure
	}

	initSDL ();
	init_gfx();
	research ();
	eliminate_c ();
	menu();
	shutdownSDL ();
	return 0;
}

///////////////////////// HIDDEN MESSAGE /////////////////////////
char author[] = { "copyright (c)1991 FTA, (c)2024 Jason Bou-Samra" };
const char* title = "FUN COLUMNS - SDL";
const char* descr = "clone of FTA 1991 version";
