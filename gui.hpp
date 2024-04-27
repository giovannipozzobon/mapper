#ifndef GUI_HPP
#define GUI_HPP

#include <stdio.h>


#define TAB_WIDTH 48
#define TAB_COUNT 4

#define COLOR_WHITE         7
#define COLOR_BLACK         8
#define COLOR_DARK_GRAY     9
#define COLOR_GREEN         2
#define COLOR_BLUE          4
#define COLOR_LIGTH_GRAY    0xF

#define TAB_FILES   1
#define TAB_TILES   2
#define TAB_EDITOR  3
#define TAB_CONFIG  4


class Gui {
private:

    char tabname[TAB_COUNT][7] = {
        {6, 'F', 'i', 'l', 'e', ' ', ' '},
        {6, 'T', 'i', 'l', 'e', 's', ' '},
        {6, 'E', 'd', 'i', 't', 'o', 'r'},
        {6, 'C', 'o', 'n', 'f', 'i', 'g'},

    };

    // TAB_NUMBER x1,y1,x2,y2, Id Area/Id Action
    char mapMouse[TAB_COUNT][6] = {
        {TAB_FILES,1,0,TAB_WIDTH-2,11, 1},  //TAB FIles
        {TAB_TILES,TAB_WIDTH*1,0,TAB_WIDTH*2-2,11,2}, //TAB Tiles
        {TAB_EDITOR,TAB_WIDTH*2,0,TAB_WIDTH*3-2,11,2}, //TAB Editor
        {TAB_CONFIG,TAB_WIDTH*3,0,TAB_WIDTH*4-2,11,4}, //TAB Config

    };

    char  strText [sizeof(int)*40+1];
    uint8_t currentTab=0;

    void DrawTabs();
    void DrawTextTabs();
    void DrawBoard();
    void DrawBoardText(char * str);
    void DrawArea(uint8_t tab);

public:

    void DrawScreen();

    void PrintOnScreen(uint8_t x, uint8_t y, char * text);

};



#endif //GUI_HPP