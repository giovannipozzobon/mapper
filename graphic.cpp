#include "graphic.hpp"

void Graphic::Gfx_DrawString(int x_pos , int y_pos, char * str)
{
	int ptr = (int) &str[0];

  	*API_FUNCTION_ADDR     = API_FN_DRAW_STRING;
  	API_PARAMETERS_ADDR[0] = x_pos & 0xFF; 
  	API_PARAMETERS_ADDR[1] = x_pos >> 8;      
  	API_PARAMETERS_ADDR[2] = y_pos & 0xFF;        
  	API_PARAMETERS_ADDR[3] = y_pos  >> 8;
  	API_PARAMETERS_ADDR[4] = ptr & 0xFF;        
  	API_PARAMETERS_ADDR[5] = ptr >> 8; 
  	*API_COMMAND_ADDR      = API_GROUP_GRAPHICS;
    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)

}


void Graphic::DrawPixel(int x,int y) {
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

void Graphic::DrawLine(int x1,int y1,int x2,int y2) {
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

void Graphic::DrawRectangle(int x1,int y1,int x2,int y2) {
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


void Graphic::DrawImage(int x,int y, uint8_t imageID) {
	
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


void Graphic::ResetPalette(){
    // Reset the palette
    *API_FUNCTION_ADDR     = API_RESET_PALETTE ;
    *API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;

}


void Graphic::SetDrawDefaults(uint8_t _and, uint8_t _xor, uint8_t solid, uint8_t dimension, uint8_t flip) {
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

void Graphic::SetCurrentTileMap(unsigned char * addr, int x, int y){
	
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

void Graphic::DrawTileMap(int x1, int y1, int x2, int y2){

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

void Graphic::SetPalette(uint8_t color, uint8_t r, uint8_t g, uint8_t b){

	while(*API_COMMAND_ADDR) {}
								 
    API_PARAMETERS_ADDR[0] = color;                     
    API_PARAMETERS_ADDR[1] = r;
    API_PARAMETERS_ADDR[2] = g;                     
    API_PARAMETERS_ADDR[3] = b;

	  *API_FUNCTION_ADDR     = API_SET_PALETTE;
  	*API_COMMAND_ADDR      = API_GROUP_GRAPHICS;
	
	while(*API_COMMAND_ADDR) {};

}

void Graphic::SetColor(uint8_t color)
{
  *API_FUNCTION_ADDR     = API_SET_COLOR;
  API_PARAMETERS_ADDR[0] = color        ;
  *API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;
  while(*API_COMMAND_ADDR) {};
}

void Graphic::SetSolidFlag(uint8_t flag)
{
  *API_FUNCTION_ADDR     = API_SET_SOLID_FLAG;
  API_PARAMETERS_ADDR[0] = flag        ;
  *API_COMMAND_ADDR      = API_GROUP_GRAPHICS ;
  while(*API_COMMAND_ADDR) {};
}