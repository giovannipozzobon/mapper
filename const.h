#include <stdint.h>

#define TAB_WIDTH 48
#define TAB_COUNT 4

#define COLOR_WHITE         7
#define COLOR_BLACK         8
#define COLOR_DARK_GRAY     9
#define COLOR_GREEN         2
#define COLOR_BLUE          4
#define COLOR_LIGTH_GRAY    0xF

// tab name
char tabname[TAB_COUNT][7] = {
	{6, 'F', 'i', 'l', 'e', ' ', ' '},
	{6, 'T', 'i', 'l', 'e', 's', ' '},
	{6, 'E', 'd', 'i', 't', 'o', 'r'},
	{6, 'C', 'o', 'n', 'f', 'i', 'g'},

};

// 
char coordinatesMouse[TAB_COUNT][4] = {
	{1,0,TAB_WIDTH-2,11},
	{TAB_WIDTH*1,0,TAB_WIDTH*2-2,11},
	{TAB_WIDTH*2,0,TAB_WIDTH*3-2,11},
	{TAB_WIDTH*3,0,TAB_WIDTH*4-2,11},

};