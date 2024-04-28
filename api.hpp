#ifndef API_HPP
#define API_HPP

#include <stdio.h>

class Api {

private:

    typedef struct mouse_state
    {
        unsigned int mouse_x;
        unsigned int mouse_y;
        uint8_t buttons; 
        
    } mouse_state;


    /* Neo6502 Kernel API control addresses */

    volatile uint8_t* API_COMMAND_ADDR    = (uint8_t*)0xFF00 ; // function group address
    volatile uint8_t* API_FUNCTION_ADDR   = (uint8_t*)0xFF01 ; // function address
    volatile uint8_t* API_PARAMETERS_ADDR = (uint8_t*)0xFF04 ; // function parameters base address (8 bytes)


    /* Neo6502 Kernel API control codes (see documents/release/api.pdf) */

    // Console functions (Group 1)
    uint8_t API_GROUP_GENERAL       = (uint8_t )0x01 ; // API function group General
    uint8_t API_FN_TIMER            = (uint8_t )0x01 ; // API function Timer
    uint8_t API_FN_BASIC            = (uint8_t )0x03 ; // API function Basic

    // Console functions (Group 2)
    uint8_t API_GROUP_CONSOLE       = (uint8_t )0x02 ; // API function group Concole
    uint8_t API_FN_WRITE_CHAR       = (uint8_t )0x00 ; // API function Write Char
    uint8_t API_FN_READ_CHAR        = (uint8_t )0x01 ; // API function Read Char
    uint8_t API_FN_CHECK_STATUS     = (uint8_t )0x02 ; // API function Check Status
    uint8_t API_FN_WRITE_CHAR_CURS  = (uint8_t )0x06 ; // API function Write Char Curs
    uint8_t API_FN_CURSOR_POS       = (uint8_t )0x07 ; // API function Cursor Pos
    uint8_t API_FN_CLEAR_SCREEN     = (uint8_t )0x0C ; // API function Clear Screen

    // File functions (Group 3)
    uint8_t API_GROUP_FILE          = (uint8_t )0x03 ; // API function group File
    uint8_t API_FN_CAT_DIR          = (uint8_t )0x01 ; // API function ID show the files in the directory
    uint8_t API_FN_LOAD_FILE        = (uint8_t )0x02 ; // API function ID Load from file to memory
    uint8_t API_FN_STORE_FILE       = (uint8_t )0x03 ; // API function ID Save memory to file 
    uint8_t API_FN_OPEN_FILE        = (uint8_t )0x04 ; // API function ID Open file 
    uint8_t API_FN_CLOSE_FILE       = (uint8_t )0x05 ; // API function ID Close file 
    uint8_t API_FN_READ_FILE        = (uint8_t )0x08 ; // API function ID Read file 
    uint8_t API_FN_WRITE_FILE       = (uint8_t )0x09 ; // API function ID Write file 
    
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

    //SPRITE functions (Group 6)
    uint8_t API_GROUP_SPRITE        = (uint8_t )0x06 ; // API function group Sprite
    uint8_t API_FN_RESET_SPRITE     = (uint8_t )0x01 ; // API function ID
    uint8_t API_FN_UPDATE_SPRITE    = (uint8_t )0x02 ; // API function ID
    uint8_t API_FN_HIDE_SPRITE      = (uint8_t )0x03 ; // API function ID
    uint8_t API_FN_DISTANCE_SPRITE  = (uint8_t )0x04 ; // API function ID

    //Controller functions (Group 7)
    uint8_t API_GROUP_CONTROLLER    = (uint8_t )0x07 ; // API function group Controller
    uint8_t API_FN_READ_CONTROLLER  = (uint8_t )0x01 ; // API function ID The keys are "WASDOP" O e P are fires A e B

    // Sound functions (Group 8)
    uint8_t API_GROUP_SOUND         = (uint8_t )0x08 ; // API function group Sound
    uint8_t API_FN_SOUND_CH_RESET   = (uint8_t )0x02 ; // API function parameter ID
    uint8_t API_FN_PLAY_SOUND       = (uint8_t )0x05 ; // API function ID

