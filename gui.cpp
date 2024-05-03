#include "gui.hpp"


void Gui::ReadGfxValue(){

    blitter.WaitBlitter();
    blitter.BlitterSimpleCopy(0x90,(char *) 0,0,value_gfx,16);
    blitter.WaitBlitter();
    
    nr_tiles = value_gfx[1];
    nr_sprite16 = value_gfx[2];
    nr_sprite32 = value_gfx[3];
    
    sprintf(strText," %d %d %d ", nr_tiles, nr_sprite16, nr_sprite32);
    strText[0]=40;
    graphic.Gfx_DrawString(30,110,strText);

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

void Gui::DrawFilesBox(){

	console.gotoxy(16, 10);
	console.cputc(0x81);
	sprintf(strText, "FILE TILES:");
	puts(strText);

	console.gotoxy(5, 20);
	console.cputc(143);
	puts("TILES:");

}

void Gui::DrawArea(uint8_t tab){

    switch (tab)
    {
    case TAB_FILES:
        graphic.SetSolidFlag(1);
        //Clear All
        graphic.SetColor(COLOR_BLACK);
        graphic.DrawRectangle(START_POS_X,0,320,240);

        //Draw the Files space
        graphic.SetColor(COLOR_DARK_GRAY);
        graphic.DrawRectangle(0,TITLE_TAB_Y2+1,320,TAB_BOARD_Y1-1);

        // Prepare for imput
        DrawFilesBox();
        graphic.SetColor(COLOR_WHITE);
        sprintf(strText," TAB %d",tab);
        strText[0]=5;
        graphic.Gfx_DrawString(50,200,strText);
        break;

    case TAB_TILES:
        graphic.SetSolidFlag(1);
        //Clear All
        graphic.SetColor(COLOR_BLACK);
        graphic.DrawRectangle(START_POS_X,0,320,240);

        //Draw the Files Tiles

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
        graphic.DrawRectangle(0,TITLE_TAB_Y2+1,TAB_BOARD_X2,TAB_BOARD_Y1-1);
        graphic.DrawRectangle(START_POS_X,0,320,TAB_BOARD_Y2);
        graphic.SetColor(COLOR_WHITE);
        sprintf(strText," TAB %d",tab);
        strText[0]=5;
        graphic.Gfx_DrawString(50,200,strText);      
        break;

    case TAB_CONFIG:
        graphic.SetSolidFlag(1);
        
        //Clear All
        graphic.SetColor(COLOR_BLACK);
        graphic.DrawRectangle(START_POS_X,0,320,240);

        //Draw the Files Config
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

Gui::Gui()
{
      //initialize map
    map.SetMapInitialAddress(MMAP_ADDRESS);
    map.SetMapMaxLen(MMAP_MAX_LEN);
    map.SetRowColNrItems(20,15);
    map.SetCursor(0,0,0,0,0xff); //no tiles present in grid where is the cursor
}

uint8_t Gui::SetRowColNrItems(uint8_t row, uint8_t col){

    return map.SetRowColNrItems(row,col);
}


void Gui::DrawScreen()
{
    DrawTabs();
    DrawTextTabs();
    DrawBoard();


    // If the firt time select the first tab only for Debug
    //if (currentTab==0) currentTab =2;

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
        LoadMapFromGrid(); 
        break;
    case TAB_CONFIG:
        DrawArea(TAB_CONFIG);
        break;
    
    default:
        break;
    }

    //DrawSelTabs(1, COLOR_WHITE);
};

void Gui::ClearSpaceTiles(){

    // Clear the space of tiles
    graphic.SetSolidFlag(1);
    graphic.SetColor(COLOR_BLACK);
    graphic.DrawRectangle(START_POS_X-1,START_POS_Y,START_POS_X+TILES_W_H,TAB_BOARD_Y1-1);
    graphic.DrawRectangle(START_POS_X+TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN-1,START_POS_Y,START_POS_X+2*TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN,TAB_BOARD_Y1-1);
}

void Gui::DrawTilesBox(){
    uint8_t t,exit =0;

    ClearSpaceTiles();

    for (uint8_t i = 0; i < NR_ROWS_TILES; i++)
    {
        // tiles are paged: 26 items for page
        t=(2*tiles_page*NR_ROWS_TILES) + i;
        if (t>=nr_tiles) { //  >= because we start from 0 and not from 1
            end_tiles_page = tiles_page;
            exit=1;
            break;
         } // when arrive to the last tile exit

        graphic.DrawImage(START_POS_X, START_POS_Y+ (TILES_W_H+1)*i, t);       

    }

    if (exit==1) return;

    for (uint8_t i = 0; i < NR_ROWS_TILES; i++)
    {
        // tiles are paged: 26 items for page and first 13 have already drawed
        t=(2*tiles_page*NR_ROWS_TILES)+ NR_ROWS_TILES + i;

        if (t>=nr_tiles) { //  >= because we start from 0 and not from 1
            end_tiles_page = tiles_page;
            break;
         } // when arrive to the last tile exit
        
        graphic.DrawImage(START_POS_X+TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN, START_POS_Y+ (TILES_W_H+1)*i, t);  

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
        graphic.Gfx_DrawString(START_POS_X+TILES_W_H+3, 4+START_POS_Y+(TILES_W_H+1)*i,strChar);
        strChar[1]= Key_Tile[i+NR_ROWS_TILES][0];
        graphic.Gfx_DrawString(START_POS_X+TILES_W_H*2+SPACE_TILE_CHAR*2+CHAR_LEN,4+START_POS_Y+ (TILES_W_H+1)*i,strChar);
    }

    // Write the page symbols
    strChar[1]= KEY_PAG_DEC;
    graphic.Gfx_DrawString(START_POS_X+CHAR_LEN-3, TAB_BOARD_Y1, strChar);
    strChar[1]= KEY_PAG_INC;
    graphic.Gfx_DrawString(START_POS_X+TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN+CHAR_LEN-1, TAB_BOARD_Y1, strChar);
}

    void Gui::ActionMouse(int x, int y, uint8_t btn1, uint8_t btn2){

}

void Gui::DrawCursorSquare(){

     //Update information for new position of cursor 
    map.UpdateCursorFromGrid(grid_cursor_X_old, grid_cursor_Y_old,GRID_X1+grid_cursor_X_old*TILES_W_H, GRID_Y1+grid_cursor_Y_old*TILES_W_H);

    // if ImagaID is -1 then draw a black box else draw the image saved
    if (map.ReadCursorImageID() == 0xff) {
        graphic.SetSolidFlag(0);
        graphic.SetColor(COLOR_BLACK); 
        graphic.DrawRectangle(GRID_X1+grid_cursor_X_old*TILES_W_H,GRID_Y1+grid_cursor_Y_old*TILES_W_H,GRID_X1+grid_cursor_X_old*TILES_W_H+TILES_W_H-1, GRID_Y1+grid_cursor_Y_old*TILES_W_H+TILES_W_H-1);
    } else {
        graphic.SetSolidFlag(1);
        graphic.DrawImage(map.ReadCursorMapX(), map.ReadCursorMapY(), map.ReadCursorImageID());
    }

    graphic.SetSolidFlag(0);
    graphic.SetColor(COLOR_WHITE); 
    graphic.DrawRectangle(GRID_X1+grid_cursor_X*TILES_W_H,GRID_Y1+grid_cursor_Y*TILES_W_H,GRID_X1+grid_cursor_X*TILES_W_H+TILES_W_H-1, GRID_Y1+grid_cursor_Y*TILES_W_H+TILES_W_H-1);

    grid_cursor_X_old = grid_cursor_X;
    grid_cursor_Y_old = grid_cursor_Y;


}

void Gui::DrawTileInGrid(){

    graphic.DrawImage(GRID_X1+grid_cursor_X*TILES_W_H, GRID_Y1+grid_cursor_Y*TILES_W_H, tile_Selected); 

    // Set information for the cursor grid and save in grid
    map.SetCursor(grid_cursor_X, grid_cursor_Y, GRID_X1+grid_cursor_X*TILES_W_H, GRID_Y1+grid_cursor_Y*TILES_W_H, tile_Selected);
    map.SaveCursorToGrid();

}

void Gui::checkKeyForSelTile(char key){
    uint8_t pos;
    for (uint8_t i = 0; i < NR_ROWS_TILES*2+16; i++)
    {

        if (Key_Tile[i][0] == key) {
            tile_Selected = Key_Tile[i][1]+(2*tiles_page*NR_ROWS_TILES);

            //Delete a rectangle around the OLD tiles selected
            graphic.SetSolidFlag(0);
            graphic.SetColor(COLOR_BLACK); 
            graphic.DrawRectangle(old_red_square_tiles_X1,old_red_square_tiles_Y1,old_red_square_tiles_X2,old_red_square_tiles_Y2); 



            if ((i<NR_ROWS_TILES) || (key== 97) || (key==98) || (key==99)){
                if (i<NR_ROWS_TILES) {pos=i;} else {pos=i-16;}  
                /*
                graphic.SetSolidFlag(1);
                graphic.SetColor(COLOR_WHITE);
                sprintf(strText," I %d %d",pos, key);
                strText[0]=10;
                graphic.Gfx_DrawString(50,180,strText); */

                // here we are on then first column
                //recalculate the new position and update the coordinates
                old_red_square_tiles_X1= START_POS_X-1 ;
                old_red_square_tiles_X2= START_POS_X+TILES_W_H;
                old_red_square_tiles_Y1= START_POS_Y-1+ (TILES_W_H+1)*pos;
                old_red_square_tiles_Y2= START_POS_Y+ TILES_W_H +(TILES_W_H+1)*pos;               
               
            } else {

                if (i<2*NR_ROWS_TILES) {pos=i-13;} else {pos=i-29;}
                /*
                graphic.SetSolidFlag(1);               
                graphic.SetColor(COLOR_WHITE);
                 sprintf(strText," Q %d %d",pos, key);
                strText[0]=10;
                graphic.Gfx_DrawString(50,180,strText);  */

               // here we are on then first column
                //recalculate the new position and update the coordinates
                old_red_square_tiles_X1= START_POS_X-1+TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN;
                old_red_square_tiles_X2= START_POS_X+TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN+TILES_W_H;
                old_red_square_tiles_Y1= START_POS_Y+ (TILES_W_H+1)*pos;
                old_red_square_tiles_Y2= START_POS_Y+ (TILES_W_H+1)*pos+TILES_W_H;  

            }
            
            //Draw a rectangle around the tiles selected
            graphic.SetSolidFlag(0);
            graphic.SetColor(COLOR_RED);     
            graphic.DrawRectangle(old_red_square_tiles_X1,old_red_square_tiles_Y1,old_red_square_tiles_X2,old_red_square_tiles_Y2);    

            break;
        }

    }

}
    
void Gui::ActionKey(char key){
uint8_t exit =0;

    // TODO: Verify is the keys are the TAB Key so change the TAB
    switch (key)
    {
    case KEY_C_Q1: 
    case KEY_C_Q2:
        if (currentTab != TAB_FILES){
            currentTab = TAB_FILES;
            DrawScreen();
            exit =  1;
        }
        break;

     case KEY_C_W1:
     case KEY_C_W2:
        if (currentTab != TAB_TILES){
            currentTab = TAB_TILES;
            DrawScreen();
             exit =  1;
        }
        break;

    case KEY_C_R1:
    case KEY_C_R2:
        if (currentTab != TAB_EDITOR){
            currentTab = TAB_EDITOR;
            DrawScreen(); 
            exit =  1;
        }
        break;
        
    case KEY_C_T1:
    case KEY_C_T2:
        if (currentTab != TAB_CONFIG){
            currentTab = TAB_CONFIG;
            DrawScreen(); 
            exit =  1;
        }
        break;
                        
    default:
        break;
    }

    if (exit == 0) {
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
}

void Gui::ActionTabFile(char key){
uint8_t k;
unsigned char namefileGfx[] = {12, 'g', 'r', 'a', 'p', 'h', 'i', 'c', 's', '.', 'g', 'f', 'x'};
unsigned char namefileMap[] = {8, 'm', 'a', 'p', '0', '.', 'm', 'a', 'p'};

    switch (key){
        case KEY_C_L1:
        case KEY_C_L2:
            console.clrscr();
            file.DisplayDirectory();
            console.CheckKeyboardArray();
            console.gotoxy(10,10);
            puts("CARICA FILE MAP");
            //console.ReadLine((int) namefile);
            //puts((char *) namefile);
            map.LoadMap(namefileMap);
            break;

        case KEY_C_S1:
        case KEY_C_S2:
            console.clrscr();
            file.DisplayDirectory();
            console.CheckKeyboardArray();
            console.gotoxy(10,10);
            puts("SAVE FILE MAP");
            //console.ReadLine((int) namefile);
            //puts((char *) namefile);
            map.SaveMap(namefileMap);
            break;

        case KEY_C_N1:
        case KEY_C_N2:
            console.clrscr();
            console.gotoxy(0,10);
            puts("THE MAP WILL BE DELETE. ARE YOU SURE TO CONTINUE (Y/N)?");
            console.CheckKeyboardArray();
            k=console.cgetc();
            if ((k=='Y') || (k=='y')) ResetMap();
            break;

        case KEY_C_G1:
        case KEY_C_G2:
            console.clrscr();
            file.DisplayDirectory();
            console.CheckKeyboardArray();
            console.gotoxy(10,10);
            puts("CARICA FILE GFX");
            //console.ReadLine((int) namefile);
            //puts((char *) namefile);
            file.LoadGrafix(namefileGfx);
            ReadGfxValue();
            break;

        case KEY_C_A1:
        case KEY_C_A2:
            break;

        default:
            break;
    }
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
            if (tiles_page<end_tiles_page) tiles_page++;
            DrawTilesBox();
            tmp='I';
            break;
        case KEY_C_LEFT:
            grid_cursor_X--;
            if (grid_cursor_X < 0) grid_cursor_X=NR_TILES_HR-1;
            DrawCursorSquare();
            break;
        case KEY_C_RIGHT:
            grid_cursor_X++;
            if (grid_cursor_X >= NR_TILES_HR) grid_cursor_X=0;
            DrawCursorSquare();
            break;
        case KEY_C_UP:
            grid_cursor_Y--;
            if (grid_cursor_Y < 0) grid_cursor_Y=NR_TILES_VE-1;            
            DrawCursorSquare();
            break;
        case KEY_C_DOWN:
            grid_cursor_Y++;
            if (grid_cursor_Y >= NR_TILES_VE) grid_cursor_Y=0;            
            DrawCursorSquare();
            break;
        case KEY_C_SPACE:
            DrawTileInGrid();
            break;
        default:
            checkKeyForSelTile(key);
            break;
    }

    graphic.SetColor(COLOR_WHITE);
    graphic.SetSolidFlag(1);
    sprintf(strText," KEY %d %d",tiles_page,end_tiles_page);
    strText[0]=7;
    graphic.Gfx_DrawString(50,150,strText);    
}

void Gui::ActionTabConfig(char key){
char k;
    switch (key){
        case KEY_C_N1:
        case KEY_C_N2:
            break;
        default:
            break;
    }

}

void Gui::ResetMap(){
uint8_t k, rows, cols;
 
    map.ResetMap();

}

void Gui::SetNewMap(){
uint8_t k, rows, cols;
 

    console.clrscr();
    console.gotoxy(10,10);
    puts("INSERT NR ROWS OF MAP");
    console.CheckKeyboardArray();
    k=console.cgetc();

    console.clrscr();
    console.gotoxy(10,40);
    puts("INSERT NR COLS OF MAP");
    console.CheckKeyboardArray();
    k=console.cgetc();

}

uint8_t Gui::WhichTABVisible(){
    return currentTab;
 }

void Gui::LoadMapFromGrid(){
uint8_t tile;
    for (int y = 0; y < map.GetCols(); y++)
    {

        for (int x = 0; x < map.GetRows(); x++)
        {
            tile = map.GetItemFromGrid(map.GetRows()*y+x);
            if (tile != 0xff)
                graphic.DrawImage(GRID_X1+x*TILES_W_H, GRID_Y1+y*TILES_W_H, tile); 

        }
    }


}
