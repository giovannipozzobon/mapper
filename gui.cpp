#include "gui.hpp"


void Gui::ReadGfxValue(){
    
    blitter.WaitBlitter();
    blitter.BlitterSimpleCopy(0x90,(char *) 0,0,value_gfx,16);
    blitter.WaitBlitter();
    
    nr_tiles = value_gfx[1];
    nr_sprite16 = value_gfx[2];
    nr_sprite32 = value_gfx[3];
    /*
    sprintf(strText," %d %d %d ", nr_tiles, nr_sprite16, nr_sprite32);
    strText[0]=40;
    graphic.Gfx_DrawString(30,110,strText);
    */
}

void  Gui::DrawTabs(){

    graphic.SetSolidFlag(1);
    graphic.SetColor(COLOR_DARK_GRAY);

    for (uint8_t t = 0; t < TAB_COUNT; t++)
    {
        graphic.DrawRectangle(TITLE_TAB_X1+t*TAB_WIDTH,TITLE_TAB_Y1,TITLE_TAB_X1+t*TAB_WIDTH+TAB_WIDTH-2,TITLE_TAB_Y2);
    }
    
};

void  Gui::DrawTextTabs(){
    char * tmpstr;

    graphic.SetSolidFlag(0);
  
    for (uint8_t t = 0; t < TAB_COUNT; t++)
    {
        tmpstr = tabname[t];
        graphic.SetColor(COLOR_BLACK);
        graphic.Gfx_DrawString(TITLE_TAB_X1+t*TAB_WIDTH+3,TITLE_TAB_Y1+2,tmpstr);
        graphic.SetColor(COLOR_WHITE);
        graphic.Gfx_DrawString(TITLE_TAB_X1+t*TAB_WIDTH+2,TITLE_TAB_Y1+1,tmpstr);
    }

};

void Gui::DrawBoard(){

    graphic.SetSolidFlag(1);
    graphic.SetColor(COLOR_LIGTH_GRAY);
    graphic.DrawRectangle(TAB_BOARD_X1,TAB_BOARD_Y1,TAB_BOARD_X2,TAB_BOARD_Y2);

}

void Gui::DrawBoardText(char * str){

    DrawBoard(); // delete the previous text
    graphic.SetSolidFlag(0);
    graphic.SetColor(COLOR_WHITE);
    graphic.Gfx_DrawString(30,232,str);

}

void Gui::DrawArea(uint8_t tab){

    switch (tab)
    {
    case TAB_FILES:
        graphic.SetSolidFlag(1);
        graphic.SetColor(COLOR_DARK_GRAY);
        graphic.DrawRectangle(0,TITLE_TAB_Y2+1,320,TAB_BOARD_Y1-1);
        graphic.SetColor(COLOR_WHITE);
        sprintf(strText," TAB %d",tab);
        strText[0]=5;
        graphic.Gfx_DrawString(50,200,strText);
        break;

    case TAB_TILES:
        graphic.SetSolidFlag(1);
        graphic.SetColor(COLOR_DARK_GRAY);
        graphic.DrawRectangle(0,TITLE_TAB_Y2+1,320,TAB_BOARD_Y1-1);
        graphic.SetColor(COLOR_WHITE);
        sprintf(strText," TAB %d",tab);
        strText[0]=5;
        graphic.Gfx_DrawString(50,200,strText);       
        break;

    case TAB_EDITOR:
        graphic.SetSolidFlag(1);
        graphic.SetColor(COLOR_BLACK);
        graphic.DrawRectangle(0,TITLE_TAB_Y2+1,START_POS_X-1,TAB_BOARD_Y1-1);
        graphic.DrawRectangle(START_POS_X,TAB_BOARD_Y1,320,TAB_BOARD_Y2);
        graphic.SetColor(COLOR_WHITE);
        sprintf(strText," TAB %d",tab);
        strText[0]=5;
        graphic.Gfx_DrawString(50,200,strText);      
        break;

    case TAB_CONFIG:
        graphic.SetSolidFlag(1);
        graphic.SetColor(COLOR_DARK_GRAY);
        graphic.DrawRectangle(0,TITLE_TAB_Y2+1,320,TAB_BOARD_Y1-1);
        graphic.SetColor(COLOR_WHITE);
        sprintf(strText," TAB %d",tab);
        strText[0]=5;
        graphic.Gfx_DrawString(50,200,strText);     
        break;
    
    default:
        break;
    }


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

    DrawTabs();
    DrawTextTabs();
    DrawBoard();


    // If the firt time select the first tab
    if (currentTab==0) currentTab =2;

    switch (currentTab)
    {
    case TAB_FILES:
        DrawArea(TAB_FILES);
        break;
    case TAB_TILES:
        DrawArea(TAB_TILES);
        break;
    case TAB_EDITOR:
        DrawArea(TAB_EDITOR);
        DrawTilesBox();
        DrawKeyTitle(); 
        break;
    case TAB_CONFIG:
        DrawArea(TAB_CONFIG);
        break;
    
    default:
        break;
    }

    //DrawSelTabs(1, COLOR_WHITE);

  
};

