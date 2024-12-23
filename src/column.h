#ifndef COLUMN_H
#define COLUMN_H

extern int tile_current[3];
extern int tile_next[3];
extern int tile_initial[3];
extern int grid[2][18][8];
extern int mask[2];
extern int spr_y[6];
extern int colcnt[8];

int new_column(void);			// select random column to drop brick into
int disp_column(int row, int col);	// update column board
int current_brick(void);			// choose current/preview random brick
int next_brick(void);			// choose current/preview random brick
int initial_brick(void);			// choose current/preview random brick
int rotate_col(void);
int display_tile(void);			// display current column in play (not implemented)
int move_horiz(void);
int move_down(void);
int count_col(void);
int reset(void);

#endif
