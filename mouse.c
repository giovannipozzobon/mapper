
#include <stdio.h>
#include "mouse.h"
#include "const.h"

extern char tabname[TAB_COUNT][7];
extern char coordinatesMouse[TAB_COUNT][4];

char  strTextMouse [sizeof(int)*40+1];

int checkMouseAndKey(mouse_state * mouseState){
    
    SetSolidFlag(1);

    GetMouseState(mouseState);
    sprintf(strTextMouse," X:%d  Y:%d B1:%d B2:%d",mouseState->mouse_x, mouseState->mouse_y, mouseState->leftBtn, mouseState->rigthBtn);
    strTextMouse[0]=40;
    //DrawBoardText(strText);
     Gfx_DrawString(1,80,strTextMouse);

    if (mouseState->leftBtn!=0) //checkArea(); 
    {
        for (int i = 0; i < TAB_COUNT; i++)
        {
            if (mouseState->mouse_x > coordinatesMouse[i][0] && mouseState->mouse_x < coordinatesMouse[i][2] &&
                mouseState->mouse_y > coordinatesMouse[i][1] && mouseState->mouse_y < coordinatesMouse[i][3]) {
                    sprintf(strTextMouse," TAB %d",i+1);
                    strTextMouse[0]=7;
                    Gfx_DrawString(40,40,strTextMouse);
                    break;
                }
        }
    }
    return 1;
}

/*
 if mouse.dblclick>0 then mouse.dblclick:=mouse.dblclick-1;

    NeoReadMouse;
    mouse.but := neoMouseButtons;
    mouse.wheel := neoMouseWheel;
    mouse.x:=neoMouseX;
    mouse.y:=neoMouseY;

    // wheel processing
    wheeldelta := mouse.wheel - mwheelprev;
    mwheelprev := mouse.wheel;
    mouse.wheel := Sgn(wheeldelta);

    // button processing
    mouse.butchange := mouse.but xor mbutprev;
    mbutprev := mouse.but;

    // position processing
    if (pmx<>mouse.x) or (pmy<>mouse.y) then MouseMoved;
    pmx:=mouse.x;
    pmy:=mouse.y;

    mouse.LDown := mouse.butchange and mouse.but and 1 <> 0;
    mouse.RDown := mouse.butchange and mouse.but and 2 <> 0;
    mouse.MDown := mouse.butchange and mouse.but and 4 <> 0;
    mouse.LUp := (mouse.butchange and 1 <> 0) and (mouse.but and 1 = 0);
    mouse.RUp := (mouse.butchange and 2 <> 0) and (mouse.but and 2 = 0);
    mouse.MUp := (mouse.butchange and 4 <> 0) and (mouse.but and 4 = 0);

    if mouse.LUp then begin  
        mouse.dblclick := DBL_CLICK_LEN;
    end;

    mouse.areaId := $ff;

    if (mouse.butchange or mouse.but or mouse.wheel) = 0 then exit;
    cursorMode := cursorMode or CUR_MOUSE;
    mouse.areaId := ScanForArea(currentTab,mouse.x,mouse.y);

*/