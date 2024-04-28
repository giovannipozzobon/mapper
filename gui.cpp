#include "gui.hpp"
#include "api.hpp"


void  Gui::DrawTabs(){

    api.SetSolidFlag(1);
    api.SetColor(COLOR_DARK_GRAY);

    for (uint8_t t = 0; t < TAB_COUNT; t++)
    {
        api.DrawRectangle(t*TAB_WIDTH,0,t*TAB_WIDTH+TAB_WIDTH-2,10);
    }
    
};

void  Gui::DrawTextTabs(){
    char * tmpstr;

    api.SetSolidFlag(0);
    
  
    for (uint8_t t = 0; t < TAB_COUNT; t++)
    {
        tmpstr = tabname[t];
        api.SetColor(COLOR_BLACK);
        api.Gfx_DrawString(t*TAB_WIDTH+3,2,tmpstr);
        api.SetColor(COLOR_WHITE);
        api.Gfx_DrawString(t*TAB_WIDTH+2,1,tmpstr);
    }
    
};

void Gui::PrintOnScreen(uint8_t x, uint8_t y, char * text){
    
    api.gotoxy(x,y);
    puts(text);
}

void Gui::DrawBoard(){

    api.SetSolidFlag(1);
    api.SetColor(COLOR_GREEN);
    api.DrawRectangle(0,230,320-1,240-1);

}

void Gui::DrawBoardText(char * str){

    //SetSolidFlag(0);
    api.SetDrawDefaults(0xf0,COLOR_WHITE, 1, 1, 0);
    //SetColor(COLOR_WHITE);
    api. Gfx_DrawString(30,232,str);

}

void Gui::DrawArea(uint8_t tab){

    api.SetSolidFlag(1);
    api.SetColor(COLOR_DARK_GRAY);

    api.DrawRectangle(0,11,320,229);

    sprintf(strText," TAB %d",tab);
    strText[0]=5;
    api.Gfx_DrawString(50,200,strText);

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


void Gui::DrawScreen(){
    api.ClearScreen();
    DrawTabs();
    DrawTextTabs();
    DrawBoard();

    // If the firt time select the first tab
    if (currentTab==0) currentTab =1;

    switch (currentTab)
    {
    case 1:
        DrawArea(1);
        break;
    case 2:
        DrawArea(2);
        break;
    case 3:
        DrawArea(3);
        break;
    case 4:
        DrawArea(4);
        break;
    
    default:
        break;
    }

    //DrawSelTabs(1, COLOR_WHITE);
  
};

