#ifndef MAP_HPP
#define MAP_HPP

#include <stdio.h>
#include <cstdint>
#include "file.hpp"

#define ERROR   -1
#define OK      0


class Map{

private:

   typedef struct cursor_grid
    {
        uint8_t cursor_grid_x;
        uint8_t cursor_grid_y;
        uint8_t cursor_offset_x;
        uint8_t cursor_offset_y;
        int cursor_map_x;
        int cursor_map_y;             
        uint8_t imageID; 
        
    } cursor_grid;

    File file;

    char * grid_addr_init;
    char * grid_addr_ram;
    int max_len_map;
    char * max_addr_ram;
    int nr_item;
    uint8_t NrRow;
    uint8_t NrCol;

    cursor_grid cursor;

    uint8_t FillMem(uint8_t value);

public:

    uint8_t LoadMap(unsigned char * namefile);
    uint8_t SaveMap(unsigned char * namefile);
    
    void AddItem(uint8_t imageID, uint8_t pos_x, uint8_t pos_y);
    void DelItem(uint8_t imageID, uint8_t pos_x, uint8_t pos_y);
    
    void SetMapInitialAddress(int address);
    void SetMapMaxLen(int len);
    uint8_t SetRowColNrItems(uint8_t row, uint8_t col, uint8_t fill);

    void SetCursor(uint8_t cursor_grid_x, uint8_t cursor_grid_y, uint8_t cursor_offset_x, uint8_t cursor_offset_y, int cursor_map_x, int cursor_map_y, uint8_t imageID);

    uint8_t ReadCursorImageID();
    int ReadCursorMapX();
    int ReadCursorMapY();
    void UpdateCursorFromGrid(uint8_t grid_x, uint8_t grid_y, int map_x, int map_y, int pos_with_offset);
    void SaveCursorToGrid();
    int GetMapAddress();
    int GetItems();
    int GetRows();
    int GetCols();
    int GetItemFromGrid(int index);
    void ResetMap();
    int FillMap(uint8_t value);
   

};

#endif //MAP_HPP