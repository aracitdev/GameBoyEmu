#include "Mmu.h"

uint8_t bootDMG[256] = {
    0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
    0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
    0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
    0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
    0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
    0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
    0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
    0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
    0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
    0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
    0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
    0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
    0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
    0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
    0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x00, 0x00, 0x23, 0x7D, 0xFE, 0x34, 0x20,
    0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x00, 0x00, 0x3E, 0x01, 0xE0, 0x50
};

    void Mmu::Init(Cart* C, Gpu* G)
    {
        Crt=C;
        DivWritten=false;
        GPU=G;
        BootRomEnabled = HardwareRegisters + 0x50;
    }

    uint8_t Mmu::Read(uint16_t Address)
    {
        if(*BootRomEnabled != 0x01 && Address < 0x100)
        {
            return bootDMG[Address];
        }
        else
        if(Address <= MemoryMap::CartBankXEnd || (Address >= MemoryMap::CartRamStart && Address <= MemoryMap::CartRamEnd))
        {
            return Crt->Read(Address);
        }
        else
        if(Address >= MemoryMap::IntRam0Start && Address <= MemoryMap::IntRamXEnd)
        {
            return InternalRam[Address - MemoryMap::IntRam0Start];
        }
        else
        if(Address >= MemoryMap::EchoStart && Address <=MemoryMap::EchoEnd)
        {
            return InternalRam[Address - MemoryMap::EchoStart];
        }
        else
        if(Address >= MemoryMap::HardwareRegsStart && Address <= MemoryMap::HardwareRegsEnd)
        {
            return HardwareRegisters[Address - MemoryMap::HardwareRegsStart];
        }
        else
        if(Address >= MemoryMap::ZeroPage && Address <= 0xFFFF)
        {
            return Zero[Address - MemoryMap::ZeroPage];
        }
        else
        if( (Address >= MemoryMap::CRamStart && Address <= MemoryMap::MapsEnd) || (Address >= MemoryMap::OemStart && Address <= MemoryMap::OemEnd))
        {
            return GPU->Read(Address);
        }
        std::cout <<"Failed.\n";
        return 0;
    }

    void Mmu::Write(uint16_t Address, uint8_t Value)
    {

        if(Address == 0xFF04)
            DivWritten=true;
        if(Address <= MemoryMap::CartBankXEnd)
        {
            Crt->Write(Address, Value);
        }
        else
        if(Address >= MemoryMap::IntRam0Start && Address <= MemoryMap::IntRam0End)
        {
            InternalRam[Address - MemoryMap::IntRam0Start]=Value;
        }
        else
        if(Address >= MemoryMap::CartRamStart && Address <= MemoryMap::CartRamEnd)
        {
            Crt->Write(Address, Value);
        }
        else
        if(Address >= MemoryMap::EchoStart && Address <=MemoryMap::EchoEnd)
        {
            InternalRam[Address - MemoryMap::EchoStart]=Value;
        }
        else
        if(Address >= MemoryMap::HardwareRegsStart && Address <= MemoryMap::HardwareRegsEnd)
        {
            HardwareRegisters[Address - MemoryMap::HardwareRegsStart]=Value;
            if(Address == 0xFF46)
                GPU->DmaTransferStarted=true;
        }
        else
        if(Address >= MemoryMap::ZeroPage && Address <= 0xFFFF)
        {
            Zero[Address - MemoryMap::ZeroPage]=Value;
        }
        else
        if((Address >= MemoryMap::CRamStart && Address <= MemoryMap::MapsEnd) || (Address >= MemoryMap::OemStart && Address <= MemoryMap::OemEnd))
        {
            GPU->Write(Address, Value);
        }
    }


    uint8_t* Mmu::GetPointer(uint16_t Address)
    {

        if(*BootRomEnabled != 0x01 && Address < 0x100)
        {
            return &(bootDMG[Address]);
        }
        else
        if(Address <= MemoryMap::CartBankXEnd)
        {
            return Crt->GetPointer(Address);
        }
        else
        if(Address >= MemoryMap::IntRam0Start && Address <= MemoryMap::IntRam0End)
        {
            return &(InternalRam[Address - MemoryMap::IntRam0Start]);
        }
        else
        if(Address >= MemoryMap::CartRamStart && Address <= MemoryMap::CartRamEnd)
        {
            return Crt->GetPointer(Address);
        }
        else
        if(Address >= MemoryMap::EchoStart && Address <=MemoryMap::EchoEnd)
        {
            return &(InternalRam[Address - MemoryMap::EchoStart]);
        }
        else
        if(Address >= MemoryMap::HardwareRegsStart && Address <= MemoryMap::HardwareRegsEnd)
        {
            return &(HardwareRegisters[Address - MemoryMap::HardwareRegsStart]);
        }
        else
        if(Address >= MemoryMap::ZeroPage && Address <= 0xFFFF)
        {
            return &(Zero[Address - MemoryMap::ZeroPage]);
        }
        else
        if((Address >= MemoryMap::CRamStart && Address <= MemoryMap::MapsEnd ) || (Address >= MemoryMap::OemStart && Address <= MemoryMap::OemEnd))
        {
            return GPU->GetPointer(Address);
        }
        return 0;
    }


    bool Mmu::SaveState(std::ofstream& out)
    {
        out.write((const char*)InternalRam, MemoryMap::IntRam0Size);
        out.write((const char*)HardwareRegisters, MemoryMap::HardwareRegsSize);
        out.write((const char*)Zero, 0xFFFF - 0xFF80);
        out.write((const char*)Unusable, 0xFEFF-0xFEA0);
        out.write((const char*)(&DivWritten), sizeof(DivWritten));
        return true;
    }

    bool Mmu::LoadState(std::ifstream& in)
    {
        in.read((char*)InternalRam, MemoryMap::IntRam0Size);
        in.read((char*)HardwareRegisters, MemoryMap::HardwareRegsSize);
        in.read((char*)Zero, 0xFFFF - 0xFF80);
        in.read((char*)Unusable, 0xFEFF - 0xFEA0);
        in.read((char*)(&DivWritten), sizeof(DivWritten));
        return true;
    }
