#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <stdio.h>
#include <cstdint>

class Graphic {

private:

    volatile uint8_t* API_COMMAND_ADDR    = (uint8_t*)0xFF00 ; // function group address
    volatile uint8_t* API_FUNCTION_ADDR   = (uint8_t*)0xFF01 ; // function address
    volatile uint8_t* API_PARAMETERS_ADDR = (uint8_t*)0xFF04 ; // function parameters base address (8 bytes)

    // Graphics functions (Group 5)
    uint8_t API_GROUP_GRAPHICS      = (uint8_t )0x05 ; // API function group Graphics
    uint8_t API_SET_DEFAULTS        = (uint8_t )0x01 ; // API function ID for Color
    uint8_t API_DRAW_LINE           = (uint8_t )0x02 ; // API function ID Draw Line 
    uint8_t API_DRAW_RECTANGLE      = (uint8_t )0x03 ; // API function ID Draw Rectangle 
    uint8_t API_DRAW_ELLIPSE        = (uint8_t )0x04 ; // API function ID Draw Ellipse 
    uint8_t API_DRAW_PIXEL          = (uint8_t )0x05 ; // API function ID Draw Pixel 
    uint8_t API_FN_DRAW_STRING     = (uint8_t )0x06 ; // API function ID Write String
    uint8_t API_FN_DRAW_IMAGE       = (uint8_t )0x07 ; // API function ID Write Image
    uint8_t API_FN_DRAW_TILEMAP     = (uint8_t )0x08 ; // API function ID Draw TileMap
    uint8_t API_SET_PALETTE         = (uint8_t )0x20 ; // API function ID for set palette
    uint8_t API_RESET_PALETTE       = (uint8_t )0x22 ; // API function ID for reset palette
    uint8_t API_SET_CUR_TILEMAP     = (uint8_t )0x23 ; // API function ID Set Current Tilemap
    uint8_t API_SET_COLOR           = (uint8_t )0x40 ; // API function ID Set Color
    uint8_t API_SET_SOLID_FLAG      = (uint8_t )0x41 ; // API function ID Set Solid Flag
    uint8_t API_SET_DRAW_SIZE       = (uint8_t )0x42 ; // API function ID Set Draw Size
    uint8_t API_SET_FLIP_BIT        = (uint8_t )0x43 ; // API function ID Set Flip Bit


public:
    void Gfx_DrawString(int x_pos , int y_pos, char * str);
    
    void DrawLine(int x1,int y1,int x2,int y2);

    void DrawRectangle(int x1,int y1,int x2,int y2);

    void DrawImage(int x,int y, uint8_t imageID);

    void ResetPalette();

    void SetDrawDefaults(uint8_t _and, uint8_t _xor, uint8_t solid, uint8_t dimension, uint8_t flip);

    void SetCurrentTileMap(unsigned char * addr, int x, int y);

    void DrawTileMap(int x1, int y1, int x2, int y2);

    void SetPalette(uint8_t color, uint8_t r, uint8_t g, uint8_t b);

    void SetColor(uint8_t color);

    void SetSolidFlag(uint8_t flag);

    void DrawPixel(int x,int y);

};

#endif //GRAPHIC_HPP