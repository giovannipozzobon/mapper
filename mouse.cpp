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
    api.GetMouseState();
    
    // check the movment
    X = api.mouse_data.mouse_x;
    Y = api.mouse_data.mouse_y;        
    move();

    // check button 
    btnChanged = api.mouse_data.buttons ^ mBtnPrev;
    mBtnPrev = api.mouse_data.buttons;

    leftBtnDown = (btnChanged & api.mouse_data.buttons & 1) !=0;
    rigthBtnDown = (btnChanged & api.mouse_data.buttons & 2) !=0;
    leftBtnUp = ((btnChanged & 1) != 0) && ((api.mouse_data.buttons & 1) ==0);
    rigthBtnUp = ((btnChanged & 2) != 0) && ((api.mouse_data.buttons & 2) ==0);

    if (leftBtnUp) {  
        dblClick = DBL_CLICK_LEN;
    };

}

bool Mouse::IsPresent(){
    return api.TestMousePresent();
};

// Mouse Cursor ON
void Mouse::CursorOnOff(uint8_t state){
    api.SetCursorOnOff(state);
};

// Set mouse Cursor shape
void Mouse::ChoiseMouseCursor(uint8_t shape){
    api.SelectMouseCursor(shape);
};

// Set mouse Cursor shape
void Mouse::MoveMouseCursor(int x, int y){
    api.MoveCursorMouse(x,y);
};

