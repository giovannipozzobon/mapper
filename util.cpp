#include "util.hpp"

unsigned int Util::nop_delay(unsigned int delay) {
    unsigned int timer;
    for(timer=0; timer<delay*7; timer++) {
        __asm__ ("NOP");
    }
    return timer;
}
