#include "gui.hpp"



Gui::Gui()
{
    int rows_grid = 20;
    int cols_grid = 15;

    strcpy(cmdFile," (G)fx:Load | Map:(L)oad (S)ave Save(A)s (N)ew si(Z)e");
    cmdFile[0]= 52;

    //initialize map
    map.SetMapInitialAddress(MMAP_ADDRESS);
    map.SetMapMaxLen(MMAP_MAX_LEN);
    map.SetRowColNrItems(20,15,1);
    
    // Set the offset for the grid
    offset_max_X = rows_grid - NR_TILES_HR;
    offset_max_Y = cols_grid - NR_TILES_VE;
    tile_Selected = 0xff;
    map.SetCursor(0,0,0,0,0,0,0xff); //no tiles present in grid where is the cursor
   
 }

void Gui::ReadGfxValue(){

    blitter.WaitBlitter();
    blitter.BlitterSimpleCopy(0x90,(char *) 0,0,value_gfx,16);
    blitter.WaitBlitter();
    
    nr_tiles = value_gfx[1];
    nr_sprite16 = value_gfx[2];
    nr_sprite32 = value_gfx[3];
    
    //sprintf(strText," %d %d %d ", nr_tiles, nr_sprite16, nr_sprite32);
    //strText[0]=40;
    //graphic.Gfx_DrawString(30,110,strText);

}

