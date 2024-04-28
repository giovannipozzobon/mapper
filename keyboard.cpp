#include "keyboard.hpp"


void Keyboard::SetCursorPosition(uint8_t x_pos , uint8_t y_pos)
{
  *API_FUNCTION_ADDR     = API_FN_CURSOR_POS ;
  API_PARAMETERS_ADDR[0] = x_pos             ;
  API_PARAMETERS_ADDR[1] = y_pos             ;
  *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;
}

void Keyboard::write (const unsigned char* buf, unsigned count) {
 	volatile unsigned char *cmd = (unsigned char *)0xFF00;
 	while (count--) {
 		while(*API_COMMAND_ADDR) {};   
    *API_FUNCTION_ADDR     = API_FN_WRITE_CHAR;
    API_PARAMETERS_ADDR[0] = *buf++;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;
 	}
}

void Keyboard::ClearScreen(){
    // Clear Screen
    *API_FUNCTION_ADDR     = API_FN_CLEAR_SCREEN ;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE;
    while(*API_COMMAND_ADDR) {};

} 

char Keyboard::CheckKeyboardArray(){
    // Check keyboard array
 
    *API_FUNCTION_ADDR     = API_FN_CHECK_STATUS ;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;
    return(API_PARAMETERS_ADDR[0]);

} 

// Get character from keyboard
char Keyboard::inkey() {
    while(*API_COMMAND_ADDR) {}  
    *API_FUNCTION_ADDR     = API_FN_READ_CHAR ;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;                 // Group 2, Command 1
    while(*API_COMMAND_ADDR) {}
    return(API_PARAMETERS_ADDR[0]);            // Return parameter
}


char Keyboard::cgetc() {
  char ch=0;
  while(ch==0) {
    ch=inkey();
  }
  return ch;
}


// Position cursor (API Group 2, Function 7)
void Keyboard::gotoxy(uint8_t sx, uint8_t sy)
{
  API_PARAMETERS_ADDR[0] = sx;
  API_PARAMETERS_ADDR[1] = sy;
  *API_FUNCTION_ADDR  = API_FN_CURSOR_POS  ;
  *API_COMMAND_ADDR   = API_GROUP_CONSOLE ;     
}


// Put a character
void Keyboard::cputc(char ch) {

    while(*API_COMMAND_ADDR) {}  
    API_PARAMETERS_ADDR[0] = ch;
    *API_FUNCTION_ADDR  = API_FN_WRITE_CHAR_CURS  ;
    *API_COMMAND_ADDR   = API_GROUP_CONSOLE ;   
}

// Put a character at screen coord
void Keyboard::cputcxy(int sx, int sy, char ch) {
    gotoxy(sx,sy);
    cputc(ch);
}

// Clear screen
void Keyboard::clrscr() {
    cputc(12);
    gotoxy(0,0);
}

void Keyboard::ClearKeyboardArray(){
    // Clear keyboard array
    while(CheckKeyboardArray()==0xff) {
      cgetc();
    }

} 
 
