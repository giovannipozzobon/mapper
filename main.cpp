#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "mouse.hpp"
#include "gui.hpp"
#include "util.hpp"
#include "console.hpp"
#include "file.hpp"
#include <stdlib.h>


char buffer [sizeof(int)*40+1];
const unsigned char nameFileGfx[] = {12, 'g', 'r', 'a', 'p', 'h', 'i', 'c', 's', '.', 'g', 'f', 'x'};

int main(){
    Mouse mouse;
    Gui gui;
    Util util;
    Console keyboard;
    File file;
   

    int k; 
    char key='0';

    file.LoadGrafix(nameFileGfx);
    gui.ReadGfxValue();

    mouse.CursorOnOff(mouse.CURSORON);
    mouse.ChoiseMouseCursor(mouse.SHAPE_ARROW);

    gui.DrawScreen();
    gui.ReadGfxValue(); //used only to debud to see the correct number of tiles

    while (1)
    {

        mouse.Read();

        key = keyboard.inkey();
        //if (key == keyboard.KEY_CURS_UP) key='U';
        if (key != 0) gui.ActionKey(key);

        //sprintf(buffer," %d %d %d %d %c",mouse.X, mouse.Y, mouse.leftBtnUp, mouse.rigthBtnUp, key);
        //sprintf(buffer," %i ", array);
        //buffer[0]=40;
        //gui.DrawBoardText(buffer);
    
        util.nop_delay(5000);
    }
     return 0;

};
