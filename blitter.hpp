#ifndef BLITTER_HPP
#define BLITTER_HPP

#include <stdio.h>
#include <cstdint>

class Blitter {

private:

    volatile uint8_t* API_COMMAND_ADDR      = (uint8_t*)0xFF00 ; // function group address
    volatile uint8_t* API_FUNCTION_ADDR     = (uint8_t*)0xFF01 ; // function address
    volatile uint8_t* API_ERROR_ADDR        = (uint8_t*)0xFF02 ; // function errors
    volatile uint8_t* API_STATUS_ADDR       = (uint8_t*)0xFF03 ; // function errors
    volatile uint8_t* API_PARAMETERS_ADDR   = (uint8_t*)0xFF04 ; // function parameters base address (8 bytes)

    // Blitter functions (Group 12)
    uint8_t API_GROUP_BLITTER           = (uint8_t )0x0C ; // API function group Blitter
    uint8_t API_FN_BLITTER_BUSY         = (uint8_t )0x01 ; // API function Busy Blitter
    uint8_t API_FN_SIMPLE_BLITTER_COPY  = (uint8_t )0x02 ; // API function Blitter Copy

    uint8_t BlitterBusy();

public:

    void WaitBlitter();
    uint8_t BlitterSimpleCopy(uint8_t t_source, char * adr_source, uint8_t t_destination, char * adr_destination, int numbytes);

};

#endif //BLITTER_HPP