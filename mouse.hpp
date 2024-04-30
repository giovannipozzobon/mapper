#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <stdio.h>
#include <cstdint>


class Mouse {
private:
    
    volatile uint8_t* API_COMMAND_ADDR    = (uint8_t*)0xFF00 ; // function group address
    volatile uint8_t* API_FUNCTION_ADDR   = (uint8_t*)0xFF01 ; // function address
    volatile uint8_t* API_PARAMETERS_ADDR = (uint8_t*)0xFF04 ; // function parameters base address (8 bytes)

    // Mouse Functions (Group 11)
    uint8_t API_GROUP_MOUSE         = (uint8_t )0x0b ; // API function group Mouse
    uint8_t API_FN_MOVE_CURSOR      = (uint8_t )0x01 ; // API Move cursor mouse
    uint8_t API_FN_MOUSE_CURS_ON_OFF= (uint8_t )0x02 ; // API Move cursor mouse
    uint8_t API_FN_GET_MOUSE_STATE  = (uint8_t )0x03 ; // API Get mouse state
    uint8_t API_FN_TEST_MOUSE_EXIST = (uint8_t )0x04 ; // API Test mouse present
    uint8_t API_FN_SEL_MOUSE_CURSOR = (uint8_t )0x05 ; // API Select mouse cursor

    typedef struct mouse_state
    {
        unsigned int mouse_x;
        unsigned int mouse_y;
        uint8_t buttons; 
        
    } mouse_state;

    mouse_state mouse_data;
    uint8_t mBtnPrev;
    int lastX;
    int lastY;

    const uint8_t DBL_CLICK_LEN = 16;
    
 
    void move();
    
    void MoveCursorMouse(int x,int y);

    void SetCursorOnOff(uint8_t statecursor);

    void GetMouseState();

    uint8_t TestMousePresent();

    uint8_t SelectMouseCursor(uint8_t shape);

public:
    const uint8_t CURSORON = 1;
    const uint8_t CURSOROFF = 0;

    const uint8_t SHAPE_ARROW = 0;

    int X;
    int Y;
    uint8_t mouseMoved;
    uint8_t btnChanged; //Is buttons changed?
    uint8_t dblClick;
    uint8_t leftBtnUp;
    uint8_t leftBtnDown;
    uint8_t rigthBtnUp;
    uint8_t rigthBtnDown;
    
    Mouse();

    void Read();

    bool IsPresent();

    void CursorOnOff(uint8_t state);

    void ChoiseMouseCursor(uint8_t shape);

    void MoveMouseCursor(int x, int y);
};
#endif // MOUSE_HPP