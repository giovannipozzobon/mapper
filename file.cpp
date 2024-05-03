#include "file.hpp"


uint8_t File::LoadGrafix(unsigned char * file){   

	int ptr = (int) &file[0];	

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

void File::DisplayDirectory()
{
	*API_FUNCTION_ADDR     = API_FN_CAT_DIR;
    *API_COMMAND_ADDR      = API_GROUP_FILE ;

}

void File::OpenFile(uint8_t channel, unsigned char *  fileName, uint8_t mode)
{
	int ptr = (int) &fileName[0];
  	*API_FUNCTION_ADDR     = API_FN_OPEN_FILE;
    API_PARAMETERS_ADDR[0] = channel;   
  	API_PARAMETERS_ADDR[1] = ptr & 0xFF; 
  	API_PARAMETERS_ADDR[2] = ptr >> 8;           
  	API_PARAMETERS_ADDR[3] = mode;
  	*API_COMMAND_ADDR      = API_GROUP_FILE ;

    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)

}

void File::CloseFile(uint8_t channel)
{
  	*API_FUNCTION_ADDR     = API_FN_CLOSE_FILE;      
  	API_PARAMETERS_ADDR[0] = channel;
  	*API_COMMAND_ADDR      = API_GROUP_FILE ;

    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)

}

uint8_t File::WriteFile(uint8_t channel, int memory, int nrbyte)
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


uint8_t File::LoadFile( int memory, unsigned char * fileName)
{
	int ptr = (int) &fileName[0];
  	*API_FUNCTION_ADDR     = API_FN_LOAD_FILE;
  	API_PARAMETERS_ADDR[0] = ptr & 0xFF; 
  	API_PARAMETERS_ADDR[1] = ptr >> 8;      
  	API_PARAMETERS_ADDR[2] = memory & 0xFF;        
  	API_PARAMETERS_ADDR[3] = memory  >> 8;
  	*API_COMMAND_ADDR      = API_GROUP_FILE ;

    while(*API_COMMAND_ADDR) {};                          // Wait for the command to finish (not strictly required)
	  return API_PARAMETERS_ADDR[0];
}

uint8_t File::SaveFile( int memory, int nrbyte , unsigned char * fileName)
{
	int ptr = (int) &fileName[0];
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
