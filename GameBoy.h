#ifndef GAMEBOY_H_INCLUDED
#define GAMEBOY_H_INCLUDED
#include <fstream>
#include <string>

#include "Cart.h"
#include "Cpu.h"
#include "Gpu.h"
#include "Mmu.h"
#include "Debugger/Debugger.h"
#include "Timer.h"
#include "Apu.h"
#include "ConfigLoader.h"

class GameBoy
{
public:

    GameBoy();
    ~GameBoy();

    void UpdateWindowView(void);

    bool Init(uint8_t* RomData, size_t Size,sf::RenderWindow& W, const std::string&);

    void UpdateSpeed(void);

    void StartWithBootDMG(bool enabled);

    bool SaveState(const std::string& filename);
    bool LoadState(const std::string& filename);

    void Run(void);

    sf::View* GameView;

    Debugger ProgramDebugger;
    Cpu CPU;
    Gpu GPU;
    Mmu MMU;
    Apu APU;
    Timer Time;
    ConfigLoader Config;
    Cart* Cartridge;
    sf::RenderWindow* Window;
    float SpeedMultiplier;
    uint8_t currentState;
    std::string fileName;
private:
};


#endif // GAMEBOY_H_INCLUDED
