#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "sprite_sheet.h"
#include "events.h"

/////////////////////// SDL STRUCTURES /////////////////////////
SDL_Window *window	= NULL;
SDL_Renderer *sr;
SDL_Event event;
SDL_RWops* rwops_new;
SDL_Surface* image;
SDL_Texture * texture;

Uint32 format;
const char *format2;
int access;
int widt;
int heig;

///////////////////////// WINDOW PARMS /////////////////////////
#define WIDTH	1280		// pixels
#define HEIGHT	800		// pixels
#define TITLE	"FUN COLUMNS"	// window title

/////////////////////// INITIALIZE SDL /////////////////////////
int initSDL() {
	SDL_Init (SDL_INIT_EVERYTHING);

/* new window */
	window = SDL_CreateWindow (	TITLE,			/* title */
					SDL_WINDOWPOS_CENTERED,/* x pos */
					SDL_WINDOWPOS_CENTERED,/* w pos */
					WIDTH,			/* width */
					HEIGHT,			/* height */
					SDL_WINDOW_BORDERLESS);			/* Additional flag(s) */

if (window == NULL) {
	fprintf (stderr, "SDL window failed to initialise: %s\n",
	SDL_GetError ());
	return 1;
	}							  /* deal with error */

	sr = SDL_CreateRenderer (window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /* create renderer */
	SDL_RenderSetScale (sr, 4.0, 4.0);              // scale x2 x4 options on cli
}

/////////////////////// SHUTDOWN SDL /////////////////////////
int shutdownSDL(void) {
	SDL_DestroyWindow (window);	// free memory
	SDL_Quit ();			// shutdown entire sdl sub-systems
	return 0;
}

///////////////// INIT GFX /////////////////
int init_gfx(void) {
	rwops_new = SDL_RWFromMem(byn, sizeof(byn));
	image = IMG_LoadPNG_RW(rwops_new);
	texture = SDL_CreateTextureFromSurface(sr, image);
	SDL_FreeSurface( image );
	image = NULL;
	SDL_QueryTexture(texture, &format, &access, &widt, &heig);
	format2 = SDL_GetPixelFormatName(format);
	printf("format: %s, access: %i, width: %i, height: %i\n", format2, access, widt, heig);
	return 0;
}

///////////////// WAIT FOR KEY /////////////////
int check_key(void) {
	int kkey = 1;
	while(kkey) {
		SDL_Delay(40);
		while(SDL_PollEvent(&event)) {
 			if(event.type == SDL_KEYDOWN) {
				kkey = 0;
			}
		}
	}
}
