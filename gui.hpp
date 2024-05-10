#ifndef GUI_HPP
#define GUI_HPP

#include <stdio.h>
#include <string.h>
#include "graphic.hpp"
#include "blitter.hpp"
#include "map.hpp"
#include "file.hpp"
#include "console.hpp"
#include "util.hpp"




// TABS Constant
#define TAB_WIDTH           60
#define TAB_COUNT           4
#define TAB_BOARD_X1        0
#define TAB_BOARD_X2        START_POS_X-1
#define TAB_BOARD_Y1        230
#define TAB_BOARD_Y2        240
#define TITLE_TAB_X1        0
#define TITLE_TAB_X2        START_POS_X-1
#define TITLE_TAB_Y1        0
#define TITLE_TAB_Y2        10

#define TAB_FILES           0
#define TAB_TILES           1
#define TAB_EDITOR          2
#define TAB_HELP            3

// Colors Values
#define COLOR_WHITE         7
#define COLOR_BLACK         8
#define COLOR_DARK_GRAY     9
#define COLOR_LIGTH_GRAY    0xF
#define COLOR_GREEN         2
#define COLOR_DARK_GREEN    0xA
#define COLOR_BLUE          4
#define COLOR_RED           1
#define COLOR_YELLOW        3
#define COLOR_ORANE         0xB

//Tiles Box Values
#define START_POS_X         265
#define START_POS_Y         4//17
#define NR_COLS_TILES       2
#define NR_ROWS_TILES       13
#define TILES_W_H           16
#define SPACE_TILE_CHAR     4
#define CHAR_LEN            8
#define MAX_PAGE_TILE       5

//Action Keys TAB Switch
/*
#define KEY_C_Q1             81
#define KEY_C_Q2             113
#define KEY_C_W1             87
#define KEY_C_W2             119
#define KEY_C_R1             82
#define KEY_C_R2             114
#define KEY_C_T1             84
#define KEY_C_T2             116
*/
#define KEY_C_F1             70
#define KEY_C_F2             102
#define KEY_C_T1             84
#define KEY_C_T2             116
#define KEY_C_E1             69
#define KEY_C_E2             101
#define KEY_C_H1             72
#define KEY_C_H2             104
//#define KEY_C_C1             67
//#define KEY_C_C2             99


//Action Keys Editor
#define KEY_PAG_DEC         60
#define KEY_PAG_INC         62
#define KEY_C_LEFT		    1		// Cursor Left
#define KEY_C_RIGHT	        4		// Cursor Right
#define KEY_C_DOWN 	        19		// Cursor Down
#define KEY_C_UP 		    23		// Cursor Up
#define KEY_C_SPACE 		32		// Cursor Up
#define KEY_C_R1     		82		// ReFill
#define KEY_C_R2     		114	    // ReFill
//#define KEY_C_Y1     		89		// Fill
//#define KEY_C_Y2     		121		// Fill

//Action Keys File & Config
#define KEY_C_A1		    65		
#define KEY_C_A2	        97	
#define KEY_C_L1		    76		
#define KEY_C_L2	        108		
#define KEY_C_S1 	        83		
#define KEY_C_S2 		    115		
#define KEY_C_N1     		78		
#define KEY_C_N2     		110		
#define KEY_C_G1     		71		
#define KEY_C_G2     		103	
#define KEY_C_Z1     		90		
#define KEY_C_Z2     		122	
#define LENFILENAMEMAX      30


//Editor Grid
#define GRID_X1             4
#define GRID_X2             260
#define GRID_Y1             15
#define GRID_Y2             223
#define NR_TILES_HR         16
#define NR_TILES_VE         13
#define STEP_GRID_X         8
#define STEP_GRID_Y         6

//Editor Tiles
#define NR_TILES_ROW        20
#define NR_TILES_COl        15



//Memory address for tiles map 
#define MMAP_ADDRESS  0xD000 // initial Address of grid's memory 
#define MMAP_MAX_LEN  0x2000 // must be multiply of 20*15 tiles. 8K

// info about position of mouse in screen
#define MOUSEPOSTABBOX 6
#define MOUSEPOSSCREEN 5
#define MOUSEPOSEDITOR 4
#define MOUSEPOSFILE 6

class Gui {
private:

    char tabname[TAB_COUNT][9] = {
        {8, '(','F', ')', 'i', 'l', 'e', ' ', ' '},
        {8, '(','T', ')', 'i', 'l', 'e', 's', ' '},
        {8, '(','E', ')', 'd', 'i', 't', 'o', 'r'},
        {8, '(','H', ')', 'e', 'l', 'p', ' ', ' '},

    };

    // TAB_NUMBER x1,y1,x2,y2, Id Area/Key Action
    char mapTabMouse[TAB_COUNT][MOUSEPOSTABBOX] = {
        {TAB_FILES,1,0,TAB_WIDTH-2,11, KEY_C_F1},  //TAB Files
        {TAB_TILES,TAB_WIDTH*1,0,TAB_WIDTH*2-2,11,KEY_C_T1}, //TAB Tiles
        {TAB_EDITOR,TAB_WIDTH*2,0,TAB_WIDTH*3-2,11,KEY_C_E1}, //TAB Editor
        {TAB_HELP,TAB_WIDTH*3,0,TAB_WIDTH*4-2,11,KEY_C_H1}, //TAB Help

    };