    // UExt I/O Functions (Group 10)
    uint8_t API_GROUP_UEXT_IO       = (uint8_t )0x0A ; // API function group UExt
    uint8_t API_FN_SET_SPEED_PROT   = (uint8_t )0x0F ; // API Set UART Speed and Protocol
    uint8_t API_FN_WRITE_UART       = (uint8_t )0x10 ; // API Write byte to UART

    // Mouse Functions (Group 11)
    uint8_t API_GROUP_MOUSE         = (uint8_t )0x0b ; // API function group Mouse
    uint8_t API_FN_MOVE_CURSOR      = (uint8_t )0x01 ; // API Move cursor mouse
    uint8_t API_FN_MOUSE_CURS_ON_OFF= (uint8_t )0x02 ; // API Move cursor mouse
    uint8_t API_FN_GET_MOUSE_STATE  = (uint8_t )0x03 ; // API Get mouse state
    uint8_t API_FN_TEST_MOUSE_EXIST = (uint8_t )0x04 ; // API Test mouse present
    uint8_t API_FN_SEL_MOUSE_CURSOR = (uint8_t )0x05 ; // API Select mouse cursor


public:

    mouse_state mouse_data;

    void ResetChannelSound(uint8_t nr_channel);

    void PlaySoundChannel(uint8_t nr_channel, uint8_t sfx);

    void Gfx_DrawString(int x_pos , int y_pos, char * str);
    
    void DisplayDirectory();

    void OpenFile(uint8_t channel, const unsigned char * fileName, uint8_t mode);

    void CloseFile(uint8_t channel);

    uint8_t WriteFile(uint8_t channel, int memory, int nrbyte);

    uint8_t LoadFile( int memory, const unsigned char * fileName);

    uint8_t SaveFile( int memory, int nrbyte , const unsigned char * fileName);

    void DrawLine(int x1,int y1,int x2,int y2);

    void DrawRectangle(int x1,int y1,int x2,int y2);

    void DrawImage(int x,int y, uint8_t imageID);

    uint8_t LoadGrafix(const unsigned char * file);

    void DrawSprite(uint8_t id, int x, int y, uint8_t image);

    void MoveSprite(uint8_t id, int x, int y);

    uint8_t DistanceSprites(uint8_t id_sprite1, uint8_t id_sprite2, uint8_t distance) ;

    void HideSprite(uint8_t id);

    void ResetSprite();

    uint8_t CheckJoypad();

    int readTimer();

    void waitXcycleclock(int cicli);

    void ResetPalette();

    void SetDrawDefaults(uint8_t _and, uint8_t _xor, uint8_t solid, uint8_t dimension, uint8_t flip);

    void SetCurrentTileMap(unsigned char * addr, int x, int y);

    void DrawTileMap(int x1, int y1, int x2, int y2);

    unsigned int nop_delay(unsigned int delay) ;

    void SetPalette(uint8_t color, uint8_t r, uint8_t g, uint8_t b);

    void SetColor(uint8_t color);

    void SetSolidFlag(uint8_t flag);

    void DrawPixel(int x,int y);

    void ClearScreen();

    char CheckKeyboardArray();

    void ReturnToBasic();


    // Get character from keyboard
    int inkey();

    int cgetc();


    // Position cursor (API Group 2, Function 7)
    void gotoxy(uint8_t sx, uint8_t sy);

    // write to conole a string with lengh count
    void write (const unsigned char* buf, unsigned count);

    // Put a character
    void cputc(char ch);

    // Put a character at screen coord
    void cputcxy(int sx, int sy, char ch);

    // Clear screen
    void clrscr();

    void ClearKeyboardArray();

    void SetSpeed_ProtocolUART(uint32_t baudrate);

    void WritelUART(uint8_t chr);

    void WriteStringTolUART(char * ptr_str);

    void MoveCursorMouse(int x,int y);

    void SetCursorOnOff(uint8_t statecursor);

    void GetMouseState();

    uint8_t TestMousePresent();

    uint8_t SelectMouseCursor(uint8_t shape);

};

#endif //API_HPP