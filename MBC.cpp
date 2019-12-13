#include "MBC.h"

MBC1::MBC1(uint8_t* Buffer, size_t size)
{
    Head.Create(Buffer);
    CurrentRomBank=1;
    RamSize=GetRamSize(Head.RAM);
    Ram=RamSize ? new uint8_t[RamSize] : nullptr;
    Rom=Buffer;
    MaxRomBank= (size / 0x4000) + (size % 0x4000 !=0 ? 1 : 0);
    RomSize=size;
    std::cout <<"RAM ? " <<(uint32_t)RamSize<<"\n";
    for(uint32_t counter=0; counter <RamSize; counter++)
        Ram[counter]=0xFF;
}

void MBC1::Write(uint16_t Address, uint8_t Value)
{
    if(Address <= 0x1FFF)
        RamEnabled=Value == 0x0A;
    if(Address >= 0xA000 && Address <= 0xBFFF && Ram)
        Ram[Address - 0xA000 + CurrentRamBank * (0xBFFF - 0xA000)]=Value;
    if(Address >= 0x6000 && Address <= 0x7FFF)
        RamBanking= 0x00 != Value;
    if(Address >= 0x2000 && Address <= 0x3FFF)
    {
        Lower=Value;
        if(Lower == 0)
            Lower=1;
        CurrentRomBank= (Upper << 3) | (Lower & 0x1F);
        if(CurrentRomBank > MaxRomBank)
        {
            std::stringstream ss;
            ss <<"Current Rom Bank " <<(uint16_t)CurrentRomBank <<" is greater than max Rom Bank " <<(uint16_t)MaxRomBank<<"\n";
            Debug.Log(ss.str().c_str(), DebugLog::FatalError, "MBC.h");
        }
    }
    if(Address >= 0x4000 && Address <= 0x5FFF)
    {
        if(Ram && RamBanking && RamEnabled)
            CurrentRamBank=Value;
        else
        {
            Upper=Value;
            CurrentRomBank=(Upper << 3) | (Lower & 0x1F);
        }
    }
}

uint8_t MBC1::Read(uint16_t Address)
{
    if(Address <= 0x3FFF)
        return Rom[Address];
    if(Address >= 0x4000 && Address <= 0x7FFF)
        return Rom[Address - 0x4000 + CurrentRomBank * (0x4000)];
    if(Address >= 0xA000 && Address <= 0xBFFF)
        return Ram[Address - 0xA000 + CurrentRamBank * (0x2000)];
    return 0x00;
}


uint8_t* MBC1::GetPointer(uint16_t Address)
{

    if(Address <= 0x3FFF)
        return &(Rom[Address]);
    if(Address >= 0x4000 && Address <= 0x7FFF)
        return &(Rom[Address - 0x4000 + CurrentRomBank * (0x4000)]);
    if(Address >= 0xA000 && Address <= 0xBFFF)
        return &(Ram[Address - 0xA000 + CurrentRamBank * (0x2000)]);
    return 0x00;
}

MBC3::MBC3(uint8_t* Buffer, size_t size)
{
    Head.Create(Buffer);
    CurrentRomBank=1;
    RamSize=GetRamSize(Head.RAM);
    Ram=RamSize ? new uint8_t[RamSize] : nullptr;
    std::stringstream ss;
    ss<<"Loaded MBC1 Rom of size " <<size<<"\n";
    Debug.Log(ss.str().c_str(), DebugLog::Debug, "MBC.h");
    Rom=Buffer;
    MaxRomBank= (size / 0x4000) + (size % 0x4000 !=0 ? 1 : 0);
    RomSize=size;
    std::cout <<"RAM ? " <<(uint32_t)RamSize<<"\n";
    for(uint32_t counter=0; counter <RamSize; counter++)
        Ram[counter]=0xFF;
}

void MBC3::Write(uint16_t Address, uint8_t Value)
{
    if(Address <= 0x1FFF)
        RamEnabled=Value == 0x0A;
    if(Address >= 0xA000 && Address <= 0xBFFF && Ram)
        Ram[Address - 0xA000 + CurrentRamBank * (0xBFFF - 0xA000)]=Value;
    if(Address >= 0x2000 && Address <= 0x3FFF)
    {
        CurrentRomBank= Value & 0b01111111;;
        if(CurrentRomBank == 0)
            CurrentRomBank=1;
        if(CurrentRomBank > MaxRomBank)
        {
            std::stringstream ss;
            ss <<"Current Rom Bank " <<(uint16_t)CurrentRomBank <<" is greater than max Rom Bank " <<(uint16_t)MaxRomBank<<"\n";
            Debug.Log(ss.str().c_str(), DebugLog::FatalError, "MBC.h");
        }
    }
    if(Address >= 0x4000 && Address <= 0x5FFF)
    {
        CurrentRamBank=Value;
    }
}

