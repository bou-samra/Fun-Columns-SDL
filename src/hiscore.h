#ifndef HISCORE_H
#define HISCORE_H

extern SDL_Rect gameo_back;
extern SDL_Rect gameo_trim;	// game over trim
extern SDL_Rect entern_back;	// enter name back ground
extern SDL_Rect entern_trim;	// enter name trim
extern SDL_Rect cursor;		// Name entry cursor

int filewrite(void);
int fileread(void);
int insert_score(int);		// insert entry into high score list
int Ren_restart(void);		// restart
int Ren_gameover(void);		// game over
int Ren_name(void);		// render name entry
int end_game(void);
int Ren_cursor(void);		// render cursor

extern FILE *fptr_r;                                           // pointer to read handle
extern FILE *fptr_w;

extern int score;
extern char level_r;					// game level (remaining)
extern char level_c;					// game level (current)
extern int total;
extern int total_c;
extern char hscores [8][7+1];
extern char names[8][7+1];
extern char name_temp[7+1];

#endif
