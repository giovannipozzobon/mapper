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
    GetMouseState();
    
    // check the movment
    X = mouse_data.mouse_x;
    Y = mouse_data.mouse_y;        
    move();

    // check button 
    btnChanged = mouse_data.buttons ^ mBtnPrev;
    mBtnPrev = mouse_data.buttons;

    leftBtnDown = (btnChanged & mouse_data.buttons & 1) !=0;
    rigthBtnDown = (btnChanged & mouse_data.buttons & 2) !=0;
    leftBtnUp = ((btnChanged & 1) != 0) && ((mouse_data.buttons & 1) ==0);
    rigthBtnUp = ((btnChanged & 2) != 0) && ((mouse_data.buttons & 2) ==0);

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


void Mouse::MoveCursorMouse(int x,int y){

    API_PARAMETERS_ADDR[0] = x & 0xFF;                      // P0P1
    API_PARAMETERS_ADDR[1] = x >> 8;
    API_PARAMETERS_ADDR[2] = y & 0xFF;                     // P2P3
    API_PARAMETERS_ADDR[3] = y >> 8;
    *API_FUNCTION_ADDR  = API_FN_MOVE_CURSOR;
    *API_COMMAND_ADDR   = API_GROUP_MOUSE;   
   

};

void Mouse::SetCursorOnOff(uint8_t statecursor){

    API_PARAMETERS_ADDR[0] = statecursor;   
    *API_FUNCTION_ADDR  = API_FN_MOUSE_CURS_ON_OFF;
    *API_COMMAND_ADDR   = API_GROUP_MOUSE;   

};

void Mouse::GetMouseState(){
    
    *API_FUNCTION_ADDR  = API_FN_GET_MOUSE_STATE;
    *API_COMMAND_ADDR   = API_GROUP_MOUSE;  
    mouse_data.mouse_x = API_PARAMETERS_ADDR[1];
    mouse_data.mouse_x = mouse_data.mouse_x <<8;
    mouse_data.mouse_x = API_PARAMETERS_ADDR[0];

    mouse_data.mouse_y = API_PARAMETERS_ADDR[3];
    mouse_data.mouse_y = mouse_data.mouse_y <<8;
    mouse_data.mouse_y = API_PARAMETERS_ADDR[2];

    mouse_data.buttons = API_PARAMETERS_ADDR[4];

    //mouse_data->leftBtn = (API_PARAMETERS_ADDR[4] & 0x01);
    //mouse_data->rigthBtn = ((API_PARAMETERS_ADDR[4]>>1) & 0x01);

};


uint8_t Mouse::TestMousePresent(){

    *API_FUNCTION_ADDR  = API_FN_TEST_MOUSE_EXIST;
    *API_COMMAND_ADDR   = API_GROUP_MOUSE;   
    return(API_PARAMETERS_ADDR[0]);

};

uint8_t Mouse::SelectMouseCursor(uint8_t shape){

    API_PARAMETERS_ADDR[0] = shape;   
    *API_FUNCTION_ADDR  = API_FN_SEL_MOUSE_CURSOR;
    *API_COMMAND_ADDR   = API_GROUP_MOUSE;  
    return(API_PARAMETERS_ADDR[0]); 
};