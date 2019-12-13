#include "RomOnly.h"

RomOnly::RomOnly(uint8_t* Buffer, size_t size)
{
    Head.Create(Buffer);
    Rom=Buffer;
    RomSize=size;
}

void RomOnly::Write(uint16_t Address, uint8_t Value)
{
}

uint8_t RomOnly::Read(uint16_t Address)
{
    return Rom[Address];
}

uint8_t* RomOnly::GetPointer(uint16_t Address)
{
    return Rom + Address;
}
