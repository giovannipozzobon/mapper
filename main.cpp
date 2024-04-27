#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "mouse.hpp"
#include "gui.hpp"




char buffer [sizeof(int)*40+1];
//mouse_state mouseState;

extern char tabname[TAB_COUNT][7];
extern char coordinatesMouse[TAB_COUNT][4];

int main(){
    Mouse mouse;
    Gui gui;

    mouse.CursorOnOff(mouse.CURSORON);
    mouse.ChoiseMouseCursor(mouse.SHAPE_ARROW);


    gui.DrawScreen();


    while (1)
    {

    mouse.Read();
    sprintf(buffer," X:%d  Y:%d B1:%d B2:%d",mouse.X, mouse.Y, mouse.leftBtnUp, mouse.rigthBtnUp);
    buffer[0]=40;
    Gfx_DrawString(1,80,buffer);
    sprintf(buffer," mouse change: %d",mouse.btnChanged);
    Gfx_DrawString(40,40,buffer); 
    nop_delay(7000);

      /*   
            //CheckMouse();

            nop_delay(5000);
            mouseState=GetMouseState();
            sprintf(buffer,"mouse position X: %d  Y: %d Btn1: %d Btn2: %d",mouseState.mouse_x, mouseState.mouse_y, mouseState.btn1, mouseState.btn2);
            puts(buffer);


    // move the mouse cursor
  
        for (int i = 0; i < 200; i++)
        {
            MoveCursorMouse(i,i);
            nop_delay(5000);
            mouseState=GetMouseState();
            sprintf(buffer,"mouse position X: %d  Y: %d Btn1: %d Btn2: %d",mouseState.mouse_x, mouseState.mouse_y, mouseState.btn1, mouseState.btn2);
            puts(buffer);

        }
    */        

    }
     return 0;

};
