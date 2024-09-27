#ifndef HISCORE_H
#define HISCORE_H

extern SDL_Rect gameo_back;
extern SDL_Rect gameo_trim;	// game over trim
extern SDL_Rect entern_back;	// enter name back ground
extern SDL_Rect entern_trim;	// enter name trim
extern SDL_Rect cursor;		// Name entry cursor

int Ren_restart(void);		// restart
int Ren_gameover(void);		// game over
int Ren_name(void);		// render name entry
int end_game(void);
int Ren_cursor(void);		// render cursor

#endif
