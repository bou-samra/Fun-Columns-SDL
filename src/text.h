char about[] = {	// about screen
"FUN COLUMNS"
" BY FTA    "
"CODING:    "
"O. GOGUEL  "
"DESIGN:    "
"O. BAILLY  "
"   MAITRE  "
"VERSION 1.1"
"TOOLBOX-MAG"
" ISSUE: 04 "
" 03-FEB-91 "
" COPYRIGHT "
"FTA/TOOLBOX"
};

int aboutl [13][2] = {
{118, 35},	// fun columns
{118, 49},	// by fta
{118, 63},	// coding:
{118, 72},	// o. goguel
{118, 88},	// design:
{118, 97},	// o. bailly
{118, 104},	//   maitre
{118, 132},	// version 1.1
{118, 141},	// toolbox-mag
{118, 150},	// issue: 04
{118, 159},	// 03-deb-91
{118, 175},	// copyright
{118, 184} 	// fta/toolbox
};

char high[] = {		//  high scores
"HIGH   "
"SCORES:"
"HULK   "			// OLIVIER
"..10000"
"EARTH  "			// J-YVES
"...9000"
"BUSH   "			// BERNARD
"...8000"
"AXE    "			// ERIC
"...7000"
"PERFECT"			// HUBERT
"...6000"
"POWERS "			// J-LUC
"...5000"
"TUGBOAT"			// YVAN
"...4000"
"DINO   "			// EMILE
"......1"
};

int highl [18][2] = {
{22, 11},	// HIGH
{22, 18},	// SCORES:
{22, 34},	// HULK
{22, 42},	// ......0
{22, 54},	// EARTH
{22, 62},	// ......0
{22, 74},	// BUSH
{22, 82},	// ......0
{22, 94},	// AXE
{22, 102},	// ......0
{22, 114},	// PERFECT
{22, 122},	// ......0
{22, 134},	// POWERS
{22, 142},	// ......0
{22, 154},	// TUGBOAT
{22, 162},	// ......0
{22, 174},	// DINO
{22, 182} 	// ......0
};

char status[] = {	// current status
"SCORE: "
"      0"		// score
"LEVEL: "
"1E    1"		// levels remaining / completed (31)
"TOTAL: "
"      0"		// tiles smashed
};

int statusl [6][2] = {
{240, 11},	// score:
{240, 20},	// 0
{240, 31},	// level:
{240, 40},	// 00 1
{240, 51},	// total:
{240, 60} 	// 0
};

char m_menu[] = {	// main menu
"CHOOSE :   "
"1-VERY EASY"
"2-EASY     "
"3-MEDIUM   "
"4-HARD     "
"5-VERY HARD"
"6-JEDI     "
"A-ABOUT    "
"I-INFO     "
"Q-QUIT     "
};

int m_menul [10][2] =  {
{118, 52},	// choose
{118, 66},	// 1 - very easy
{118, 73},	// 2 - easy
{118, 80},	// 3 - medium
{118, 87},	// 4 - hard
{118, 94},	// 5 - very hard
{118, 101},	// 6 - jedi
{118, 115},	// a - about
{118, 122},	// i - info
{118, 129}	// q - quit
};

char info[] = {		// info/instruction screen
"COLUMNS    "
"RULES.     "
" <-:LEFT   "
" ->:RIGHT  "
"  R:ROTATE "
"SPC:FALL   "
" ^R:RESTART"
" ^S:NEW PAT"
"  N:NEXT   "
"  P:PAUSE  "
" HAVE FUN !"
};

int infol [11][2] =  {
{116, 50},	//  columns
{116, 57},	//  rules.
{116, 71},	//  <-:left
{116, 78},	//  ->:right
{116, 85},	//   r:rotate
{116, 92},	// spc:fall
{116, 99},	//  ^r:restart
{116, 106},	//  ^s:new pat
{116, 113},	//   n:next
{116, 120},	//   p:pause
{116, 134}	// have fun !
};

char gameo[] = {
"GAME OVER"
};

int gameol [1][2] = {
{124, 97}
};

char pause[] = {
"> PAUSE <"
};

int pausel [1][2] = {
{124, 97}
};
