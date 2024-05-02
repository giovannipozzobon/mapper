#include "map.hpp"


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
    if (nr_item > max_len_map) return ERROR; else return OK;

}

