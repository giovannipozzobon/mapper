#include "neo6502.hpp"
#include "api.hpp"

void SetCursorPosition(uint8_t x_pos , uint8_t y_pos)
{
  *API_FUNCTION_ADDR     = API_FN_CURSOR_POS ;
  API_PARAMETERS_ADDR[0] = x_pos             ;
  API_PARAMETERS_ADDR[1] = y_pos             ;
  *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;
}



void ResetChannelSound(uint8_t nr_channel)
{
  *API_FUNCTION_ADDR     = API_FN_SOUND_CH_RESET;
  API_PARAMETERS_ADDR[0] = nr_channel        ;
  *API_COMMAND_ADDR      = API_GROUP_SOUND ;
}



void PlaySoundChannel(uint8_t nr_channel, uint8_t sfx)
{
  *API_FUNCTION_ADDR     = API_FN_PLAY_SOUND;
  API_PARAMETERS_ADDR[0] = nr_channel;
  API_PARAMETERS_ADDR[1] = sfx                ;
  *API_COMMAND_ADDR      = API_GROUP_SOUND ;
}

void Gfx_DrawString(int x_pos , int y_pos, char * str)
{
	int ptr = (int) &str[0];

  	*API_FUNCTION_ADDR     = API_FN_DRAW_STRING;
  	API_PARAMETERS_ADDR[0] = x_pos & 0xFF; 
  	API_PARAMETERS_ADDR[1] = x_pos >> 8;      
  	API_PARAMETERS_ADDR[2] = y_pos & 0xFF;        
  	API_PARAMETERS_ADDR[3] = y_pos  >> 8;
  	API_PARAMETERS_ADDR[4] = ptr & 0xFF;        
  	API_PARAMETERS_ADDR[5] = ptr >> 8; 
  	*API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;
}

void write (const unsigned char* buf, unsigned count) {
 	volatile unsigned char *cmd = (unsigned char *)0xFF00;
 	while (count--) {
 		while(*API_COMMAND_ADDR) {};   
    *API_FUNCTION_ADDR     = API_FN_WRITE_CHAR;
    API_PARAMETERS_ADDR[0] = *buf++;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;
 	}
}


void DisplayDirectory()
{
	*API_FUNCTION_ADDR     = API_FN_CAT_DIR;
  *API_COMMAND_ADDR      = API_GROUP_FILE ;

}

void OpenFile(uint8_t channel, const unsigned char *  fileName, uint8_t mode)
{
	volatile int ptr = (volatile int) &fileName[0];
  	*API_FUNCTION_ADDR     = API_FN_OPEN_FILE;
    API_PARAMETERS_ADDR[0] = channel;   
  	API_PARAMETERS_ADDR[1] = ptr & 0xFF; 
  	API_PARAMETERS_ADDR[2] = ptr >> 8;           
  	API_PARAMETERS_ADDR[3] = mode;
  	*API_COMMAND_ADDR      = API_GROUP_FILE ;

    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)

}

void CloseFile(uint8_t channel)
{
  	*API_FUNCTION_ADDR     = API_FN_CLOSE_FILE;      
  	API_PARAMETERS_ADDR[0] = channel;
  	*API_COMMAND_ADDR      = API_GROUP_FILE ;

    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)

}

uint8_t WriteFile(uint8_t channel, int memory, int nrbyte)
{
  	int nr_written_byte;
    *API_FUNCTION_ADDR     = API_FN_WRITE_FILE;
  	API_PARAMETERS_ADDR[0] = channel;    
  	API_PARAMETERS_ADDR[1] = memory & 0xFF;        
  	API_PARAMETERS_ADDR[2] = memory  >> 8;
  	API_PARAMETERS_ADDR[4] = nrbyte & 0xFF;        
  	API_PARAMETERS_ADDR[5] = nrbyte  >> 8;
    
  	*API_COMMAND_ADDR      = API_GROUP_FILE ;

    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)
	  nr_written_byte = API_PARAMETERS_ADDR[1];
    nr_written_byte = nr_written_byte << 8;
    nr_written_byte += API_PARAMETERS_ADDR[0];
    return nr_written_byte;
}