void  Gui::DrawTabs(){

    graphic.SetSolidFlag(1);
    //Reset the strip
    graphic.SetColor(COLOR_BLACK);
    graphic.DrawRectangle(0,TITLE_TAB_Y1,320,TITLE_TAB_Y2);

    for (uint8_t t = 0; t < TAB_COUNT; t++)
    {
        graphic.SetColor(COLOR_DARK_GRAY);
        if (t == currentTab ) graphic.SetColor(COLOR_BLUE);
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
    graphic.SetColor(COLOR_BLUE);
    if (currentTab == TAB_EDITOR)
        graphic.DrawRectangle(TAB_BOARD_X1,TAB_BOARD_Y1,TAB_BOARD_X2,TAB_BOARD_Y2);
    else 
        graphic.DrawRectangle(TAB_BOARD_X1,TAB_BOARD_Y1,320,TAB_BOARD_Y2);

}

void Gui::DrawBoardText(char * str){

    DrawBoard(); // delete the previous text
    graphic.SetSolidFlag(0);
    graphic.SetColor(COLOR_WHITE);
    graphic.Gfx_DrawString(0,232,str);

}

void Gui::DrawFilesBox(){

    ShowInfoTabFile();
}

void Gui::DrawTilesInScreen(){
    //draw all tiles togheter
uint8_t x=0, y=0, tile=0;

    for (int y = 0; y < NR_TILES_COl; y++)
    {

        for (int x = 0; x < NR_TILES_ROW; x++)
        {
            graphic.DrawImage(x*TILES_W_H, GRID_Y1+y*TILES_W_H, tile); 
            tile++;
            if (tile >= nr_tiles) break;

        }

        if (tile >= nr_tiles) break;
    }


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
        DrawBoardText(cmdFile);
        /*
        graphic.SetColor(COLOR_WHITE);
        sprintf(strText," TAB %d",tab);
        strText[0]=5;
        graphic.Gfx_DrawString(50,200,strText);
        */
        break;

    case TAB_TILES:
        graphic.SetSolidFlag(1);
        //Clear All
        graphic.SetColor(COLOR_BLACK);
        graphic.DrawRectangle(START_POS_X,0,320,240);

        //Draw the Files Tiles

        graphic.SetColor(COLOR_DARK_GRAY);
        graphic.DrawRectangle(0,TITLE_TAB_Y2+1,320,TAB_BOARD_Y1-1);
        DrawTilesInScreen();
        
        //Print the Number of Tile and Gfx file name
        sprintf(cmdTiles," Tiles Nr: %d | Gfx FileName:%s", nr_tiles, fileNameGfx);
        cmdTiles[0]=60;
        DrawBoardText(cmdTiles);
 
        /*
        graphic.SetColor(COLOR_WHITE);
        sprintf(strText," TAB %d",tab);
        strText[0]=5;
        graphic.Gfx_DrawString(50,200,strText);   
        */    
        break;

    case TAB_EDITOR:
        graphic.SetSolidFlag(1);
        graphic.SetColor(COLOR_BLACK);
        graphic.DrawRectangle(0,TITLE_TAB_Y2+1,TAB_BOARD_X2,TAB_BOARD_Y1-1);
        graphic.DrawRectangle(START_POS_X,0,320,TAB_BOARD_Y2);
        /*
        graphic.SetColor(COLOR_WHITE);
        sprintf(strText," TAB %d",tab);
        strText[0]=5;
        graphic.Gfx_DrawString(50,200,strText);   
        */   
        break;

    case TAB_HELP:
        graphic.SetSolidFlag(1);
        
        //Clear All
        graphic.SetColor(COLOR_BLACK);
        graphic.DrawRectangle(START_POS_X,0,320,240);

        //Draw the Files Config
        graphic.SetColor(COLOR_DARK_GRAY);
        graphic.DrawRectangle(0,TITLE_TAB_Y2+1,320,TAB_BOARD_Y1-1);
        /*
        graphic.SetColor(COLOR_WHITE);
        sprintf(strText," TAB %d",tab);
        strText[0]=5;
        graphic.Gfx_DrawString(50,200,strText);     
        */
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



uint8_t Gui::SetRowColNrItems(uint8_t row, uint8_t col){

    return map.SetRowColNrItems(row,col,1);
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
        DrawCursorSquare();
        break;
    case TAB_HELP:
        DrawArea(TAB_HELP);
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

void Gui::ClearSpaceMap(){

    // Clear the space of tiles
    graphic.SetSolidFlag(1);
    graphic.SetColor(COLOR_BLACK);
    graphic.DrawRectangle(0,TITLE_TAB_Y2-1,START_POS_X-1,TAB_BOARD_Y1-1);
  
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

key_with_Modifier Gui::ActionMouse(int x, int y, uint8_t btn1, uint8_t btn2){
uint8_t i,t, pos_y;
key_with_Modifier key;

    key.chr = 0;
    key.modifier = 0;

    if (btn1 == 1) {
        if ((x >=TITLE_TAB_X1) && (x <= TITLE_TAB_X2)  && (y>=TITLE_TAB_Y1) && (y<= TITLE_TAB_Y2) ) {
            for (i = 0; i < TAB_COUNT; i++)
            {
                if ((mapTabMouse[i][1] <= x) &&  (mapTabMouse[i][3] >= x)) 
                if ((mapTabMouse[i][2] <= y) &&  (mapTabMouse[i][4] >= y)){
                        key.modifier = console.KEY_ALT;
                        key.chr = mapTabMouse[i][5];
                        return key;
                }
            }
        }

        if (currentTab == TAB_EDITOR){
            // Check map
           if ((GRID_X1 <= x) &&  (GRID_X2 >= x)) 
               if ((GRID_Y1 <= y) &&  (GRID_Y2 >= y)){
                    grid_cursor_X = (x-GRID_X1)/TILES_W_H;
                    grid_cursor_Y = (y-GRID_Y1)/TILES_W_H;
                    key.modifier = 0;
                    key.chr = KEY_C_SPACE;
                    return key;
                }
            
        
            // Check Tiles Box
            // Firsrt Col
            if ((START_POS_X <= x) &&  (START_POS_X+TILES_W_H >= x)) 
               if ((START_POS_Y <= y) &&  (START_POS_Y+ (TILES_W_H+1)*NR_ROWS_TILES >= y)){
                    pos_y = (y-START_POS_Y)/(TILES_W_H+1);
                    key.modifier = 0;
                    key.chr = Key_Tile[pos_y][0];
                    return key;
                }
                 

            // Second Col      
            if ((START_POS_X+TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN <= x) &&  (START_POS_X+TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN+TILES_W_H >= x)) 
               if ((START_POS_Y <= y) &&  (START_POS_Y+ (TILES_W_H+1)*NR_ROWS_TILES >= y)){
                    pos_y = (y-START_POS_Y)/(TILES_W_H+1);
                    key.modifier = 0;
                    key.chr = Key_Tile[pos_y+NR_ROWS_TILES][0];
                    return key;
               }

            //Check Cursor for change Tiles (<   > cxursor)
            if (START_POS_X+CHAR_LEN <= x && START_POS_X+CHAR_LEN+8 >=x)
                if ((TAB_BOARD_Y1-1 <= y) &&  (TAB_BOARD_Y1+8 >= y)){
                    key.modifier = 0;
                    key.chr = KEY_PAG_DEC;
                    //delay the click id much fast
                    util.nop_delay(5000);
                    return key;           
                }

            if (START_POS_X+TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN+CHAR_LEN <= x && START_POS_X+TILES_W_H+SPACE_TILE_CHAR+CHAR_LEN+TILES_W_H+CHAR_LEN*2  >=x)
                if ((TAB_BOARD_Y1-1 <= y) &&  (TAB_BOARD_Y1+8 >= y)){
                    key.modifier = 0;
                    key.chr = KEY_PAG_INC;
                    //delay the click id much fast
                    util.nop_delay(5000);
                    return key;           
                }

        } else if (currentTab == TAB_FILES){

        } else if (currentTab == TAB_TILES) {

        }

    }

    return key;
}

void Gui::DrawCursorSquare(){
int pos_with_offset;

    if (tile_Selected == 0xff) return;
    
    //pos_with_offset = offset_Y*STEP_GRID_Y*map.GetRows()+map.GetRows()*grid_cursor_Y_old+offset_X*STEP_GRID_X+grid_cursor_X_old;
    pos_with_offset = offset_Y_old*map.GetRows()+map.GetRows()*grid_cursor_Y_old+offset_X_old+grid_cursor_X_old;
     //Update information for old position of cursor
    map.UpdateCursorFromGrid(grid_cursor_X_old, grid_cursor_Y_old,GRID_X1+grid_cursor_X_old*TILES_W_H, GRID_Y1+grid_cursor_Y_old*TILES_W_H, pos_with_offset);


    if (offset_changed==0) {

        // if ImagaID is -1 then draw a black box else draw the image saved
        if (map.ReadCursorImageID() == 0xff) {
            graphic.SetSolidFlag(0);
            graphic.SetColor(COLOR_BLACK); 
            graphic.DrawRectangle(GRID_X1+grid_cursor_X_old*TILES_W_H,GRID_Y1+grid_cursor_Y_old*TILES_W_H,GRID_X1+grid_cursor_X_old*TILES_W_H+TILES_W_H-1, GRID_Y1+grid_cursor_Y_old*TILES_W_H+TILES_W_H-1);
        } else {
            graphic.SetSolidFlag(1);
            graphic.DrawImage(map.ReadCursorMapX(), map.ReadCursorMapY(), map.ReadCursorImageID());
        }

    }
    else  { //offset is changed so redraw all the grid using the new coordination
        offset_changed = 0;
        ClearSpaceMap();
        LoadMapFromGrid();
        offset_X_old = offset_X;
        offset_Y_old = offset_Y;
    }

    graphic.SetSolidFlag(0);
    graphic.SetColor(COLOR_WHITE); 
    graphic.DrawRectangle(GRID_X1+grid_cursor_X*TILES_W_H,GRID_Y1+grid_cursor_Y*TILES_W_H,GRID_X1+grid_cursor_X*TILES_W_H+TILES_W_H-1, GRID_Y1+grid_cursor_Y*TILES_W_H+TILES_W_H-1);

    grid_cursor_X_old = grid_cursor_X;
    grid_cursor_Y_old = grid_cursor_Y;


    //Print coordinate and Comand for Editor
    sprintf(cmdEditor," X:%d  Y:%d   |  ^(R)efill Map", grid_cursor_X+offset_X, grid_cursor_Y+offset_Y);
    cmdEditor[0]=35;
    DrawBoardText(cmdEditor);

}

void Gui::DrawTileInGrid(){
   if (tile_Selected != 0xff){
        graphic.DrawImage(GRID_X1+grid_cursor_X*TILES_W_H, GRID_Y1+grid_cursor_Y*TILES_W_H, tile_Selected); 

        // Set information for the cursor grid and save in grid
        map.SetCursor(grid_cursor_X, grid_cursor_Y, offset_X, offset_Y, GRID_X1+grid_cursor_X*TILES_W_H, GRID_Y1+grid_cursor_Y*TILES_W_H, tile_Selected);
        map.SaveCursorToGrid();
    }

    //Print coordinate and Comand for Editor. 
    sprintf(cmdEditor," X:%d  Y:%d   |  ^(R)efill Map", grid_cursor_X+offset_X, grid_cursor_Y+offset_Y);
    cmdEditor[0]=35;
    DrawBoardText(cmdEditor);
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
    
void Gui::ActionKey(key_with_Modifier key_mod){
uint8_t exit =0;
char key;

    key =key_mod.chr;

    if (key_mod.modifier == console.KEY_ALT || key_mod.modifier == console.KEY_ALT_GR) {
        // TODO: Verify is the keys are the TAB Key so change the TAB
        switch (key)
        {
        case KEY_C_F1: 
        case KEY_C_F2:
            if (currentTab != TAB_FILES){
                currentTab = TAB_FILES;
                DrawScreen();
                exit =  1;
            }
            break;

        case KEY_C_T1:
        case KEY_C_T2:
            if (currentTab != TAB_TILES){
                currentTab = TAB_TILES;
                DrawScreen();
                exit =  1;
            }
            break;

        case KEY_C_E1:
        case KEY_C_E2:
            if (currentTab != TAB_EDITOR){
                currentTab = TAB_EDITOR;
                DrawScreen(); 
                exit =  1;
            }
            break;
            
        case KEY_C_H1:
        case KEY_C_H2:
            if (currentTab != TAB_HELP){
                currentTab = TAB_HELP;
                DrawScreen(); 
                infoHelp = 1;
                ShowInfoTabHelp();
                exit =  1;
            }
            break;
                            
        default:
            break;
        }
    }

    if (exit == 0) {
        switch (currentTab){
            case TAB_FILES:
                ActionTabFile(key_mod);
                break;
            case TAB_TILES:
                ActionTabTile(key_mod);
                break;
            case TAB_EDITOR:
                ActionTabEditor(key_mod);
                break;
            case TAB_HELP:
                ActionTabHelp(key_mod);
                break;
            default:
                break;
        }
    }
}

void Gui::ActionTabFile(key_with_Modifier key_mod){
uint8_t k,error;
char key;

    key =key_mod.chr;

    switch (key){
        case KEY_C_L1:
        case KEY_C_L2:
            console.clrscr();
            console.SetColorText(COLOR_WHITE, COLOR_BLACK); 
            file.DisplayDirectory();
            console.CheckKeyboardArray();
            console.gotoxy(10,10);
            puts("LOAD FILE MAP \n");
            InputFileName();
            //DrawBoardText((char *)fileName);
            error = map.LoadMap(fileName);
            // Set the offset for the grid
            if (error == 0){
                offset_max_X = map.GetRows() - NR_TILES_HR;
                offset_max_Y = map.GetCols() - NR_TILES_VE;
                console.SetColorText(COLOR_GREEN, COLOR_BLACK); 
                puts("\n \n FILE MAP LOADED");
            } else {
                fileName[0]=0;
                console.SetColorText(COLOR_RED, COLOR_BLACK); 
                puts("\n \n ERROR IN LOAD MAP");
            }
            ReloadTab();
            break;

        case KEY_C_A1:
        case KEY_C_A2:
            console.clrscr();
            console.SetColorText(COLOR_WHITE, COLOR_BLACK); 
            file.DisplayDirectory();
            console.CheckKeyboardArray();
            console.gotoxy(10,10);
            puts("SAVE FILE MAP \n");
            InputFileName();
            //DrawBoardText((char *)fileName);
            error = map.SaveMap(fileName);
            if (error == 0) {
                console.SetColorText(COLOR_GREEN, COLOR_BLACK); 
                puts("\n \n FILE MAP SAVED");
            } else {
                fileName[0]=0;
                console.SetColorText(COLOR_RED, COLOR_BLACK); 
                puts("\n \n ERROR IN SAVE MAP");
            }
            ReloadTab();
            break;
        case KEY_C_S1:
        case KEY_C_S2:
            console.clrscr();
            console.SetColorText(COLOR_WHITE, COLOR_BLACK); 
            if (strlen(fileName) != 0) {  
                error = map.SaveMap(fileName);
                if (error == 0) {
                    console.SetColorText(COLOR_GREEN, COLOR_BLACK); 
                    puts("\n \n FILE MAP SAVED");
                } else {
                    fileName[0]=0;
                    console.SetColorText(COLOR_RED, COLOR_BLACK); 
                    puts("\n \n ERROR IN SAVE MAP");
                }
            } else {
                console.SetColorText(COLOR_RED, COLOR_BLACK);
                puts("\n \n NO FILENAME: PLEASE USE SAVE AS");
            }
            ReloadTab();
            break;
        case KEY_C_N1:
        case KEY_C_N2:
            console.clrscr();
            console.SetColorText(COLOR_WHITE, COLOR_BLACK); 
            console.gotoxy(10,10);
            puts("THE MAP WILL BE EMPTY.\n");
            console.gotoxy(10,20);
            puts("ARE YOU SURE TO CONTINUE (Y/N)?");
            console.CheckKeyboardArray();
            k=console.cgetc();
            if ((k=='Y') || (k=='y')) { 
                ResetMap();
                console.SetColorText(COLOR_GREEN, COLOR_BLACK); 
                puts("\n \n MAP IS EMPTY");
            } else {
                console.SetColorText(COLOR_RED, COLOR_BLACK); 
                puts("\n \n DONE NOTHING ");
            }
            ReloadTab();
            break;

        case KEY_C_G1:
        case KEY_C_G2:
            console.clrscr();
            console.SetColorText(COLOR_WHITE, COLOR_BLACK); 
            file.DisplayDirectory();
            console.CheckKeyboardArray();
            console.gotoxy(10,10);
            puts("CARICA FILE GFX\n");
            InputFileNameGfx();
            //DrawBoardText((char *)fileNameGfx);
            error = file.LoadGrafix(fileNameGfx);
            if (error == 0) {
                console.SetColorText(COLOR_GREEN, COLOR_BLACK); 
                puts("\n \n FILE GFX LOADED\n");
                ReadGfxValue();
            }
            else {
                fileNameGfx[0]=0;
                console.SetColorText(COLOR_RED, COLOR_BLACK); 
                puts("\n \n ERROR IN GFX LOADED");
            }
            ReloadTab();
            break;

        case KEY_C_Z1:
        case KEY_C_Z2:
            console.clrscr();
            console.SetColorText(COLOR_WHITE, COLOR_BLACK); 
            console.CheckKeyboardArray();
            console.gotoxy(10,10);
            puts("Insert the new size of map");
            SetNewMap();
            ReloadTab();
            break;

        default:
            break;
    }
}

void Gui::ActionTabTile(key_with_Modifier key_mod){

}


void Gui::ActionTabEditor(key_with_Modifier key_mod){
char tmp;
char key;

    key =key_mod.chr;

    if (key_mod.modifier == console.KEY_ALT || key_mod.modifier == console.KEY_ALT_GR) {
        switch (key){
                
            case KEY_C_R1:
            case KEY_C_R2:
                FillGrid();
                break;

            default:
            
            break;
        }
    }
    else {

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
                if (grid_cursor_X < 0) {
                    offset_X--;
                    if (offset_X < 0) {
                        offset_X = offset_max_X; 
                        grid_cursor_X=NR_TILES_HR-1;
                    } else grid_cursor_X=0;
                    offset_changed = 1;
                }
                DrawCursorSquare();
                break;
            case KEY_C_RIGHT:
                grid_cursor_X++;
                if (grid_cursor_X >= NR_TILES_HR) {
                    offset_X++;
                    if (offset_X > offset_max_X){
                        offset_X = 0;
                        grid_cursor_X = 0;
                    } else grid_cursor_X = NR_TILES_HR-1;
                    offset_changed = 1;
                }
                DrawCursorSquare();
                break;
            case KEY_C_UP:
                grid_cursor_Y--;
                if (grid_cursor_Y < 0) {
                    offset_Y--;
                    if (offset_Y < 0){ 
                        offset_Y = offset_max_Y; 
                        grid_cursor_Y=NR_TILES_VE-1;
                    } else grid_cursor_Y=0;
                    offset_changed = 1;
                }            
                DrawCursorSquare();
                break;
            case KEY_C_DOWN:
                grid_cursor_Y++;
                if (grid_cursor_Y >= NR_TILES_VE){
                    offset_Y++;
                    if (offset_Y > offset_max_Y){
                        offset_Y = 0;
                        grid_cursor_Y = 0;
                    } else grid_cursor_Y =NR_TILES_VE-1; 
                    offset_changed = 1;        
                }
                DrawCursorSquare();
                break;
            case KEY_C_SPACE:
                    DrawTileInGrid();
                break;
            default:
                checkKeyForSelTile(key);
                break;
        }
    }

    
/*
    graphic.SetColor(COLOR_WHITE);
    graphic.SetSolidFlag(1);
    sprintf(strText," KEY %d %d",tiles_page,end_tiles_page);
    strText[0]=7;
    graphic.Gfx_DrawString(50,150,strText);    
*/
}

void Gui::ActionTabHelp(key_with_Modifier key_mod){
char k;
char key;

    key = key_mod.chr;
    
    switch (key){
        case '1':
            infoHelp = 1;
            DrawArea(TAB_HELP);
            ShowInfoTabHelp();
            break;
        case '2':
            infoHelp = 2;
            DrawArea(TAB_HELP);
            ShowInfoTabHelp();
            break;
        default:
            break;
    }

}

void Gui::ResetMap(){
 
    map.ResetMap();

}

void Gui::FillGrid(){
 
    map.FillMap(tile_Selected);
    LoadMapFromGrid(); 

}


void Gui::SetNewMap(){
uint8_t k, rows, cols, error;
char strNr[10]; 

    console.gotoxy(0,30);
    console.cputc(135);
    puts("\n \nInsert nr rows of map:\n");
    console.CheckKeyboardArray();
    rows = console.ReadNumber(strNr ,3);

    puts("\n \nInsert nr cols of map:\n");
    console.CheckKeyboardArray();
    cols = console.ReadNumber(strNr, 3);

    error =SetRowColNrItems(rows, cols);
    if (error == 0) {
        ResetMap();
        console.SetColorText(COLOR_GREEN, COLOR_BLACK); 
        puts("\n \n MAP RESIZE DONE \n \n");
    }
    else {
        console.SetColorText(COLOR_RED, COLOR_BLACK); 
        puts("\n \n MAP RISIZE ERROR \n \n");
    }
}

uint8_t Gui::WhichTABVisible(){
    return currentTab;
 }

void Gui::LoadMapFromGrid(){
uint8_t tile;
    for (int y = 0; y < NR_TILES_VE; y++)
    {

        for (int x = 0; x < NR_TILES_HR; x++)
        {
            tile = map.GetItemFromGrid(offset_Y*map.GetRows()+map.GetRows()*y+offset_X+x);
            if (tile != 0xff)
                graphic.DrawImage(GRID_X1+x*TILES_W_H, GRID_Y1+y*TILES_W_H, tile); 

        }

    }


}

void Gui::InputFileName(){

	console.gotoxy(0, 14);
	console.cputc(135);
	puts("Enter the file name for Map: \n");

    console.ReadString (fileName);
}

void Gui::InputFileNameGfx(){

	console.gotoxy(0, 14);
	console.cputc(135);
	puts("Enter the file name for Gfx: \n");

    console.ReadString (fileNameGfx);

}

void Gui::ShowInfoTabFile(){

    graphic.SetSolidFlag(0);

    sprintf(strInfo1, " INFORMATION:");
    graphic.SetColor(COLOR_ORANE);
    graphic.Gfx_DrawString(10,40,strInfo1);

    sprintf(strInfo1, " File GFX: %s \n",fileNameGfx);
	sprintf(strInfo2, " Nr. Tiles: %d \n",nr_tiles );
    sprintf(strInfo3, " File Map: %s \n",fileName);
	sprintf(strInfo4, " Nr. Rows: %d  Nr. Cols: %d \n",map.GetRows(), map.GetCols());
	sprintf(strInfo6, " Max memory: %d  Used Memory: %d \n",map.GetMaxMemory(), map.GetUsedMemory());	
    strInfo6[0]=60;

    sprintf(strInfo5, " Mapper - Map editor for NEO6502            Vers 1.1");
    strInfo5[0]=60;

   

    
    graphic.SetColor(COLOR_WHITE);
    graphic.Gfx_DrawString(10,70,strInfo1);
    graphic.Gfx_DrawString(10,90,strInfo2);
    graphic.Gfx_DrawString(10,110,strInfo3);
    graphic.Gfx_DrawString(10,130,strInfo4);
    graphic.Gfx_DrawString(10,150,strInfo6);
    
    graphic.SetColor(COLOR_DARK_GREEN);
    graphic.Gfx_DrawString(10,220,strInfo5);
    /*
	console.gotoxy(0, 40);
	console.SetColorText(COLOR_WHITE, COLOR_DARK_GRAY);
    sprintf(strInfo1, " File GFX: %s \n",fileNameGfx);
	sprintf(strInfo2, " Nr. Tiles: %d \n",nr_tiles );
    sprintf(strInfo3, " File Map: %s \n",fileName);
	sprintf(strInfo4, " Nr. Rows: %d  Nr. Cols: %d \n",map.GetRows(), map.GetCols());

	puts(strInfo1);
	puts(strInfo2);
	puts(strInfo3);
	puts(strInfo4);
    */
}

 void Gui::ReloadTab(){

    puts("\n Press AnyKey \n");
    console.CheckKeyboardArray();
    console.cgetc();
    DrawScreen();

 }

void Gui::ShowInfoTabHelp(){

    graphic.SetSolidFlag(0);
    graphic.SetColor(COLOR_WHITE);
    strInfo5[0]=60;

    if (infoHelp == 1){
        sprintf(strInfo5, " Load the graphic file containing the tiles to use");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,20,strInfo5);
        sprintf(strInfo5, " with the \"Load Graphics\" function found in the File");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,30,strInfo5);
        sprintf(strInfo5, " tab. From here, you can also load a previously saved");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,40,strInfo5);
        sprintf(strInfo5, " map through the Save As commands. If you have already\n");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,50,strInfo5);
        sprintf(strInfo5, " set the file name using the Load Map or Save As \n");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,60,strInfo5);
        sprintf(strInfo5, " commands before, you can use the Save command to \n");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,70,strInfo5);
        sprintf(strInfo5, " avoid typing the file name again. If you want to");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,80,strInfo5);    
        sprintf(strInfo5, " change the file name, use the Save As command. The ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,90,strInfo5); 
        sprintf(strInfo5, " character \"^\" indicates that the \"CTRL\" key must be");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,100,strInfo5); 
        sprintf(strInfo5, " pressed.");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,110,strInfo5); 
        sprintf(strInfo5, " You can configure the map using the Size command: you");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,120,strInfo5);
        sprintf(strInfo5, " will enter the values of the rows and columns of the");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,130,strInfo5);
        sprintf(strInfo5, " map. This will allow you to use a map larger than the ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,140,strInfo5);    
        sprintf(strInfo5, " screen, enabling scrolling in your programs/games. ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,150,strInfo5); 
        sprintf(strInfo5, " See the attached basic example to see how to do this. ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,160,strInfo5); 
        sprintf(strInfo5, " Alternatively, see my demo of a game written in the ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,170,strInfo5); 
        sprintf(strInfo5, " C language.");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,180,strInfo5); 
        sprintf(strInfo5, " Additionally, using the New command, you can delete");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,190,strInfo5); 
        sprintf(strInfo5, " /reset the map while keeping the size unchanged.");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,200,strInfo5); 
        sprintf(strInfo5, " In the Tiles tab, you can see all the tiles loaded ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,210,strInfo5); 
        sprintf(strInfo5, " from the graphic file.");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,220,strInfo5); 
    } else {
        sprintf(strInfo5, " In the Editor tab, you can draw the map. First, you");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,20,strInfo5);
        sprintf(strInfo5, " must have loaded them in the Files tab. Use the");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,30,strInfo5);
        sprintf(strInfo5, " arrow keys to navigate the map and the Space key");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,40,strInfo5);
        sprintf(strInfo5, " to copy the selected tile onto the map. Alternatively,");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,50,strInfo5);
        sprintf(strInfo5, " use the left mouse button. ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,60,strInfo5);
        sprintf(strInfo5, " If the map is larger than the visible portion, use");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,70,strInfo5);
        sprintf(strInfo5, " the arrow keys to load the non-visible part.To select ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,80,strInfo5);
        sprintf(strInfo5, " the tile, you can use the characters from \"0\" to \"P\" ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,90,strInfo5);
        sprintf(strInfo5, " listed to the right of the tiles, or select one with the ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,100,strInfo5);
        sprintf(strInfo5, " mouse (left button). There are 26 tiles in the box on ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,110,strInfo5);
        sprintf(strInfo5, " the right. Use the \">\" key (or click on it with the ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,120,strInfo5);
        sprintf(strInfo5, " mouse) to load another 26 tiles. Use the \"<\" key to");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,130,strInfo5);
        sprintf(strInfo5, " load the previous 26 tiles. You can use the Refill ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,140,strInfo5);
        sprintf(strInfo5, " command to fill the map with the selected tile. Tiles ");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,150,strInfo5);
        sprintf(strInfo5, " already present in the map will not be overwritten.");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,160,strInfo5);

        graphic.SetColor(COLOR_DARK_GREEN);
        sprintf(strInfo5, " Mapper by Giovanni Pozzobon aka Jobond - 2024");
        strInfo5[0]=60;
        graphic.Gfx_DrawString(1,220,strInfo5);
    }
    
    strcpy(cmdHelp," (1) Page - (2) Page");
    cmdHelp[0]= 20;
    DrawBoardText(cmdHelp);

}