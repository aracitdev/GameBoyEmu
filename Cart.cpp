#include "Cart.h"

uint8_t Cart::CartRead(uint16_t Address, void* P)
{
    Cart* C=(Cart*)P;
    return C->Read(Address);
}

void Cart::CartWrite(uint16_t Address, uint8_t Value, void* P)
{
    Cart* C=(Cart*)P;
    C->Write(Address, Value);
}
