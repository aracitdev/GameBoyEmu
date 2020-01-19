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

bool MBC1::SaveState(std::ofstream& out)
{
    Cart::SaveState(out);
    out.write((const char*)(&CurrentRamBank), sizeof(CurrentRamBank));
    out.write((const char*)(&CurrentRomBank), sizeof(CurrentRomBank));
    out.write((const char*)(&Lower), sizeof(Lower));
    out.write((const char*)(&Upper), sizeof(Upper));
    out.write((const char*)(&RamBanking),sizeof(RamBanking));
    out.write((const char*)(&RamEnabled), sizeof(RamEnabled));
    return true;
}

bool MBC1::LoadState(std::ifstream& in)
{
    Cart::LoadState(in);
    in.read((char*)(&CurrentRamBank), sizeof(CurrentRamBank));
    in.read((char*)(&CurrentRomBank), sizeof(CurrentRomBank));
    in.read((char*)(&Lower), sizeof(Lower));
    in.read((char*)(&Upper), sizeof(Upper));
    in.read((char*)(&RamBanking), sizeof(RamBanking));
    in.read((char*)(&RamEnabled),sizeof(RamEnabled));
    return true;
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
    lastUpdate=0;
    RTC.Control=0;
    RTC.Days=0;
    RTC.Hours=0;
    RTC.Minutes=0;
    RTC.Seconds=0;
    std::cout <<"RAM ? " <<(uint32_t)RamSize<<"\n";
    for(uint32_t counter=0; counter <RamSize; counter++)
        Ram[counter]=0xFF;
}

void MBC3::Write(uint16_t Address, uint8_t Value)
{
    if(Address <= 0x1FFF)
        RamEnabled=Value == 0x0A;
    if(Address >= 0xA000 && Address <= 0xBFFF)
    {
        if(!RTCRead && Ram)
            Ram[Address - 0xA000 + CurrentRamBank * (0xBFFF - 0xA000)]=Value;
        else
        {
            switch(RTCRegister)
            {
            case 0x08:
                RTC.Seconds=Value;
                break;
            case 0x09:
                RTC.Minutes=Value;
                break;
            case 0x0A:
                RTC.Hours=Value;
                break;
            case 0x0B:
                RTC.Days=Value;
                break;
            case 0x0C:
                RTC.Control = (RTC.Control & 0x80)|(Value & 0xC1);
                break;
            }
        }
    }
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
        if(Value <= 0x03)
        {
            RTCRead=false;
            CurrentRamBank=Value;
        }
        else
        {
            RTCRegister=Value;
            RTCRead=true;
        }
    }
    if(Address >= 0x6000 && Address <= 0x7FFF)
    {
        UpdateRTC();
        LatchRTC();
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
        if(Ram && !RTCRead)
        {
            if(CurrentRamBank >= 0x08 && CurrentRamBank <= 0x0C)
                return 0;
            return Ram[Address - 0xA000 + CurrentRamBank * (0x2000)];
        }
        else
        {
            switch (RTCRegister)
            {
                case 0x08:
                    return RTC.LatchSeconds;
                    break;
                case 0x09:
                    return RTC.LatchMinutes;
                    break;
                case 0x0A:
                    return RTC.LatchHours;
                    break;
                case 0x0B:
                    return RTC.LatchDays;
                    break;
                case 0x0C:
                    return RTC.LatchControl;
                    break;
                }
        }
    }
    return 0x00;
}


void MBC3::UpdateRTC(void)
{
    time_t currentTime;
    time(&currentTime);
    if(!Bit(RTC.Control,6) && lastUpdate != currentTime)
    {
        time_t timeSinceLastUpdate = currentTime - lastUpdate;
        lastUpdate = currentTime;
        RTC.Seconds = (RTC.Seconds + timeSinceLastUpdate % 60);
        if(RTC.Seconds >= 60)
        {
            RTC.Seconds %= 60;
            RTC.Minutes++;
        }

        time_t minutesSinceLastUpdate = timeSinceLastUpdate / 60;
        RTC.Minutes = (RTC.Minutes + minutesSinceLastUpdate % 60);
        if(RTC.Minutes >= 60)
        {
            RTC.Minutes %=60;
            RTC.Hours ++;
        }
        size_t hoursSinceLastUpdate = minutesSinceLastUpdate / 60;
        RTC.Hours = (RTC.Hours + hoursSinceLastUpdate % 24);
        if(RTC.Hours >= 24)
        {
            RTC.Hours %= 24;
            RTC.Days++;
        }
        size_t daysSinceLastUpdate = (hoursSinceLastUpdate / 24);
        RTC.Days = (RTC.Days + daysSinceLastUpdate);
        if(RTC.Days > 0xFF)
        {
            SetBit(true,RTC.Control,0);
            if(RTC.Days > 511)
            {
                RTC.Days %= 512;
                SetBit(true,RTC.Control,7);
                SetBit(false, RTC.Control,0);
            }
        }
    }
}

void MBC3::LatchRTC(void)
{
        RTC.LatchSeconds=RTC.Seconds;
        RTC.LatchMinutes=RTC.Minutes;
        RTC.LatchHours=RTC.Hours;
        RTC.LatchDays=RTC.Days;
        RTC.LatchControl = RTC.Control;
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

bool MBC3::SaveState(std::ofstream& out)
{
    Cart::SaveState(out);
    out.write((const char*)(&CurrentRamBank), sizeof(CurrentRamBank));
    out.write((const char*)(&CurrentRomBank), sizeof(CurrentRomBank));
    out.write((const char*)(&Lower), sizeof(Lower));
    out.write((const char*)(&Upper), sizeof(Upper));
    out.write((const char*)(&RamEnabled),sizeof(RamEnabled));
    return true;
}

bool MBC3::LoadState(std::ifstream& in)
{
    Cart::LoadState(in);
    in.read((char*)(&CurrentRamBank), sizeof(CurrentRamBank));
    in.read((char*)(&CurrentRomBank), sizeof(CurrentRomBank));
    in.read((char*)(&Lower), sizeof(Lower));
    in.read((char*)(&Upper), sizeof(Upper));
    in.read((char*)(&RamEnabled), sizeof(RamEnabled));
    return true;
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



bool MBC5::SaveState(std::ofstream& out)
{
    Cart::SaveState(out);
    out.write((const char*)(&CurrentRamBank), sizeof(CurrentRamBank));
    out.write((const char*)(&CurrentRomBank), sizeof(CurrentRomBank));
    out.write((const char*)(&Lower), sizeof(Lower));
    out.write((const char*)(&Upper), sizeof(Upper));
    out.write((const char*)(&RamEnabled),sizeof(RamEnabled));
    return true;
}


bool MBC5::LoadState(std::ifstream& in)
{
    Cart::LoadState(in);
    in.read((char*)(&CurrentRamBank), sizeof(CurrentRamBank));
    in.read((char*)(&CurrentRomBank), sizeof(CurrentRomBank));
    in.read((char*)(&Lower), sizeof(Lower));
    in.read((char*)(&Upper), sizeof(Upper));
    in.read((char*)(&RamEnabled), sizeof(RamEnabled));
    return true;
}
