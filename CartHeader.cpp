#include "CartHeader.h"

namespace HeaderLocations
{
    const uint32_t EntryPoint = 0x100;
    const uint32_t Logo = 0x104;
    const uint32_t Title = 0x134;
    const uint32_t ManufacturerCode = 0x13F;
    const uint32_t CgbFlag = 0x143;
    const uint32_t NewLicenseCode = 0x144;
    const uint32_t SgbFlag = 0x146;
    const uint32_t CartridgeTypePos = 0x147;
    const uint32_t RomSizePos = 0x148;
    const uint32_t RamSizePos = 0x149;
    const uint32_t DestinationCode = 0x14A;
    const uint32_t OldLicenseCode = 0x14B;
    const uint32_t VersionNumber = 0x14C;
    const uint32_t HeaderChecksum = 0x14D;
    const uint32_t GlobalChecksum = 0x14E;
}


const char* CartridgeTypeTexts[] = {"RomOnly", "MBC1", "MBC2", "MBC3", "MBC4","MBC5", "Unknown"};

CartridgeType GetType(uint8_t type)
{
    switch (type)
    {
        case 0x00:
        case 0x08:
        case 0x09:
            return CartridgeType::ROMOnly;
        case 0x01:
        case 0x02:
        case 0x03:
        case 0xFF:
            return CartridgeType::MBC1;
        case 0x05:
        case 0x06:
            return CartridgeType::MBC2;
        case 0x0F:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            return CartridgeType::MBC3;
        case 0x15:
        case 0x16:
        case 0x17:
            return CartridgeType::MBC4;
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
            return CartridgeType::MBC5;
        case 0x0B:
        case 0x0C:
        case 0x0D:
        case 0x20:
        case 0x22:
        case 0xFC:
        case 0xFD:
        case 0xFE:
            return CartridgeType::Unknown;
        default:
            std::cout <<"Unknown cartridge type";
            return CartridgeType::Unknown;
    }
}

std::string ToString(CartridgeType type)
{
    uint32_t tp=((uint32_t)type);
    return std::string(CartridgeTypeTexts[tp]);
}

const uint32_t RomSizes[] = {KB(32), KB(64), KB(128), KB(256), KB(512), MB(1), MB(2), MB(4), MB(2)};
const char* RomSizeTexts[]={"32KB","64KB", "128KB", "256KB", "512KB", "1MB", "2MB","4MB","2MB"};

ROMSize GetRomSizeCode(uint8_t Size)
{
    switch (Size)
    {
        case 0x00:
            return ROMSize::KB32;
        case 0x01:
            return ROMSize::KB64;
        case 0x02:
            return ROMSize::KB128;
        case 0x03:
            return ROMSize::KB256;
        case 0x04:
            return ROMSize::KB512;
        case 0x05:
            return ROMSize::MB1;
        case 0x06:
            return ROMSize::MB2;
        case 0x07:
            return ROMSize::MB4;
        case 0x52:
            return ROMSize::MB1p1;
        case 0x53:
            return ROMSize::MB1p2;
        case 0x54:
            return ROMSize::MB1p5;
        default:
            std::cout <<"Unknown ROM size.\n";
            return ROMSize::KB32;
    }
}

size_t GetRomSize(ROMSize size)
{
    uint32_t sz=(uint32_t)(size);
    if(sz > sizeof(RomSizes))
    {
        std::cout <<"Cart rom size not handled\n";
        return 0;
    }
    return RomSizes[sz];
}

std::string ToString(ROMSize size)
{
    uint32_t sz=(uint32_t)(size);
    if(sz > sizeof(RomSizeTexts))
        return std::string();
    return RomSizeTexts[sz];
}

RAMSize GetRamSizeCode(uint8_t size_code)
{
    switch (size_code)
    {
        case 0x00:
            return RAMSize::None;
        case 0x01:
            return RAMSize::KB2;
        case 0x02:
            return RAMSize::KB8;
        case 0x03:
            return RAMSize::KB32;
        case 0x04:
            return RAMSize::KB128;
        case 0x05:
            return RAMSize::KB64;
        default:
            std::cout<<"Unknown RAM size: "<< size_code<<"\n";
            return RAMSize::None;
    }
}


const uint32_t RamSizes[]={KB(2),KB(8),KB(32),KB(128),KB(64),0};

uint32_t GetRamSize(RAMSize size)
{
    uint32_t sz=(uint32_t)(size);
    return RamSizes[sz];
}

std::string ToString(RAMSize size)
{
    switch (size)
    {
        case RAMSize::None:
            return "No RAM";
        case RAMSize::KB2:
            return "2KB";
        case RAMSize::KB8:
            return "8KB";
        case RAMSize::KB32:
            return "32KB";
        case RAMSize::KB128:
            return "128KB";
        case RAMSize::KB64:
            return "64KB";
    }
    return "";
}

Destination GetDestination(uint8_t destination)
{
    switch (destination)
    {
        case 0x00:
            return Destination::Japanese;
        case 0x01:
            return Destination::NonJapanese;
        default:
            std::cout<<"Unknown destination: "<< destination<<"\n";
            return Destination::NonJapanese;
    }
}



std::string ToString(Destination destination) {

    switch (destination)
    {
        case Destination::Japanese:
            return "Japanese";
        case Destination::NonJapanese:
            return "Non-Japanese";
    }
    return "";
}



std::string GetTitle(uint8_t* rom)
{
    const size_t Size=0x013E - 0x0134;
    char name[Size] = {0};
    uint8_t i;
    for (i = 0; i < Size && rom[HeaderLocations::Title + i]; i++)
    {
        name[i] = static_cast<char>(rom[HeaderLocations::Title + i]);
    }
    return std::string(name,i);
}

    void CartHeader::Create(uint8_t* RomBytes)
    {
        Type=GetType(RomBytes[HeaderLocations::CartridgeTypePos]);
        ROM=GetRomSizeCode(RomBytes[HeaderLocations::RomSizePos]);
        RAM=GetRamSizeCode(RomBytes[HeaderLocations::RamSizePos]);
        HasRTC=ContainsRTC(RomBytes[HeaderLocations::CartridgeTypePos]);
        HasBattery=HasBatteryBackup(RomBytes[HeaderLocations::CartridgeTypePos]);
        Title=GetTitle(RomBytes);
    }

    void CartHeader::Dump(std::ostream& out)
    {
        out << ToString(ROM) <<"\n";
        out << ToString(Type) <<"\n";
        out << Title          <<"\n";
        out << ToString(RAM)<<"\n";
    }


    bool HasBatteryBackup(uint8_t RomTypeByte)
    {
        switch(RomTypeByte)
        {
        case 0x03:
        case 0x06:
        case 0x09:
        case 0x0D:
        case 0x0F:
        case 0x10:
        case 0x13:
        case 0x17:
        case 0x1B:
        case 0x1E:
        case 0x22:
        case 0xFD:
        case 0xFF:
            return true;
            break;
        default:
            return false;
            break;
        }
    }


    bool ContainsRTC(uint8_t RomTypeByte)
    {
        switch(RomTypeByte)
        {
        case 0x0F:
        case 0x10:
            return true;
            break;
        default:
        return false;
            break;
        }
    }
