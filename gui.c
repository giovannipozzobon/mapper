#include "gui.h"
#include "const.h"

char  strText [sizeof(int)*40+1];


void  DrawTabs(){
    uint8_t t;

    SetSolidFlag(1);
    SetColor(COLOR_DARK_GRAY);

    for (t = 0; t < TAB_COUNT; t++)
    {
        DrawRectangle(t*TAB_WIDTH,0,t*TAB_WIDTH+TAB_WIDTH-2,10);
    }
    
};

void  DrawTextTabs(){
    uint8_t t;
    char * tmpstr;

    SetSolidFlag(0);
    
  
    for (t = 0; t < TAB_COUNT; t++)
    {
        tmpstr = tabname[t];
        SetColor(COLOR_BLACK);
        Gfx_DrawString(t*TAB_WIDTH+3,2,tmpstr);
        SetColor(COLOR_WHITE);
        Gfx_DrawString(t*TAB_WIDTH+2,1,tmpstr);
    }
    
};

void PrintOnScreen(uint8_t x, uint8_t y, char * text){
    
    gotoxy(x,y);
    puts(text);
}

void DrawBoard(){

    SetSolidFlag(1);
    SetColor(COLOR_GREEN);
    DrawRectangle(0,230,320-1,240-1);

}

void DrawBoardText(char * str){

    //SetSolidFlag(0);
    SetDrawDefaults(0xf0,COLOR_WHITE, 1, 1, 0);
    //SetColor(COLOR_WHITE);
    Gfx_DrawString(30,232,str);

}

void  DrawArea(){

    SetSolidFlag(1);
    SetColor(COLOR_DARK_GRAY);

    DrawRectangle(0,11,320,229);
    
};
/*
void  DrawSelTabs(uint8_t tab, uint8_t col){
char * tmpstr;

    SetSolidFlag(0);
    tmpstr = tabname[tab];
    Gfx_DrawString(tab*TAB_WIDTH+3,2,tmpstr);
    SetColor(col);
    Gfx_DrawString(tab*TAB_WIDTH+2,1,tmpstr);

};
*/


void DrawScreen(){
    ClearScreen();
    DrawTabs();
    DrawTextTabs();
    DrawBoard();
    DrawArea();
    //DrawSelTabs(1, COLOR_WHITE);
  
    };

int checkMouseAndKey(){
    mouse_state mouseState;

    SetSolidFlag(1);

    mouseState=GetMouseState();
    sprintf(strText," mouse position X: %d  Y: %d Btn1: %d Btn2: %d",mouseState.mouse_x, mouseState.mouse_y, mouseState.btn1, mouseState.btn2);
    DrawBoardText(strText);

    if (mouseState.btn1!=0) //checkArea(); 
    {
        for (int i = 0; i < TAB_COUNT; i++)
        {
            if (mouseState.mouse_x > coordinatesMouse[i][0] && mouseState.mouse_x < coordinatesMouse[i][2] &&
                mouseState.mouse_y > coordinatesMouse[i][1] && mouseState.mouse_y < coordinatesMouse[i][3]) {
                    sprintf(strText," TAB %d",i+1);
                    Gfx_DrawString(40,40,strText);
                    break;
                }
        }
    }
    return 1;
}