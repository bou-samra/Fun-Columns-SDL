#ifndef COLUMN_H
#define COLUMN_H

extern int tile_current[3];
extern int tile_next[3];
int new_column ();		// select random column to drop brick into
int disp_column (int row, int col);	// update column board
int new_brick (void);		// choose current/preview random brick
int rotate_col (void);
int display_tile ();		// display current column in play (not implemented)
int move_horiz (void);
int move_down (void);

#endif