uint8_t LoadFile( int memory, const unsigned char * fileName)
{
	volatile int ptr = (volatile int) &fileName[0];
  	*API_FUNCTION_ADDR     = API_FN_LOAD_FILE;
  	API_PARAMETERS_ADDR[0] = ptr & 0xFF; 
  	API_PARAMETERS_ADDR[1] = ptr >> 8;      
  	API_PARAMETERS_ADDR[2] = memory & 0xFF;        
  	API_PARAMETERS_ADDR[3] = memory  >> 8;
  	*API_COMMAND_ADDR      = API_GROUP_FILE ;

    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)
	  return API_PARAMETERS_ADDR[0];
}

uint8_t SaveFile( int memory, int nrbyte , const unsigned char * fileName)
{
	volatile int ptr = (volatile int) &fileName[0];
  	*API_FUNCTION_ADDR     = API_FN_STORE_FILE;
  	API_PARAMETERS_ADDR[0] = ptr & 0xFF; 
  	API_PARAMETERS_ADDR[1] = ptr >> 8;      
  	API_PARAMETERS_ADDR[2] = memory & 0xFF;        
  	API_PARAMETERS_ADDR[3] = memory  >> 8;
  	API_PARAMETERS_ADDR[4] = nrbyte & 0xFF;        
  	API_PARAMETERS_ADDR[5] = nrbyte  >> 8;
    
  	*API_COMMAND_ADDR      = API_GROUP_FILE ;

    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)
	  return API_PARAMETERS_ADDR[0];
}



void DrawPixel(int x,int y) {
	volatile unsigned char *cmd = (volatile unsigned char *)0xFF00;
    while(*API_COMMAND_ADDR) {};                         // Waits for the previous command to finish.
  	API_PARAMETERS_ADDR[0] = x & 0xFF; 
  	API_PARAMETERS_ADDR[1] = x >> 8;   
  	API_PARAMETERS_ADDR[2] = y & 0xFF;        
  	API_PARAMETERS_ADDR[3] = y >> 8;

 	  *API_FUNCTION_ADDR     = API_DRAW_PIXEL;
    *API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;
    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)

}

void DrawLine(int x1,int y1,int x2,int y2) {
	volatile unsigned char *cmd = (volatile unsigned char *)0xFF00;
    
    while(*API_COMMAND_ADDR) {};                       // Waits for the previous command to finish.
    API_PARAMETERS_ADDR[0] = x1 & 0xFF;                      // P0P1
    API_PARAMETERS_ADDR[1] = x1 >> 8;
    API_PARAMETERS_ADDR[2] = y1 & 0xFF;                     // P2P3
    API_PARAMETERS_ADDR[3] = y1 >> 8;
    API_PARAMETERS_ADDR[4] = x2 & 0xFF;                      // P4P5
    API_PARAMETERS_ADDR[5] = x2 >> 8;
    API_PARAMETERS_ADDR[6] = y2 & 0xFF;                      // P6P7
    API_PARAMETERS_ADDR[7] = y2 >> 8;

 	  *API_FUNCTION_ADDR     = API_DRAW_LINE ;
    *API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;
    while(*API_COMMAND_ADDR) {};                         // Wait for the command to finish (not strictly required)

}

void DrawRectangle(int x1,int y1,int x2,int y2) {
	volatile unsigned char *cmd = (volatile unsigned char *)0xFF00;
    while(*API_COMMAND_ADDR) {};                         // Waits for the previous command to finish.
    API_PARAMETERS_ADDR[0] = x1 & 0xFF;                      // P0P1
    API_PARAMETERS_ADDR[1] = x1 >> 8;
    API_PARAMETERS_ADDR[2] = y1 & 0xFF;                     // P2P3
    API_PARAMETERS_ADDR[3] = y1 >> 8;
    API_PARAMETERS_ADDR[4] = x2 & 0xFF;                      // P4P5
    API_PARAMETERS_ADDR[5] = x2 >> 8;
    API_PARAMETERS_ADDR[6] = y2 & 0xFF;                      // P6P7
    API_PARAMETERS_ADDR[7] = y2 >> 8;

 	  *API_FUNCTION_ADDR     = API_DRAW_RECTANGLE ;
    *API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;
    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)

}


