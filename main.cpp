#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "mouse.hpp"
#include "gui.hpp"
#include "util.hpp"
#include "console.hpp"
#include "file.hpp"


char buffer [sizeof(int)*40+1];
unsigned char nameFileGfx[] = {12, 'g', 'r', 'a', 'p', 'h', 'i', 'c', 's', '.', 'g', 'f', 'x'};

int main(){
    Mouse mouse;
    Gui gui;
    Util util;
    Console console;
    File file;


    int k; 
    //char key='0';
    uint8_t current_tab;
    uint8_t kstatus;
    key_with_Modifier key;

    //load Grafic file
    //file.LoadGrafix(nameFileGfx);
    //gui.ReadGfxValue();

    //Initialize mouse
    mouse.CursorOnOff(mouse.CURSORON);
    mouse.ChoiseMouseCursor(mouse.SHAPE_ARROW);

    //Initialize gui
    gui.DrawScreen();
    //gui.ReadGfxValue(); //used only to debud to see the correct number of tiles

    while (1)
    {

        mouse.Read();

        //key = console.inkey();
        //if (key == keyboard.KEY_CURS_UP) key='U';
        //if (key != 0) gui.ActionKey(key);
        //key='a';
        //kstatus =console.KeyModifierStatus(key);
        //sprintf(buffer," %d %d %d %d",mouse.X, mouse.Y, mouse.leftBtnDown, mouse.leftBtnDown);
        //sprintf(buffer," Key: %i  Status: %i", key, kstatus);

        key = console.get_char_modifier();
        if (key.chr != 0) gui.ActionKey(key);

        mouse.Read();
        key = gui.ActionMouse(mouse.X,mouse.Y,mouse.leftBtnDown,mouse.rigthBtnDown);
        
        if (key.chr != 0) gui.ActionKey(key);
        //sprintf(buffer," Key: %i Mod %i btn1: %d", key.chr,key.modifier, mouse.leftBtnDown);
        //buffer[0]=40;
        
        //gui.DrawBoardText(buffer);
    /*
        console.gotoxy(10,20);
        puts(buffer);
    */
        util.nop_delay(5000);
    
    }
     return 0;

};
