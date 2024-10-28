#include <SDL2/SDL.h>
#include <stdbool.h>
#include "hiscore.h"
#include "render.h"
#include "backdrop.h"

//////////////// LEVEL TABLE /////////////////
// [remaining / current / points / speed / colour]

int levels [30][5] = {
	{0x1E,  1,  50, 1,  0},		// very easy
	{0x1D,  2,  50, 1,  0},
	{0x1C,  3,  50, 1,  0},
	{0x1B,  4,  50, 1,  0},
	{0x1A,  5,  50, 1, 10},
	{0x19,  6,  50, 2, 10},		// easy
	{0x18,  7,  60, 2, 10},
	{0x17,  8,  70, 2, 10},
	{0x16,  9,  80, 2, 10},
	{0x15, 10,  90, 2, 10},
	{0x14, 11,  60, 3, 20},		// medium
	{0x13, 12,  70, 3, 20},
	{0x12, 13,  80, 3, 20},
	{0X11, 14,  90, 3, 20},
	{0x10, 15, 100, 3, 30},
	{0x0F, 16,  70, 4, 30},		// hard
	{0x0E, 17,  80, 4, 30},
	{0x0D, 18,  90, 4, 30},
	{0x0C, 19, 100, 4, 40},
	{0x0B, 20, 110, 4, 40},
	{0x0A, 21,  80, 5, 40},		// very hard
	{0x09, 22,  90, 5, 40},
	{0x08, 23, 100, 5, 50},
	{0x07, 24, 110, 5, 50},
	{0x06, 25, 120, 5, 50},
	{0x05, 26, 120, 6, 50},		// jedi
	{0x04, 27, 120, 6, 60},
	{0x03, 28, 120, 6, 60},
	{0x02, 29, 120, 6, 60},
	{0x01, 30, 120, 6, 60}
};

int level_current(void) {
	if (total_c > levels[level_c][2]) {
		level_c++;
		level_r = levels[level_c][0];
		speed = levels[level_c][3];
		total_c = 0;
		colour = levels[level_c][4];
		backdrop(colour);
	}
}