void DrawImage(int x,int y, uint8_t imageID) {
	
    while(*API_COMMAND_ADDR) {};                         // Waits for the previous command to finish.
  	API_PARAMETERS_ADDR[0] = x & 0xFF; 
  	API_PARAMETERS_ADDR[1] = x >> 8;   
  	API_PARAMETERS_ADDR[2] = y & 0xFF;        
  	API_PARAMETERS_ADDR[3] = y >> 8;
    API_PARAMETERS_ADDR[4] = imageID;

 	  *API_FUNCTION_ADDR     = API_FN_DRAW_IMAGE;
    *API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;
    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)

}



uint8_t LoadGrafix(const unsigned char * file){   

	volatile int ptr = (volatile int) &file[0];	

	  while(*API_COMMAND_ADDR) {};    

   	API_PARAMETERS_ADDR[0] = ptr & 0xFF; ;	//File name		
    API_PARAMETERS_ADDR[1] = ptr >> 8;                      
    API_PARAMETERS_ADDR[2] = 0xFF;		//grafics file
    API_PARAMETERS_ADDR[3] = 0xFF;		//grafics file                    
 
   	*API_FUNCTION_ADDR     = API_FN_LOAD_FILE ;
    *API_COMMAND_ADDR      = API_GROUP_FILE;
    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)
	  return API_PARAMETERS_ADDR[0];


}  


//Update Sprite P0 : Position is (P1P2,P3P4) Image is P5 (bits 0-5 are
//sprite number, bit 6 indicates 32 bit – NOT the same as the image number
//in the graphics system, bit 7 is clear), P6 the flip value (bit 0 horizontal, bit 1 vertical, 
//bit 2-7 clear, P7 sets the anchor point.

void DrawSprite(uint8_t id, int x, int y, uint8_t image) {

    while(*API_COMMAND_ADDR) {};                       // Waits for the previous command to finish.
    API_PARAMETERS_ADDR[0] = id;								//P0 
    API_PARAMETERS_ADDR[1] = x & 0xFF;                      // P1P2
    API_PARAMETERS_ADDR[2] = x >> 8;
    API_PARAMETERS_ADDR[3] = y & 0xFF;                     // P3P4
    API_PARAMETERS_ADDR[4] = y >> 8;
    API_PARAMETERS_ADDR[5] = image;                      // P5
    API_PARAMETERS_ADDR[6] = 0x00;                      // P6P7
    API_PARAMETERS_ADDR[7] = 0x00;

   	*API_FUNCTION_ADDR     = API_FN_UPDATE_SPRITE ;
    *API_COMMAND_ADDR      = API_GROUP_SPRITE ;
    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)

}

void MoveSprite(uint8_t id, int x, int y) {

   	while(*API_COMMAND_ADDR) {};                       // Waits for the previous command to finish.
    API_PARAMETERS_ADDR[0] = id;								//P0 
    API_PARAMETERS_ADDR[1] = x & 0xFF;                      // P1P2
    API_PARAMETERS_ADDR[2] = x >> 8;
    API_PARAMETERS_ADDR[3] = y & 0xFF;                     // P3P4
    API_PARAMETERS_ADDR[4] = y >> 8;
    API_PARAMETERS_ADDR[5] = 0x80;                      // P5
    API_PARAMETERS_ADDR[6] = 0x80;                      // P6P7
    API_PARAMETERS_ADDR[7] = 0x80;
  
    *API_FUNCTION_ADDR     = API_FN_UPDATE_SPRITE ;
    *API_COMMAND_ADDR      = API_GROUP_SPRITE ;
    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)
}

