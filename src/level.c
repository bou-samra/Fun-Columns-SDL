#include <SDL2/SDL.h>
#include <stdbool.h>
#include "hiscore.h"
#include "render.h"
#include "backdrop.h"

//////////////// LEVEL TABLE /////////////////
// [remaining / current / points / speed / colour]

int levels [30][5] = {
	{0x1E, 0x01,  50, 1,  0},		// very easy
	{0x1D, 0x02,  50, 1,  0},
	{0x1C, 0x03,  50, 1,  0},
	{0x1B, 0x04,  50, 1,  0},
	{0x1A, 0x05,  50, 1, 10},
	{0x19, 0x06,  50, 2, 10},		// easy
	{0x18, 0x07,  60, 2, 10},
	{0x17, 0x08,  70, 2, 10},
	{0x16, 0x09,  80, 2, 10},
	{0x15, 0x0A,  90, 2, 10},
	{0x14, 0x0B,  60, 3, 20},		// medium
	{0x13, 0x0C,  70, 3, 20},
	{0x12, 0x0D,  80, 3, 20},
	{0X11, 0x0E,  90, 3, 20},
	{0x10, 0x0F, 100, 3, 30},
	{0x0F, 0x10,  70, 4, 30},		// hard
	{0x0E, 0x11,  80, 4, 30},
	{0x0D, 0x12,  90, 4, 30},
	{0x0C, 0x13, 100, 4, 40},
	{0x0B, 0x14, 110, 4, 40},
	{0x0A, 0x15,  80, 5, 40},		// very hard
	{0x09, 0x16,  90, 5, 40},
	{0x08, 0x17, 100, 5, 50},
	{0x07, 0x18, 110, 5, 50},
	{0x06, 0x19, 120, 5, 50},
	{0x05, 0x1A, 120, 6, 50},		// jedi
	{0x04, 0x1B, 120, 6, 60},
	{0x03, 0x1C, 120, 6, 60},
	{0x02, 0x1D, 120, 6, 60},
	{0x01, 0x1E, 120, 6, 60}
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
