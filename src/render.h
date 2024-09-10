#ifndef RENDER_H
#define RENDER_H

int update(void);
int display_grid(void);		// refresh game board
int Ren_restart(void);		// game over/restart
int Ren_pause(void);		// pause
int Ren_game(void);		// render game
int Ren_logo(void);		// display logo
int Ren_about(void);		// display about
int Ren_info(void);		// info screen
int Ren_menu(void);		// main menu
int Ren_level(void);		// display level / current score
int Ren_next(void);		// display next block/brick/piece
int Ren_high(void);		// display high scores
int Ren_line(char line[], int char_x, int char_y, int ln, int ll, bool col ); // parameter names in function prototypes not necessary
int col_update(void);
int Ren_frame(void);

extern int tile_shp;
extern int tilesrc_x, tilesrc_y, tiledst_x, tiledst_y;
extern int row, col;
extern int tile_c;
extern int last_time, current_time, deltatime, score, speed;
extern int spr_x[5][6];
extern int mask[2];
extern int spr_y[6];

extern SDL_Rect logo_src;
extern SDL_Rect logo_dst;
//extern SDL_Rect char_src;
//extern SDL_Rect char_dst;
extern SDL_Rect main_back;
extern SDL_Rect main_trim;
extern SDL_Rect level_back;
extern SDL_Rect level_trim;
extern SDL_Rect next_back;
extern SDL_Rect next_trim;
extern SDL_Rect next_tile;
extern SDL_Rect high_back;
extern SDL_Rect high_trim;
extern SDL_Rect tile_src;
extern SDL_Rect tile_dst;
extern SDL_Rect gameo_back;

#endif