uint8_t MBC3::Read(uint16_t Address)
{
    if(Address <= 0x3FFF)
        return Rom[Address];
    if(Address >= 0x4000 && Address <= 0x7FFF)
        return Rom[Address - 0x4000 + CurrentRomBank * (0x4000)];
    if(Address >= 0xA000 && Address <= 0xBFFF)
    {
        if(CurrentRamBank >= 0x08 && CurrentRamBank <= 0x0C)
            return 0;
        return Ram[Address - 0xA000 + CurrentRamBank * (0x2000)];
    }
    return 0x00;
}


uint8_t* MBC3::GetPointer(uint16_t Address)
{

    if(Address <= 0x3FFF)
        return &(Rom[Address]);
    if(Address >= 0x4000 && Address <= 0x7FFF)
        return &(Rom[Address - 0x4000 + CurrentRomBank * (0x4000)]);
    if(Address >= 0xA000 && Address <= 0xBFFF)
        return &(Ram[Address - 0xA000 + CurrentRamBank * (0x2000)]);
    return 0x00;
}

MBC5::MBC5(uint8_t* Buffer, size_t size)
{
    Head.Create(Buffer);
    CurrentRomBank=1;
    RamSize=GetRamSize(Head.RAM);
    Ram=RamSize ? new uint8_t[RamSize] : nullptr;
    std::stringstream ss;
    ss<<"Loaded MBC1 Rom of size " <<size<<"\n";
    Debug.Log(ss.str().c_str(), DebugLog::Debug, "MBC.h");
    Rom=Buffer;
    MaxRomBank= (size / 0x4000) + (size % 0x4000 !=0 ? 1 : 0);
    RomSize=size;
    std::cout <<"RAM ? " <<(uint32_t)RamSize<<"\n";
    for(uint32_t counter=0; counter <RamSize; counter++)
        Ram[counter]=0xFF;
}

void MBC5::Write(uint16_t Address, uint8_t Value)
{
    if(Address <= 0x1FFF)
        RamEnabled=Value == 0x0A;
    if(Address >= 0xA000 && Address <= 0xBFFF && Ram)
        Ram[Address - 0xA000 + CurrentRamBank * (0xBFFF - 0xA000)]=Value;
    if(Address >= 0x2000 && Address <= 0x2FFF)
    {
        Lower=Value;
        CurrentRomBank= (((uint16_t)Upper << 8) & 0x100) + Lower;
        if(CurrentRomBank > MaxRomBank)
        {
            std::stringstream ss;
            ss <<"Current Rom Bank " <<(uint16_t)CurrentRomBank <<" is greater than max Rom Bank " <<(uint16_t)MaxRomBank<<"\n";
            Debug.Log(ss.str().c_str(), DebugLog::FatalError, "MBC.h");
        }
    }
    if(Address >= 0x3000 && Address < 0x3FFF)
    {
        Upper=Value;
        CurrentRomBank= (((uint16_t)Upper << 8) & 0x100) + Lower;
        if(CurrentRomBank > MaxRomBank)
        {
            std::stringstream ss;
            ss <<"Current Rom Bank " <<(uint16_t)CurrentRomBank <<" is greater than max Rom Bank " <<(uint16_t)MaxRomBank<<"\n";
            Debug.Log(ss.str().c_str(), DebugLog::FatalError, "MBC.h");
        }
    }
    if(Address >= 0x4000 && Address <= 0x5FFF)
    {
        CurrentRamBank=Value;
    }
}

uint8_t MBC5::Read(uint16_t Address)
{
    if(Address <= 0x3FFF)
        return Rom[Address];
    if(Address >= 0x4000 && Address <= 0x7FFF)
        return Rom[Address - 0x4000 + CurrentRomBank * (0x4000)];
    if(Address >= 0xA000 && Address <= 0xBFFF)
        return Ram[Address - 0xA000 + CurrentRamBank * (0x2000)];
    return 0x00;
}


uint8_t* MBC5::GetPointer(uint16_t Address)
{

    if(Address <= 0x3FFF)
        return &(Rom[Address]);
    if(Address >= 0x4000 && Address <= 0x7FFF)
        return &(Rom[Address - 0x4000 + CurrentRomBank * (0x4000)]);
    if(Address >= 0xA000 && Address <= 0xBFFF)
        return &(Ram[Address - 0xA000 + CurrentRamBank * (0x2000)]);
    return 0x00;
}
