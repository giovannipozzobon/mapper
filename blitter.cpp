#include "blitter.hpp"
#include <stdio.h>


uint8_t Blitter::BlitterBusy(){

    *API_FUNCTION_ADDR     = API_FN_BLITTER_BUSY;
    *API_COMMAND_ADDR      = API_GROUP_BLITTER;
    return API_PARAMETERS_ADDR[0];

}

void Blitter::WaitBlitter(){
uint8_t busy=1;

    while (busy!=0){
        busy=BlitterBusy();
    };

}

uint8_t Blitter::BlitterSimpleCopy(uint8_t t_source, char * adr_source, uint8_t t_destination, char * adr_destination, int numbytes){

    int ptr_dest = (int) &adr_destination[0];
    int ptr_source = (int) &adr_source[0];

  	*API_FUNCTION_ADDR     = API_FN_SIMPLE_BLITTER_COPY;
  	
    API_PARAMETERS_ADDR[0] = t_source;     
  	API_PARAMETERS_ADDR[1] = ptr_source & 0xFF;        
  	API_PARAMETERS_ADDR[2] = ptr_source  >> 8;
  	API_PARAMETERS_ADDR[3] = t_destination;         
    API_PARAMETERS_ADDR[4] = ptr_dest & 0xFF;        
  	API_PARAMETERS_ADDR[5] = ptr_dest  >> 8;
    API_PARAMETERS_ADDR[6] = numbytes & 0xFF;        
  	API_PARAMETERS_ADDR[7] = numbytes  >> 8;
    /*
    API_PARAMETERS_ADDR[0] = t_source;     
  	API_PARAMETERS_ADDR[1] = adr_source;
  	API_PARAMETERS_ADDR[3] = t_destination;         
    API_PARAMETERS_ADDR[4] = adr_destination;
    API_PARAMETERS_ADDR[6] = numbytes;
    */
  	*API_COMMAND_ADDR      = API_GROUP_BLITTER;
    while(*API_COMMAND_ADDR) {}; 

	return API_ERROR_ADDR[0];

}

