#include "BitFunctions.h"

/*template <class T>
inline uint8_t Bit(T Byte, uint8_t Bit)
{
    return (Byte >>Bit) & 0x1;
}*/

uint8_t Pow2(uint8_t v)
{
    uint8_t ReturnV=1;
    for(uint32_t counter=0; counter<v; counter++)
    {
        ReturnV*=2;
    }
    return ReturnV;
}

void SetBit(bool Value, uint8_t& Byte, uint8_t BitNumber)
{
    if(Value)
        Byte |= (1 << BitNumber);
    else
        Byte &= ~( 1 << BitNumber);
}
/*
uint8_t BitField(uint8_t Byte, uint8_t BitStart, uint8_t BitEnd)
{
    uint8_t ReturnV=0;
    for(int CurrentBit=BitStart; CurrentBit <= BitEnd; CurrentBit++)
    {
        ReturnV+= Bit(Byte, CurrentBit) * Pow2(CurrentBit - BitStart);
    }
    return ReturnV;
}*/

uint8_t Get2Bits(uint8_t Byte, uint8_t Bits)
{
    return (Byte >> Bits) & 3;
}

/*template uint8_t Bit<uint32_t>(uint32_t, uint8_t);
template uint8_t Bit<uint16_t>(uint16_t, uint8_t);
template uint8_t Bit<uint8_t>(uint8_t, uint8_t);
*/
