#ifndef ROMONLY_H_INCLUDED
#define ROMONLY_H_INCLUDED
#include "Cart.h"

class RomOnly: public Cart
{
public:

    RomOnly(uint8_t* Buffer, size_t size);

    virtual void Write(uint16_t Address, uint8_t Value);

    virtual uint8_t Read(uint16_t Address);

    virtual uint8_t* GetPointer(uint16_t Address);

};

#endif // ROMONLY_H_INCLUDED
