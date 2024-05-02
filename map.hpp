#ifndef MAP_HPP
#define MAP_HPP

#include <stdio.h>
#include <cstdint>

#define ERROR   -1
#define OK      0

class Map{

private:
    char * grid_addr_ram;
    int max_len_map;
    char * max_addr_ram;
    int nr_item;
    uint8_t NrRow;
    uint8_t NrCol;

public:
    uint8_t LoadMap(unsigned char * namefile);
    uint8_t SaveMap(unsigned char * namefile);
    
    void AddItem(uint8_t imageID, uint8_t pos_x, uint8_t pos_y);
    void DelItem(uint8_t imageID, uint8_t pos_x, uint8_t pos_y);
    
    void SetMapInitialAddress(int address);
    void SetMapMaxLen(int len);
    uint8_t SetRowColNrItems(uint8_t row, uint8_t col);

};

#endif //MAP_HPP