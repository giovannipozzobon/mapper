#include "mouse.hpp"


Mouse::Mouse() {};

void Mouse::move() {
    if (X != lastX || Y != lastY) {
        lastX = X;
        lastY = Y;
        mouseMoved = true;
    }
};

void Mouse::Read() {
    
    if (dblClick>0) dblClick--;

    //read the mouse state from api
    mousestate = GetMouseState();
    
    // check the movment
    X = mousestate.mouse_x;
    Y = mousestate.mouse_y;        
    move();

    // check button 
    btnChanged = mousestate.buttons ^ mBtnPrev;
    mBtnPrev = mousestate.buttons;

    leftBtnDown = (btnChanged & mousestate.buttons & 1) !=0;
    rigthBtnDown = (btnChanged & mousestate.buttons & 2) !=0;
    leftBtnUp = ((btnChanged & 1) != 0) && ((mousestate.buttons & 1) ==0);
    rigthBtnUp = ((btnChanged & 2) != 0) && ((mousestate.buttons & 2) ==0);

    if (leftBtnUp) {  
        dblClick = DBL_CLICK_LEN;
    };

}

bool Mouse::IsPresent(){
    return TestMousePresent();
};

// Mouse Cursor ON
void Mouse::CursorOnOff(uint8_t state){
    SetCursorOnOff(state);
};

// Set mouse Cursor shape
void Mouse::ChoiseMouseCursor(uint8_t shape){
    SelectMouseCursor(shape);
};

// Set mouse Cursor shape
void Mouse::MoveMouseCursor(int x, int y){
    MoveCursorMouse(x,y);
};

