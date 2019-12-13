#ifndef MEMORYMAP_H_INCLUDED
#define MEMORYMAP_H_INCLUDED
#include <cstdint>

namespace MemoryMap
{
    constexpr uint16_t MemoryStart=     0x0000;

    constexpr uint16_t IntVecsStart=    0x0000;
    constexpr uint16_t IntVecsEnd=      0x00FF;
    constexpr uint16_t IntVecsSize=     IntVecsEnd-IntVecsStart;

    constexpr uint16_t CartHeadStart=   0x0100;
    constexpr uint16_t CartHeadEnd=     0x011F;
    constexpr uint16_t CartHeadSize=    CartHeadEnd-CartHeadStart;

    constexpr uint16_t CartBank0Start=  0x0150;
    constexpr uint16_t CartBank0End=    0x3FFF;
    constexpr uint16_t CartBank0Size=   CartBank0End - CartBank0Start;

    constexpr uint16_t CartBankXStart=  0x4000;
    constexpr uint16_t CartBankXEnd=    0x7FFF;
    constexpr uint16_t CartBankXSize=   CartBankXEnd-CartBankXStart;

    constexpr uint16_t CRamStart=       0x8000;
    constexpr uint16_t CRamEnd=         0x97FF;
    constexpr uint16_t CRamSize=        CRamEnd - CRamStart;

    constexpr uint16_t MapsStart=       0x9C00;

    constexpr uint16_t BGMap1Start=     0x9800;
    constexpr uint16_t BGMap1End=       0x9BFF;
    constexpr uint16_t BGMap1Size=      BGMap1End - BGMap1Start;

    constexpr uint16_t BGMap2Start=     0x9C00;
    constexpr uint16_t BGMap2End=       0x9FFF;
    constexpr uint16_t BGMap2Size=      BGMap2End - BGMap2Start;

    constexpr uint16_t MapsEnd=         0x9FFF;

    constexpr uint16_t CartRamStart=    0xA000;
    constexpr uint16_t CartRamEnd=      0xBFFF;
    constexpr uint16_t CartRamSize=     CartRamEnd-CartRamStart;

    constexpr uint16_t IntRam0Start=    0xC000;
    constexpr uint16_t IntRam0End=      0xDFFF;
    constexpr uint16_t IntRam0Size=     IntRam0End - IntRam0Start;

    constexpr uint16_t IntRamXStart=    0xD000;
    constexpr uint16_t IntRamXEnd=      0xDFFF;
    constexpr uint16_t IntRamXSize= IntRamXEnd-IntRamXStart;
    constexpr uint16_t EchoStart=       0xE000;
    constexpr uint16_t EchoEnd=         0xFDFF;

    constexpr uint16_t OemStart=        0xFE00;
    constexpr uint16_t OemEnd=          0xFE9F;
    constexpr uint16_t OemSize=         OemEnd-OemStart;

    constexpr uint16_t Unusable=        0xFEA0;

    constexpr uint16_t HardwareRegsStart=0xFF00;
    constexpr uint16_t HardwareRegsEnd= 0xFF7F;
    constexpr uint16_t HardwareRegsSize=HardwareRegsEnd - HardwareRegsStart;
    constexpr uint16_t ZeroPage=        0xFF80;
    constexpr uint16_t Interrupt=       0xFFFF;
}

#endif // MEMORYMAP_H_INCLUDED