uint8_t DistanceSprites(uint8_t id_sprite1, uint8_t id_sprite2, uint8_t distance) {

   	while(*API_COMMAND_ADDR) {};                       // Waits for the previous command to finish.
    API_PARAMETERS_ADDR[0] = id_sprite1;								//P0 
    API_PARAMETERS_ADDR[1] = id_sprite2;                      // P1P2
    API_PARAMETERS_ADDR[2] = distance;
  
    *API_FUNCTION_ADDR     = API_FN_DISTANCE_SPRITE ;
    *API_COMMAND_ADDR      = API_GROUP_SPRITE ;
    while(*API_COMMAND_ADDR) {}; 
    
    return API_PARAMETERS_ADDR[0];                         // Wait for the command to finish (not strictly required)
}

void HideSprite(uint8_t id) {

    while(*API_COMMAND_ADDR) {};                       // Waits for the previous command to finish.
    API_PARAMETERS_ADDR[0] = id;								       //P0 

   	*API_FUNCTION_ADDR     = API_FN_HIDE_SPRITE ;
    *API_COMMAND_ADDR      = API_GROUP_SPRITE ;
    while(*API_COMMAND_ADDR) {};                       // Wait for the command to finish (not strictly required)

}

void ResetSprite() {

    while(*API_COMMAND_ADDR) {};                          // Waits for the previous command to finish.
    *API_FUNCTION_ADDR    = API_FN_RESET_SPRITE;					 // Reset Sprite
    *API_COMMAND_ADDR      = API_GROUP_SPRITE ;
    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)

}


uint8_t CheckJoypad(){

	while(*API_COMMAND_ADDR) {}
	
	*API_FUNCTION_ADDR     = API_FN_READ_CONTROLLER;
  *API_COMMAND_ADDR      = API_GROUP_CONTROLLER;
	
	while(*API_COMMAND_ADDR) {};
	return API_PARAMETERS_ADDR[0];

}


int readTimer(){
	int timer;

  *API_FUNCTION_ADDR     = API_FN_TIMER ;
  *API_COMMAND_ADDR      = API_GROUP_GENERAL ;

  while(*API_COMMAND_ADDR) {};
  
  timer = API_PARAMETERS_ADDR[0];
  timer = timer*10+API_PARAMETERS_ADDR[1];
  timer = timer*10+API_PARAMETERS_ADDR[2];
  timer = timer*10+API_PARAMETERS_ADDR[3];
	
	return timer;	
};

void waitXcycleclock(int cicli){
	int timer1, timer2, diff,scambia;
	timer1= readTimer();
	timer2= readTimer();
	
	if (timer2 < timer1) {scambia=timer2; timer2=timer1; timer1=scambia;}
	diff=timer2-timer1;
	
  while (diff<cicli){
		timer2= readTimer();
		diff = timer2 - timer1;
	}

}

void ResetPalette(){
    // Reset the palette
    *API_FUNCTION_ADDR     = API_RESET_PALETTE ;
    *API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;

}


void SetDrawDefaults(uint8_t _and, uint8_t _xor, uint8_t solid, uint8_t dimension, uint8_t flip) {
	  //SetColor(0xf0,7,1,1,0);
    //0xf0 use when is a image and second parameter is color
	
    while(*API_COMMAND_ADDR) {};                        // Waits for the previous command to finish.
   	API_PARAMETERS_ADDR[0] = _and;                      // P0P1
   	API_PARAMETERS_ADDR[1] = _xor;
   	API_PARAMETERS_ADDR[2] = solid;                     // P2P3
   	API_PARAMETERS_ADDR[3] = dimension;
   	API_PARAMETERS_ADDR[4] = flip;                      // P4
 
 	  *API_FUNCTION_ADDR     = API_SET_DEFAULTS ;
    *API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;
    while(*API_COMMAND_ADDR) {};   						// Wait for the command to finish (not strictly required)

}

