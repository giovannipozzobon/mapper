#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "gui.h"



char buffer [sizeof(int)*40+1];


int main(){
    uint8_t i, mouseIsPresent=0;
    mouse_state mouseState;
    int command;

    // Is mouse present? 
    //mouseIsPresent= TestMousePresent();

    //print on the screen
    clrscr();
    sprintf(buffer,"mouse not present %d",mouseIsPresent);
    PrintOnScreen(10, 10,buffer);
    
    // Mouse Cursor ON
    SetCursorOnOff(1);

    // Set mouse Cursor shape
    SelectMouseCursor(0);

    DrawScreen();

    while (1)
    {
       command = checkMouseAndKey();
 

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
