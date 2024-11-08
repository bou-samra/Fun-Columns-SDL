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
#include "render.h"
#include "column.h"
#include "sdl.h"
#include "menu.h"
#include "hiscore.h"

//////////////// ABOUT ///////////////////////
void about_fc() {
	printf("Fun Columns\nOriginal IIGS version: Olivier Goguel (FTA 1990/91)\nSDL version 1.0: Jason Bou-Samra (2024)\n");
}

///////////////////// MAIN ROUTINE /////////////////////////
int main(void) {

	about_fc();
	if (sodium_init() < 0) {			// initialise sodium
		printf("error... sodium failed\n");			// -1 = failure
		return 0;
	}
	initSDL();						// init. SDL subsystem
	init_gfx();						// sprite map
	fileread();
	menu();							// main menu
	filewrite();
	shutdownSDL();
	return 0;
}

///////////////////////// HIDDEN MESSAGE /////////////////////////
char author[] = { "copyright (c)1991 FTA, (c)2024 Jason Bou-Samra" };
const char* title = "FUN COLUMNS - SDL";
const char* descr = "clone of FTA 1991 version";