void SetCurrentTileMap(unsigned char * addr, int x, int y){
	
	volatile int ptr = (int) &addr[0];	

	while(*API_COMMAND_ADDR) {}
								
    API_PARAMETERS_ADDR[0] = ptr & 0xFF;                      // P0P1
    API_PARAMETERS_ADDR[1] = ptr >> 8;
    API_PARAMETERS_ADDR[2] = x & 0xFF;                      // P2P3
    API_PARAMETERS_ADDR[3] = x >> 8;
    API_PARAMETERS_ADDR[4] = y & 0xFF;                     // P4P5
    API_PARAMETERS_ADDR[5] = y >> 8;

	  *API_FUNCTION_ADDR     = API_SET_CUR_TILEMAP;
  	*API_COMMAND_ADDR      = API_GROUP_GRAPHICS;
	
	while(*API_COMMAND_ADDR) {};

}

void DrawTileMap(int x1, int y1, int x2, int y2){

	while(*API_COMMAND_ADDR) {}
								 
    API_PARAMETERS_ADDR[0] = x1 & 0xFF;                      // P0P1
    API_PARAMETERS_ADDR[1] = x1 >> 8;
    API_PARAMETERS_ADDR[2] = y1 & 0xFF;                     // P2P3
    API_PARAMETERS_ADDR[3] = y1 >> 8;
    API_PARAMETERS_ADDR[4] = x2 & 0xFF;                      // P4P5
    API_PARAMETERS_ADDR[5] = x2 >> 8;
    API_PARAMETERS_ADDR[6] = y2 & 0xFF;                     // P6P7
    API_PARAMETERS_ADDR[7] = y2 >> 8;

	  *API_FUNCTION_ADDR     = API_FN_DRAW_TILEMAP;
  	*API_COMMAND_ADDR      = API_GROUP_GRAPHICS;
	
	while(*API_COMMAND_ADDR) {};

}

unsigned int nop_delay(unsigned int delay) {
    unsigned int timer;
    for(timer=0; timer<delay*7; timer++) {
        __asm__ ("NOP");
    }
    return timer;
}


void SetPalette(uint8_t color, uint8_t r, uint8_t g, uint8_t b){

	while(*API_COMMAND_ADDR) {}
								 
    API_PARAMETERS_ADDR[0] = color;                     
    API_PARAMETERS_ADDR[1] = r;
    API_PARAMETERS_ADDR[2] = g;                     
    API_PARAMETERS_ADDR[3] = b;

	  *API_FUNCTION_ADDR     = API_SET_PALETTE;
  	*API_COMMAND_ADDR      = API_GROUP_GRAPHICS;
	
	while(*API_COMMAND_ADDR) {};

}

void SetColor(uint8_t color)
{
  *API_FUNCTION_ADDR     = API_SET_COLOR;
  API_PARAMETERS_ADDR[0] = color        ;
  *API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;
  while(*API_COMMAND_ADDR) {};
}

void SetSolidFlag(uint8_t flag)
{
  *API_FUNCTION_ADDR     = API_SET_SOLID_FLAG;
  API_PARAMETERS_ADDR[0] = flag        ;
  *API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;
  while(*API_COMMAND_ADDR) {};
}

void ClearScreen(){
    // Clear Screen
    *API_FUNCTION_ADDR     = API_FN_CLEAR_SCREEN ;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE;
    while(*API_COMMAND_ADDR) {};

} 

char CheckKeyboardArray(){
    // Check keyboard array
 
    *API_FUNCTION_ADDR     = API_FN_CHECK_STATUS ;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;
    return(API_PARAMETERS_ADDR[0]);

} 

void ReturnToBasic(){
    // Return to basic

    *API_FUNCTION_ADDR     = API_FN_BASIC ;
    *API_COMMAND_ADDR      = API_GROUP_GENERAL ;
    while(*API_COMMAND_ADDR) {};

} 

// Get character from keyboard
int inkey() {
    while(*API_COMMAND_ADDR) {}  
    *API_FUNCTION_ADDR     = API_FN_READ_CHAR ;
    *API_COMMAND_ADDR      = API_GROUP_CONSOLE ;                 // Group 2, Command 1
    while(*API_COMMAND_ADDR) {}
    return(API_PARAMETERS_ADDR[0]);            // Return parameter
}


int cgetc() {
  char ch=0;
  while(ch==0) {
    ch=inkey();
  }
  return ch;
}


