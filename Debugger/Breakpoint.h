#ifndef BREAKPOINT_H_INCLUDED
#define BREAKPOINT_H_INCLUDED
#include <cstdint>

class Breakpoint
{
public:

    Breakpoint(uint16_t A, uint8_t B);

    uint16_t Address;

    uint8_t Bank;
};

#endif // BREAKPOINT_H_INCLUDED
