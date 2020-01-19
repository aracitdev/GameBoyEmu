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

bool Cart::SaveState(std::ofstream& out)
{
    if(Ram)
        out.write((const char*)Ram, RamSize);
    return true;
}

bool Cart::LoadState(std::ifstream& in)
{
    if(Ram)
        in.read((char*)Ram, RamSize);
    return true;
}

Cart::~Cart()
{
    if(Ram)
    {
        delete[] Ram;
    }
    Ram=nullptr;
    if(Rom)
        delete[] Rom;
    Rom=nullptr;
}

void Cart::SaveRam(std::ofstream& out)
{
    out.write((const char*)Ram, RamSize);
}

void Cart::LoadRam(std::ifstream& in)
{
    in.read((char*)Ram, RamSize);
}

bool Cart::ContainsSRAM(void)
{
    return Ram != nullptr;
}
