#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "mouse.hpp"
#include "gui.hpp"
#include "util.hpp"
#include "keyboard.hpp"
#include "api.hpp"




char buffer [sizeof(int)*40+1];
//mouse_state mouseState;

//extern char tabname[TAB_COUNT][7];
//extern char coordinatesMouse[TAB_COUNT][4];

int main(){
    Mouse mouse;
    Gui gui;
    Util util;
    Keyboard keyboard;

    int k; 
    char key='0';

    mouse.CursorOnOff(mouse.CURSORON);
    mouse.ChoiseMouseCursor(mouse.SHAPE_ARROW);


    gui.DrawScreen();


    while (1)
    {

        mouse.Read();

        key = keyboard.inkey();
        if (key == keyboard.KEY_CURS_UP) key='U';

        sprintf(buffer," %d %d %d %d %c",mouse.X, mouse.Y, mouse.leftBtnUp, mouse.rigthBtnUp, key);
        buffer[0]=40;
        gui.DrawBoardText(buffer);
    
        util.nop_delay(5000);
    }
     return 0;

};
