#ifndef RENDER_H
#define RENDER_H

int update (void);
int display_grid (void);	// refresh game board
int Ren_restart (void);		// game over/restart
int Ren_pause (void);		// pause
int Ren_game (void);		// render game
int Ren_logo (void);		// display logo
int Ren_about (void);		// display about
int Ren_info (void);		// info screen
int Ren_menu (void);		// main menu
int Ren_level (void);		// display level / current score
int Ren_next (void);		// display next block/brick/piece
int Ren_high (void);		// display high scores
int Ren_line (char line[], int char_x, int char_y, int ln, int ll, bool col ); // parameter names in function prototypes not necessary 

extern int row, col;
#endif
