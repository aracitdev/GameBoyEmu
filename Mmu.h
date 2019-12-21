#ifndef MMU_H_INCLUDED
#define MMU_H_INCLUDED
#include "MemoryMap.h"
#include "Cart.h"
#include "Gpu.h"

class Gpu;
extern uint8_t bootDMG[];

class Mmu
{
    public:

    void Init(Cart* C, Gpu* G);

    uint8_t Read(uint16_t Address);

    void Write(uint16_t Address, uint8_t Value);

    uint8_t* GetPointer(uint16_t Address);


    bool SaveState(std::ofstream& out);
    bool LoadState(std::ifstream& in);

    uint8_t InternalRam[MemoryMap::IntRam0Size * 8];
    uint8_t HardwareRegisters[MemoryMap::HardwareRegsSize];
    uint8_t Zero[0xFFFF - 0xFF80];
    uint8_t Unusable[0xFEFF-0xFEA0];
    Cart* Crt;
    Gpu* GPU;
    bool DivWritten;
    uint8_t* BootRomEnabled;

    private:
};

#endif // MMU_H_INCLUDED
