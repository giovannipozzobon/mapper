#include "console.hpp"


void Console::SetCursorPosition(uint8_t x_pos , uint8_t y_pos)
{
  *API_FUNCTION_ADDR     = API_FN_CURSOR_POS ;
  API_PARAMETERS_ADDR[0] = x_pos             ;
  API_PARAMETERS_ADDR[1] = y_pos             ;
  *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;
}

void Console::write (const unsigned char* buf, unsigned count) {
 	volatile unsigned char *cmd = (unsigned char *)0xFF00;
 	while (count--) {
 		while(*API_COMMAND_ADDR) {};   
    *API_FUNCTION_ADDR     = API_FN_WRITE_CHAR;
    API_PARAMETERS_ADDR[0] = *buf++;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;
 	}
}

void Console::ClearScreen(){
    // Clear Screen
    *API_FUNCTION_ADDR     = API_FN_CLEAR_SCREEN ;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE;
    while(*API_COMMAND_ADDR) {};

} 

char Console::CheckKeyboardArray(){
    // Check Console array
 
    *API_FUNCTION_ADDR     = API_FN_CHECK_STATUS ;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;
    return(API_PARAMETERS_ADDR[0]);

} 

// Get character from Console
char Console::inkey() {
    while(*API_COMMAND_ADDR) {}  
    *API_FUNCTION_ADDR     = API_FN_READ_CHAR ;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;                 // Group 2, Command 1
    while(*API_COMMAND_ADDR) {}
    return(API_PARAMETERS_ADDR[0]);            // Return parameter
}

// Get character from Console
void Console::ReadLine(int line_read) {

  	API_PARAMETERS_ADDR[0] = line_read & 0xFF;        
  	API_PARAMETERS_ADDR[1] = line_read  >> 8;

    while(*API_COMMAND_ADDR) {}  
    *API_FUNCTION_ADDR     = API_FN_READ_LINE;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE;                 
    while(*API_COMMAND_ADDR) {}

}


char Console::cgetc() {
  char ch=0;
  while(ch==0) {
    ch=inkey();
  }
  return ch;
}


// Position cursor (API Group 2, Function 7)
void Console::gotoxy(uint8_t sx, uint8_t sy)
{
  API_PARAMETERS_ADDR[0] = sx;
  API_PARAMETERS_ADDR[1] = sy;
  *API_FUNCTION_ADDR  = API_FN_CURSOR_POS  ;
  *API_COMMAND_ADDR   = API_GROUP_CONSOLE ;     
}


// Put a character
void Console::cputc(char ch) {

    while(*API_COMMAND_ADDR) {}  
    API_PARAMETERS_ADDR[0] = ch;
    *API_FUNCTION_ADDR  = API_FN_WRITE_CHAR_CURS  ;
    *API_COMMAND_ADDR   = API_GROUP_CONSOLE ;   
}

// Put a character at screen coord
void Console::cputcxy(int sx, int sy, char ch) {
    gotoxy(sx,sy);
    cputc(ch);
}

// Clear screen
void Console::clrscr() {
    cputc(12);
    gotoxy(0,0);
}

void Console::ClearKeyboardArray(){
    // Clear Console array
  while(CheckKeyboardArray()==0xff) {
      cgetc();
  }

} 

uint8_t Console::KeyModifierStatus(uint8_t  chr){
  API_PARAMETERS_ADDR[0] = chr;
  while(*API_COMMAND_ADDR) {}  
  *API_FUNCTION_ADDR  = API_FN_KEY_STATUS;
  *API_COMMAND_ADDR   = API_GROUP_SYSTEM;   
  while(*API_COMMAND_ADDR) {}
  return(API_PARAMETERS_ADDR[0]);            // Return parameter

}

void Console::ReadString(char * str){
uint8_t i, key;

  i=0;
  while (1) {
      key=cgetc();
      if (key == 13) {
          break; // Esce dal ciclo se viene premuto INVIO
      } else if (key == 8 || key == 26) {
          if (i>0) {
              i--;
              cputc(key); 
          }
      } else {
          // Aggiunge il carattere alla stringa di testo
          i++;
          cputc(key); 
          str[i] = key;
      }
  }
  
  str[0]=i;
  
}

int Console::ReadNumber(char * str, int len){
uint8_t i, key;
int value, dec;

  i=0;
  value=0;
  while (1) {
      key=cgetc();
      if (key == 13 || i > len) {
          break; // Esce dal ciclo se viene premuto INVIO
      } else if (key == 8 || key == 26) {
          if (i>0) {
              i--;
              cputc(key); 
          }
      } else if ((key>=48) && (key <= 57)){
          // Aggiunge il carattere alla stringa di testo
          i++;
          cputc(key); 
          str[i] = key;
      }
  }
  
  str[0]=i;
  value = atoi(&str[1]);

  return value;
}

 

