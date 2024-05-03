#ifndef GUI_HPP
#define GUI_HPP

#include <stdio.h>
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
#define TITLE_TAB_Y1        0
#define TITLE_TAB_Y2        10
#define TITLE_TAB_X1        0

#define TAB_FILES           0
#define TAB_TILES           1
#define TAB_EDITOR          2
#define TAB_CONFIG          3

// Colors Values
#define COLOR_WHITE         7
#define COLOR_BLACK         8
#define COLOR_DARK_GRAY     9
#define COLOR_GREEN         2
#define COLOR_BLUE          4
#define COLOR_RED           1
#define COLOR_LIGTH_GRAY    0xF

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
#define KEY_C_Q1             81
#define KEY_C_Q2             113
#define KEY_C_W1             87
#define KEY_C_W2             119
#define KEY_C_R1             82
#define KEY_C_R2             114
#define KEY_C_T1             84
#define KEY_C_T2             116

//Action Keys Editor
#define KEY_PAG_DEC         60
#define KEY_PAG_INC         62
#define KEY_C_LEFT		    1		// Cursor Left
#define KEY_C_RIGHT	        4		// Cursor Right
#define KEY_C_DOWN 	        19		// Cursor Down
#define KEY_C_UP 		    23		// Cursor Up
#define KEY_C_SPACE 		32		// Cursor Up

//Action Keys File
#define KEY_C_L1		    76		
#define KEY_C_L2	        108		
#define KEY_C_S1 	        83		
#define KEY_C_S2 		    115		
#define KEY_C_N1     		79		
#define KEY_C_N2     		110		
#define KEY_C_G1     		71		
#define KEY_C_G2     		103	
#define KEY_C_A1     		65		
#define KEY_C_A2     		97	

//Editor Grid
#define GRID_X1             4
#define GRID_X2             260
#define GRID_Y1             15
#define GRID_Y2             223
#define NR_TILES_HR         16
#define NR_TILES_VE         13

//Memory address for tiles map 
#define MMAP_ADDRESS  0xD000 // initial Address of grid's memory 
#define MMAP_MAX_LEN  0x2000 // must be multiply of 20*15 tiles. 8K

class Gui {
private:

    char tabname[TAB_COUNT][10] = {
        {9, 'F', 'i', 'l', 'e', '(', 'Q', ')',' ',' '},
        {9, 'T', 'i', 'l', 'e', 's','(', 'W', ')',' '},
        {9, 'E', 'd', 'i', 't', 'o', 'r', '(', 'R', ')'},
        {9, 'C', 'o', 'n', 'f', 'i', 'g', '(', 'T', ')'},

    };

    // TAB_NUMBER x1,y1,x2,y2, Id Area/Id Action
    char mapMouse[TAB_COUNT][6] = {
        {TAB_FILES,1,0,TAB_WIDTH-2,11, 1},  //TAB FIles
        {TAB_TILES,TAB_WIDTH*1,0,TAB_WIDTH*2-2,11,2}, //TAB Tiles
        {TAB_EDITOR,TAB_WIDTH*2,0,TAB_WIDTH*3-2,11,2}, //TAB Editor
        {TAB_CONFIG,TAB_WIDTH*3,0,TAB_WIDTH*4-2,11,4}, //TAB Config

    };

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

    Graphic graphic;
    Blitter blitter;
    Map map;
    File file;
    Console console;
    Util util;
   
  
    char strText [sizeof(int)*40+1];
    char strChar[2]={1,65};
    char value_gfx [16];


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

    // Functions of Files Box
    void DrawFilesBox();
    void InputFileName();

    // Functions to control the program
    void ActionTabFile(char key);
    void ActionTabTile(char key);
    void ActionTabEditor(char key);
    void ActionTabConfig(char key);


public:

    Gui();

    uint8_t SetRowColNrItems(uint8_t row, uint8_t col);

    void DrawScreen();

    void DrawBoardText(char * str);

    void ActionMouse(int x, int y, uint8_t btn1, uint8_t btn2);
    
    void ActionKey(char key);

    void ReadGfxValue();

    uint8_t SaveMap();

    uint8_t LoadMap();

    uint8_t WhichTABVisible();
    
};



#endif //GUI_HPP