    char mapEditorMouse[MOUSEPOSEDITOR] [MOUSEPOSSCREEN]= {
        {1,0,TAB_WIDTH-2,11, KEY_PAG_DEC},
        {1,0,TAB_WIDTH-2,11, KEY_PAG_INC},
        {1,0,TAB_WIDTH-2,11, KEY_C_SPACE},
        {1,0,TAB_WIDTH-2,11, KEY_C_R1}
    };

    char mapFileMouse[MOUSEPOSFILE] [MOUSEPOSSCREEN] = {
        {1,0,TAB_WIDTH-2,11, KEY_C_G1},
        {1,0,TAB_WIDTH-2,11, KEY_C_L1},
        {1,0,TAB_WIDTH-2,11, KEY_C_S1},
        {1,0,TAB_WIDTH-2,11, KEY_C_A1},
        {1,0,TAB_WIDTH-2,11, KEY_C_N1},
        {1,0,TAB_WIDTH-2,11, KEY_C_Z1}
    };

    /*
    char mapTileMouse[] = {

    };
    */

    // ASCII Key --> Tile There both uppercase lowercase letters 16 are the lowercase chars
    char Key_Tile[NR_ROWS_TILES*2+16][2] = {
        {49,0}, {50,1}, {51,2}, {52,3}, {53,4}, {54,5}, {55,6}, {56,7},
        {57,8}, {48,9},
        // Uppercase letters
        {65,10}, {66,11}, {67,12}, {68,13}, {69,14}, {70,15},{71,16}, {72,17}, 
        {73,18}, {74,19}, {75,20}, {76,21}, {77,22}, {78,23}, {79,24}, {80,25},
        // Lowercase letters
        {97,10}, {98,11}, {99,12}, {100,13}, {101,14}, {102,15},{103,16}, {104,17}, 
        {105,18}, {106,19}, {107,20}, {108,21}, {109,22}, {110,23}, {111,24}, {112,25},


    };

    char cmdFile[61];
    char cmdEditor[61];
    char cmdTiles [61];
    char cmdHelp [61];
    

    Graphic graphic;
    Blitter blitter;
    Map map;
    File file;
    Console console;
    Util util;
   
  
    char strText [61];
    char strChar[2]={1,65};
    char value_gfx [16];
    char fileName[LENFILENAMEMAX];
    char fileNameGfx[LENFILENAMEMAX];
    char strInfo1[41];
    char strInfo2[41];  
    char strInfo3[41];
    char strInfo4[41];
    char strInfo5[61];
    char strInfo6[61];

    // Tiles Box variables
    uint8_t currentTab = 0;
    uint8_t tiles_page = 0;
    uint8_t tile_Selected = 0xff;
    uint8_t end_tiles_page = MAX_PAGE_TILE;
    int old_red_square_tiles_X1;
    int old_red_square_tiles_X2;
    int old_red_square_tiles_Y1;
    int old_red_square_tiles_Y2;

    // numbers of tiles, sprite loaded from grafics.gfx
    uint8_t nr_tiles = 0;
    uint8_t nr_sprite16 = 0;
    uint8_t nr_sprite32 = 0;


    // Editor Grid variables
    int grid_cursor_X=0; //Expressed in number of tiles
    int grid_cursor_Y=0; //Expressed in number of tiles
    int grid_cursor_X_old=0; //Expressed in number of tiles
    int grid_cursor_Y_old=0; //Expressed in number of tiles
    int offset_X=0; //Offset X for grid
    int offset_Y=0; //Offset Y for grid
    int offset_X_old=0; //Offset X for grid
    int offset_Y_old=0; //Offset Y for grid
    int offset_max_X=0; //Offset max X for grid
    int offset_max_Y=0; //Offset max Y for grid
    uint8_t offset_changed =0;

    // Page Help 
    uint8_t infoHelp = 1;
    
    // Functions to Draw screen
    void DrawTabs();
    void DrawTextTabs();
    void DrawBoard();
    void DrawArea(uint8_t tab);

    // Functions of Tiles Box
    void DrawTilesBox();
    void DrawMapBox();
    void DrawKeyTitle();
    void DrawCursorSquare();
    void checkKeyForSelTile(char key);
    void DrawTileInGrid();
    void ClearSpaceTiles();
    void LoadMapFromGrid();
    void ClearSpaceMap();




    // Functions of Files Box
    void DrawFilesBox();
    void InputFileName();
    void InputFileNameGfx();

    //Functions Config
    void ResetMap();

    // Functions to control the program
    void ActionTabFile(key_with_Modifier key_mod);
    void ActionTabTile(key_with_Modifier key_mod);
    void ActionTabEditor(key_with_Modifier key_mod);
    void ActionTabHelp(key_with_Modifier key_mod);


public:

    Gui();

    uint8_t SetRowColNrItems(uint8_t row, uint8_t col);

    void DrawScreen();

    void DrawBoardText(char * str);

    key_with_Modifier ActionMouse(int x, int y, uint8_t btn1, uint8_t btn2);
    
    void ActionKey(key_with_Modifier key_mod);

    void ReadGfxValue();

    uint8_t WhichTABVisible();

    void SetNewMap();

    void FillGrid();

    void ShowInfoTabFile();
    void ShowInfoTabHelp();

    void DrawTilesInScreen();

    void ReloadTab();
    
};



#endif //GUI_HPP