// Position cursor (API Group 2, Function 7)
void gotoxy(uint8_t sx, uint8_t sy)
{
  API_PARAMETERS_ADDR[0] = sx;
  API_PARAMETERS_ADDR[1] = sy;
  *API_FUNCTION_ADDR  = API_FN_CURSOR_POS  ;
  *API_COMMAND_ADDR   = API_GROUP_CONSOLE ;     
}


// Put a character
void cputc(char ch) {

    while(*API_COMMAND_ADDR) {}  
    API_PARAMETERS_ADDR[0] = ch;
    *API_FUNCTION_ADDR  = API_FN_WRITE_CHAR_CURS  ;
    *API_COMMAND_ADDR   = API_GROUP_CONSOLE ;   
}

// Put a character at screen coord
void cputcxy(int sx, int sy, char ch) {
    gotoxy(sx,sy);
    cputc(ch);
}

// Clear screen
void clrscr() {
    cputc(12);
    gotoxy(0,0);
}

void ClearKeyboardArray(){
    // Clear keyboard array
    while(CheckKeyboardArray()==0xff) {
      cgetc();
    }

} 
 

// Set speed of serial
void SetSpeed_ProtocolUART(uint32_t baudrate) { 

    while(*API_COMMAND_ADDR) {}  
    API_PARAMETERS_ADDR[0] = baudrate & 0xFF;                      
    API_PARAMETERS_ADDR[1] = ((baudrate >> 8)& 0xFF);
    API_PARAMETERS_ADDR[2] = ((baudrate >> 16)& 0xFF);                    
    API_PARAMETERS_ADDR[3] = ((baudrate >> 24)& 0xFF);  
    API_PARAMETERS_ADDR[4] = 0;                      
    *API_FUNCTION_ADDR  = API_FN_SET_SPEED_PROT;
    *API_COMMAND_ADDR   = API_GROUP_UEXT_IO;
    while(*API_COMMAND_ADDR) {}     
}

// Write byte to UART
void WritelUART(uint8_t chr) {

    while(*API_COMMAND_ADDR) {}  
    API_PARAMETERS_ADDR[0] = chr;                                          
    *API_FUNCTION_ADDR  = API_FN_WRITE_UART;
    *API_COMMAND_ADDR   = API_GROUP_UEXT_IO;  
    while(*API_COMMAND_ADDR) {}   
}

// Write string to UART
void WriteStringTolUART(char * ptr_str){
  int i=0;
  while(ptr_str[i]!= 0) {
    WritelUART(ptr_str[i]);
  }

}


void MoveCursorMouse(int x,int y){

    API_PARAMETERS_ADDR[0] = x & 0xFF;                      // P0P1
    API_PARAMETERS_ADDR[1] = x >> 8;
    API_PARAMETERS_ADDR[2] = y & 0xFF;                     // P2P3
    API_PARAMETERS_ADDR[3] = y >> 8;
    *API_FUNCTION_ADDR  = API_FN_MOVE_CURSOR;
    *API_COMMAND_ADDR   = API_GROUP_MOUSE;   
   

};

void SetCursorOnOff(uint8_t statecursor){

    API_PARAMETERS_ADDR[0] = statecursor;   
    *API_FUNCTION_ADDR  = API_FN_MOUSE_CURS_ON_OFF;
    *API_COMMAND_ADDR   = API_GROUP_MOUSE;   

};

mouse_state GetMouseState(){
    mouse_state mouse_data;
    
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
  return mouse_data;

};


uint8_t TestMousePresent(){

    *API_FUNCTION_ADDR  = API_FN_TEST_MOUSE_EXIST;
    *API_COMMAND_ADDR   = API_GROUP_MOUSE;   
    return(API_PARAMETERS_ADDR[0]);

};

uint8_t SelectMouseCursor(uint8_t shape){

    API_PARAMETERS_ADDR[0] = shape;   
    *API_FUNCTION_ADDR  = API_FN_SEL_MOUSE_CURSOR;
    *API_COMMAND_ADDR   = API_GROUP_MOUSE;  
    return(API_PARAMETERS_ADDR[0]); 
};