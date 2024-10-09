#ifndef TEXT_H
#define TEXT_H

int Ren_line(char line[], int char_x, int char_y, int ln, int ll, bool col );
void its(int, char *);
void hts(char, char *);

extern char about[];
extern int aboutl [13][2];		// about text
extern char high[];
extern int highl [18][2];		// high score panel
extern char status[];
extern int statusl [6][2];		// level panel
extern char m_menu[];
extern int m_menul [10][2];		// menu
extern char info[];
extern int infol [11][2];		// instructions
extern char gameo[];
extern int gameol [1][2];		// game over / restart
extern char pause[];
extern int pausel [1][2];		// pause
extern char name[];
extern int namel [2][2];		// end (enter name) prompt
extern char newh[];
extern int newhl [1][2];		// end (enter name) dialog box
extern int ascii [128][4];
#endif
