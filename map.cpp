#include "map.hpp"


uint8_t Map::FillMem(uint8_t value){
    if ((grid_addr_ram == 0) || (max_len_map ==0)) return ERROR;

    for(int i=0; i<nr_item; i++){
       grid_addr_ram[i]= value;

    }    
    return OK;
}

uint8_t Map::LoadMap(unsigned char * namefile){
    //code
    return 0;
}


uint8_t Map::SaveMap(unsigned char * namefile){
    //code
    return 0;
}


void Map::AddItem(uint8_t imageID, uint8_t pos_x, uint8_t pos_y){

}


void Map::DelItem(uint8_t imageID, uint8_t pos_x, uint8_t pos_y){

}


void Map::SetMapInitialAddress(int address){
    grid_addr_ram = (char *) address;
}

void Map::SetMapMaxLen(int len){
    max_len_map = len;
    max_addr_ram = grid_addr_ram + len;
}

uint8_t Map::SetRowColNrItems(uint8_t row, uint8_t col){

    NrRow = row;
    NrCol = col;
    nr_item = (int) row * (int) col;
    if (nr_item > max_len_map) 
        return ERROR; 
    else{ 
        //Fill the memory with map default value (empty)
        FillMem(0xff);
        return OK;
    }

}

 void Map::SetCursor(uint8_t cursor_grid_x, uint8_t cursor_grid_y, int cursor_map_x, int cursor_map_y, uint8_t imageID){
    cursor.cursor_grid_x = cursor_grid_x;
    cursor.cursor_grid_y = cursor_grid_y;
    cursor.cursor_map_x = cursor_map_x;
    cursor.cursor_map_y = cursor_map_y;
    cursor.imageID = imageID;

 }

uint8_t Map::ReadCursorImageID(){return cursor.imageID;}

int Map::ReadCursorMapX(){ return cursor.cursor_map_x;}

int Map::ReadCursorMapY(){ return cursor.cursor_map_y;}

void Map::UpdateCursorFromGrid(uint8_t grid_x, uint8_t grid_y, int map_x, int map_y){
    //take the imageId from memory
    cursor.imageID=grid_addr_ram[grid_x+grid_y*NrRow];
    cursor.cursor_grid_x = grid_x;
    cursor.cursor_grid_y = grid_y;
    cursor.cursor_map_x=map_x;
    cursor.cursor_map_y=map_y;
}

void Map::SaveCursorToGrid(){
    grid_addr_ram[cursor.cursor_grid_x+cursor.cursor_grid_y*NrRow] = cursor.imageID;
}
