#include "map.hpp"


uint8_t Map::FillMem(uint8_t value){
    if ((grid_addr_ram == 0) || (max_len_map ==0)) return ERROR;

    for(int i=0; i<nr_item; i++){
       grid_addr_ram[i]= value;

    }    
    return OK;
}


void Map::AddItem(uint8_t imageID, uint8_t pos_x, uint8_t pos_y){

}


void Map::DelItem(uint8_t imageID, uint8_t pos_x, uint8_t pos_y){

}


void Map::SetMapInitialAddress(int address){
    // the first 3 bytes are header of tilemap 
    
    grid_addr_init = (char *) address;
    grid_addr_ram = grid_addr_init+3;
}

void Map::SetMapMaxLen(int len){
    max_len_map = len;
    max_addr_ram = grid_addr_ram + len;
}

uint8_t Map::SetRowColNrItems(uint8_t row, uint8_t col, uint8_t fill){

    NrRow = row;
    NrCol = col;
    nr_item = (int) row * (int) col;

    if (nr_item > max_len_map) 
        return ERROR; 
    else{ 
        //Fill the memory with map default value (empty)
        grid_addr_init[0] = 1;
        grid_addr_init[1] = row;
        grid_addr_init[2] = col;
        if (fill==1) FillMem(0xff);
        return OK;
    }

}

 void Map::SetCursor(uint8_t cursor_grid_x, uint8_t cursor_grid_y, uint8_t cursor_offset_x, uint8_t cursor_offset_y, int cursor_map_x, int cursor_map_y, uint8_t imageID)
{
    cursor.cursor_grid_x = cursor_grid_x;
    cursor.cursor_grid_y = cursor_grid_y;
    cursor.cursor_offset_x = cursor_offset_x;
    cursor.cursor_offset_y = cursor_offset_y;
    cursor.cursor_map_x = cursor_map_x;
    cursor.cursor_map_y = cursor_map_y;
    cursor.imageID = imageID;

 }

uint8_t Map::ReadCursorImageID(){return cursor.imageID;}

int Map::ReadCursorMapX(){ return cursor.cursor_map_x;}

int Map::ReadCursorMapY(){ return cursor.cursor_map_y;}

void Map::UpdateCursorFromGrid(uint8_t grid_x, uint8_t grid_y, int map_x, int map_y, int pos_with_offset){
    //take the imageId from memory
    cursor.imageID=grid_addr_ram[pos_with_offset];
    cursor.cursor_grid_x = grid_x;
    cursor.cursor_grid_y = grid_y;
    cursor.cursor_map_x=map_x;
    cursor.cursor_map_y=map_y;

}

void Map::SaveCursorToGrid(){
    grid_addr_ram[cursor.cursor_grid_x+cursor.cursor_offset_x+(cursor.cursor_grid_y+cursor.cursor_offset_y)*NrRow] = cursor.imageID;
}


uint8_t Map::LoadMap(char * namefile){
uint8_t error=0;

    error=file.LoadFile((int) grid_addr_init, namefile);
    if (error == 0){
        SetRowColNrItems(grid_addr_init[1],  grid_addr_init[2], 0);
        return OK;
    } else return ERROR;
}

uint8_t Map::SaveMap(char * namefile){
uint8_t error=0;

    error=file.SaveFile((int) grid_addr_init, nr_item+3, namefile);
    if (error == 0) return OK;
    return ERROR;
}

int Map::GetItems(){ return nr_item;}
int Map::GetRows(){return NrRow;}
int Map::GetCols(){return NrCol;}
int Map::GetMaxMemory() {return max_len_map;}
int Map::GetUsedMemory() {return nr_item;}
int Map::GetMapAddress(){ return (int) grid_addr_init;}

int Map::GetItemFromGrid(int index){
    return grid_addr_ram[index];
}

void Map::ResetMap(){
    FillMem(0xff);
}



int Map::FillMap(uint8_t value){

    if ((grid_addr_ram == 0) || (max_len_map ==0)) return ERROR;

    for(int i=0; i<nr_item; i++){
       
       if (grid_addr_ram[i] == 0Xff) grid_addr_ram[i]= value;

    }    
    return OK;

}
