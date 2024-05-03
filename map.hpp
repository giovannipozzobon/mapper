#ifndef MAP_HPP
#define MAP_HPP

#include <stdio.h>
#include <cstdint>

#define ERROR   -1
#define OK      0


class Map{

private:

   typedef struct cursor_grid
    {
        uint8_t cursor_grid_x;
        uint8_t cursor_grid_y;
        int cursor_map_x;
        int cursor_map_y;             
        uint8_t imageID; 
        
    } cursor_grid;

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
    uint8_t SetRowColNrItems(uint8_t row, uint8_t col);

    void SetCursor(uint8_t cursor_grid_x, uint8_t cursor_grid_y, int cursor_map_x, int cursor_map_y, uint8_t imageID);

    uint8_t ReadCursorImageID();
    int     ReadCursorMapX();
    int     ReadCursorMapY();
    void    UpdateCursorFromGrid(uint8_t grid_x, uint8_t grid_y, int map_x, int map_y);
    void    SaveCursorToGrid();

};

#endif //MAP_HPP