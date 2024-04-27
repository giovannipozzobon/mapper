#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <stdio.h>
#include "api.hpp"


class Mouse {
private:
    uint8_t mBtnPrev;
    int lastX;
    int lastY;
    mouse_state mousestate;
    const uint8_t DBL_CLICK_LEN = 16;
    
 
    void move();

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