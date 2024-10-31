#include <SDL2/SDL.h>
#include <stdbool.h>
#include "text.h"
#include "render.h"
#include "sdl.h"
#include "events.h"
#include "column.h"
#include "backdrop.h"

SDL_Rect gameo_back	= {119, 93, 82, 13};	// Game Over Background
SDL_Rect gameo_trim	= {118, 92, 84, 15};	// Game Over Trim
SDL_Rect entern_back	= {115, 131, 90, 29};	// Enter Name Background
SDL_Rect entern_trim	= {114, 130, 92, 31};	// Enter Name Trim
SDL_Rect cursor		= {128, 146, 7, 5};	// Name entry cursor
SDL_Rect cursor_last	= {128, 146, 7, 5};	// last cursor position
SDL_Rect fnt		= {128, 146, 7, 5};	// Name entry cursor
char pen1		= 0xff;

int score			= 0x00;			// current score
char level_r		= 0x00;			// game level (remaining)
char level_c		= 0x01;			// game level (current)
int total		= 0x00;			// smashed tiles
int total_c		= 0x00;			// total count


int hscores1[8]		= {1000, 780, 600, 500, 400, 300, 200, 100};
char hscores[8][7+1]	= {{"......."}, {"......."}, {"......."}, {"......."}, {"......."}, {"......."}, {"......."}, {"......."}};		// high score panel - scores
char names[8][7+1]	= {{"HULK   "}, {"EARTH  "}, {"BUSH   "}, {"AXE    "}, {"PERFECT"}, {"POWERS "}, {"TUGBOAT"}, {"DINO   "}};								// high score panel - names
char name_temp[7+1]	= "       ";

///////////////// DISPLAY RESTART /////////////////
int Ren_restart(void) {
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);
	SDL_RenderFillRect(sr, &gameo_back);						// restart background
	for (int z = 0; z < 1; z++) {							// 1 line of text
		Ren_line(gameo, gameol[z][0], gameol[z][1], z * 9, 9, 1);
	}
	SDL_RenderPresent(sr);
	check_key();
	return 0;
}

/////////////// INSERT ENTRY INTO HIGH SCORE LIST ///////////////////////
int insert_score(int new) {
	int hscores_new = new;
	int counter;

	for (int i = 0; i < 8; i++) {
		if (hscores_new > hscores1[i]) {
			counter = 8 - i;						// find position in list to insert
				for (int j = 0; j < counter; j++) {
					hscores1[7 - j] = hscores1[6 - j];		// shift right from position to make space, drop off last position
					for (int k = 0; k < 8; k++) {
						names[7 - j][k] = names[6 - j][k];	// do same as above for name array
					}
				}
				hscores1[i] = hscores_new;				// insert new high score into integer aray
				for (int k = 0; k < 8; k++) {
					names[i][k] = name_temp[k];			// insert new name into name ASCII array
				}
				break;
		}
	}
	for (int j = 0; j < 8; j++){
		its(hscores1[j], str, 0x2e);							// convert high scores to ASCII code
		for (int k = 0; k < 8; k++){
			hscores[j][k] = str[k];						// store in high score ASCII array
		}
	}
	return 0;									// all done
}

/////////////////// RENDER NAME ////////////////////
int Ren_name(void){
	SDL_SetRenderDrawColor(sr, 0xff , 0xff , 0xff, 0xff);				// white pen
	SDL_RenderFillRect(sr, &entern_back);						// enter name background
	SDL_RenderFillRect(sr, &gameo_back);						// game over background
	SDL_SetRenderDrawColor(sr, 0x00 , 0x00 , 0x00, 0xff);				// black pen
	SDL_RenderDrawRect(sr, &entern_trim);						// enter name trim
	SDL_RenderDrawRect(sr, &gameo_trim);						// enter name trim
	SDL_RenderDrawLine(sr, 118, 161, 207, 161);					// enter name shadow
	SDL_RenderDrawLine(sr, 118, 162, 207, 162);
	SDL_RenderDrawLine(sr, 206, 134, 206, 162);
	SDL_RenderDrawLine(sr, 207, 134, 207, 162);					// enter name shadow
	SDL_RenderDrawLine(sr, 122, 107, 203, 107);
	SDL_RenderDrawLine(sr, 122, 108, 203, 108);
	SDL_RenderDrawLine(sr, 202, 96, 202, 108);
	SDL_RenderDrawLine(sr, 203, 96, 203, 108);					// game over shadow


	for (int z = 0; z < 1; z++) {							// 1 line of text (game over)
		Ren_line(gameo, gameol[z][0], gameol[z][1], z * 9, 9, 1);
	}

	for (int z = 0; z < 2; z++) {							// 2 lines of text (enter name)
		Ren_line(name, namel[z][0], namel[z][1], z * 10, 10, 1);
	}

	for (int z = 0; z < 1; z++) {							// 1 line of text (new high)
		Ren_line(newh, newhl[z][0], newhl[z][1], z * 7, 7, 1);
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
//	Ren_logo();									// logo
//	Ren_level();									// render current level/score
//	Ren_next();									// render next brick/block/piece
//	Ren_high();									// render high scores
//	SDL_SetRenderDrawColor (sr, 0xff, 0xff, 0xff, 255);
//	SDL_RenderDrawRect(sr, &main_trim);						// trim
//	display_grid();
	Ren_name();
	SDL_Delay(20);
	return 0;
}

///////////////// DISPLAY GAME OVER /////////////
int Ren_gameover(void) {
	int counter = 0;
	cursor.x = 128;
	for (int i = 0; i < 8; i++) {
		newh[i] = 0x20;
		name_temp[i] = 0x20;
	}
	while (event.key.keysym.sym != SDLK_RETURN) {
		Ren_cursor();
		SDL_PollEvent (&event);
		if (event.type == SDL_KEYDOWN) {
			if ((event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) || (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) || (event.key.keysym.sym == SDLK_SPACE) || (event.key.keysym.sym == SDLK_RETURN)) {
//				printf("event.key.keysym.sym: %02x\n", event.key.keysym.sym);
				name_temp[counter] = event.key.keysym.sym;		// ascii name array
				newh[(cursor.x - 128) / 8] = event.key.keysym.sym;	// fill name array
//				SDL_RenderPresent(sr);
				counter++;
				if (counter > 7){counter = 7;}
				cursor.x = cursor.x + 8;				// advance cursor
				if (cursor.x == 192) {
					cursor.x = 184;					// 192 - 8
				}
			}
			else if (event.key.keysym.sym == SDLK_BACKSPACE) {
				name_temp[counter]=0x20;				// ascii name array
				counter--;
				if (counter < 0){counter = 0;}
				cursor.x = cursor.x - 8; 				// backspace
				if (cursor.x == 120) {
					cursor.x = 128;					// 120 + 8
				}
				newh[(cursor.x - 128) / 8] = 32;
			}
		}
	}
	return 0;
}

////////////////// HANDLE END GAME /////////////////////////
int end_game(void) {
//	score = 801;

	if (game_end == 1) {								// restart
		Ren_restart();								// Ren_restart();
	} else if (game_end == 2) {							// game over
		if (score < hscores1[7]) {
			Ren_restart();							// if score less then lowest on list, no name entry
		} else {
			Ren_gameover();
			insert_score(score);						// else display name entry dialog
		}
	}
//	reset();
	return 0;
}
