/**
 * \file MBC.h
 * \author Sean C.
 * \version 1.0
 * Defines the different types of memory bank controllers.
*/

#ifndef MBC_H_INCLUDED
#define MBC_H_INCLUDED
#include <sstream>
#include "Cart.h"
#include "DebugLog.h"

class MBC1: public Cart
{
public:

    MBC1(uint8_t* Buffer, size_t size);

    virtual void Write(uint16_t Address, uint8_t Value);

    virtual uint8_t Read(uint16_t Address);


    virtual uint8_t* GetPointer(uint16_t Address);

    bool RamEnabled=false;
    uint8_t CurrentRamBank=1;
    uint8_t CurrentRomBank=1;
    uint8_t MaxRomBank=1;

    uint8_t Lower=1;
    uint8_t Upper=0;
    bool RamBanking=false;

};

class MBC3: public Cart
{
public:

    MBC3(uint8_t* Buffer, size_t size);

    virtual void Write(uint16_t Address, uint8_t Value);

    virtual uint8_t Read(uint16_t Address);


    virtual uint8_t* GetPointer(uint16_t Address);

    bool RamEnabled=false;
    uint8_t CurrentRamBank=1;
    uint8_t CurrentRomBank=1;
    uint8_t MaxRomBank=1;

    uint8_t Lower=1;
    uint8_t Upper=0;
};



class MBC5: public Cart
{
public:

    MBC5(uint8_t* Buffer, size_t size);
    virtual void Write(uint16_t Address, uint8_t Value);

    virtual uint8_t Read(uint16_t Address);

    virtual uint8_t* GetPointer(uint16_t Address);

    bool RamEnabled=false;
    uint8_t CurrentRamBank=1;
    uint16_t CurrentRomBank=1;
    uint8_t MaxRomBank=1;

    uint8_t Lower=1;
    uint8_t Upper=0;

};

#endif // MBC_H_INCLUDED