void Gui::DrawTilesBox(){
    uint8_t t;


    for (uint8_t i = 0; i < NR_ROWS_TILES; i++)
    {
        // tiles are paged: 26 items for page
        t=(2*tiles_page*NR_ROWS_TILES) + i;

        graphic.DrawImage(START_POS_X, START_POS_Y+ TILES_W_H*i, t); 
        graphic.DrawImage(START_POS_X+TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN, START_POS_Y+ TILES_W_H*i, t+NR_ROWS_TILES);        

    }


}

void Gui::DrawKeyTitle(){

    // Set the settings to write texts
    graphic.SetSolidFlag(0);
    graphic.SetColor(COLOR_WHITE);

    // tiles are paged: 26 items for page
    for (uint8_t i = 0; i < NR_ROWS_TILES; i++)
    {
        strChar[1]= Key_Tile[i][0];
        graphic.Gfx_DrawString(START_POS_X+TILES_W_H+3, 4+START_POS_Y+TILES_W_H*i,strChar);
        strChar[1]= Key_Tile[i+NR_ROWS_TILES][0];
        graphic.Gfx_DrawString(START_POS_X+TILES_W_H*2+SPACE_TILE_CHAR*2+CHAR_LEN,4+START_POS_Y+ TILES_W_H*i,strChar);
    }

    // Write the page symbols
    strChar[1]= KEY_PAG_DEC;
    graphic.Gfx_DrawString(START_POS_X+CHAR_LEN-3, TAB_BOARD_Y1, strChar);
    strChar[1]= KEY_PAG_INC;
    graphic.Gfx_DrawString(START_POS_X+TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN+CHAR_LEN-1, TAB_BOARD_Y1, strChar);
}

    void Gui::ActionMouse(int x, int y, uint8_t btn1, uint8_t btn2){

    }

    
void Gui::ActionKey(char key){

    // TODO: Verify is the keys are the TAB Key so change the TAB


    switch (currentTab){
        case TAB_FILES:
            ActionTabFile(key);
            break;
        case TAB_TILES:
            ActionTabTile(key);
            break;
        case TAB_EDITOR:
            ActionTabEditor(key);
            break;
        case TAB_CONFIG:
            ActionTabConfig(key);
            break;
        default:
            break;
    }


}

void Gui::ActionTabFile(char key){

}

void Gui::ActionTabTile(char key){

}

void Gui::ActionTabEditor(char key){
char tmp;
    switch (key){
        case KEY_PAG_DEC:
            if (tiles_page>0) tiles_page--;
            DrawTilesBox();
            tmp='D';
            break;
        case KEY_PAG_INC:
            if (tiles_page<MAX_PAGE_TILE-1) tiles_page++;
            DrawTilesBox();
            tmp='I';
            break;
        default:
            break;
    }
    graphic.SetColor(COLOR_WHITE);
    graphic.SetSolidFlag(1);
    sprintf(strText," KEY %d",tiles_page);
    strText[0]=5;
    graphic.Gfx_DrawString(50,150,strText);    
}

void Gui::ActionTabConfig(char key){

}
