#ifndef FILE_HPP
#define FILE_HPP

#include <stdio.h>
#include <cstdint>

class File {

private:

    volatile uint8_t* API_COMMAND_ADDR    = (uint8_t*)0xFF00 ; // function group address
    volatile uint8_t* API_FUNCTION_ADDR   = (uint8_t*)0xFF01 ; // function address
    volatile uint8_t* API_PARAMETERS_ADDR = (uint8_t*)0xFF04 ; // function parameters base address (8 bytes)

    // File functions (Group 3)
    uint8_t API_GROUP_FILE          = (uint8_t )0x03 ; // API function group File
    uint8_t API_FN_CAT_DIR          = (uint8_t )0x01 ; // API function ID show the files in the directory
    uint8_t API_FN_LOAD_FILE        = (uint8_t )0x02 ; // API function ID Load from file to memory
    uint8_t API_FN_STORE_FILE       = (uint8_t )0x03 ; // API function ID Save memory to file 
    uint8_t API_FN_OPEN_FILE        = (uint8_t )0x04 ; // API function ID Open file 
    uint8_t API_FN_CLOSE_FILE       = (uint8_t )0x05 ; // API function ID Close file 
    uint8_t API_FN_READ_FILE        = (uint8_t )0x08 ; // API function ID Read file 
    uint8_t API_FN_WRITE_FILE       = (uint8_t )0x09 ; // API function ID Write file 


public:

    void DisplayDirectory();

    void OpenFile(uint8_t channel, unsigned char * fileName, uint8_t mode);

    void CloseFile(uint8_t channel);

    uint8_t WriteFile(uint8_t channel, int memory, int nrbyte);

    uint8_t LoadFile( int memory, unsigned char * fileName);

    uint8_t SaveFile( int memory, int nrbyte , unsigned char * fileName);


    uint8_t LoadGrafix(unsigned char * file); 

};

#endif //FILE_HPP