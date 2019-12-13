#ifndef GAMEBOY_H_INCLUDED
#define GAMEBOY_H_INCLUDED

#include "Cart.h"
#include "Cpu.h"
#include "Gpu.h"
#include "Mmu.h"
#include "Debugger/Debugger.h"
#include "Timer.h"
#include "Input.h"
#include "Apu.h"

class GameBoy
{
public:

    GameBoy();

    bool Init(uint8_t* RomData, size_t Size,sf::RenderWindow& W);

    void UpdateSpeed(void);

    void StartWithBootDMG(bool enabled);


    void Run(void);

    Debugger ProgramDebugger;
    Cpu CPU;
    Gpu GPU;
    Mmu MMU;
    Apu APU;
    Timer Time;
    Cart* Cartridge;
    sf::RenderWindow* Window;
    Input In;
    float SpeedMultiplier;
private:
};


#endif // GAMEBOY_H_INCLUDED
