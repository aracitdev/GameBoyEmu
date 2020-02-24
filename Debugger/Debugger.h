#ifndef DEBUGGER_H_INCLUDED
#define DEBUGGER_H_INCLUDED
#include "Breakpoint.h"
#include <exception>
#include <signal.h>
#include <sstream>
#include <bitset>
#include "../Cpu.h"
#include "../Mmu.h"
#include "../Cart.h"
#include "../Timer.h"
#include "PalleteWindow.h"

extern Cpu* CrashCPU;
extern Mmu* CrashMMU;
extern Cart* CrashCART;

void OnTerminate();

class Debugger
{
public:

    bool IsAddress(std::vector<Breakpoint>& Addressses);

    void Tick(uint32_t ticks);

    void OnBreak(void);

    void PrintPC(void);

    void Enable(Cpu* C, Mmu* M, Cart* Crt, Timer* T);

    bool StepEnabled=false;
    bool PrintLine=false;
    std::vector<Breakpoint> BreakPoints;
    std::vector<Breakpoint> EnableStepMode;
    std::vector<Breakpoint> DisableStepMode;
    PalleteWindow PWindow;

    uint64_t TotalCycles=0;
private:
    bool Enabled=false;
    Cpu* CPU;
    Mmu* MMU;
    Cart* Cartridge;
    Timer* Time;
};


#endif // DEBUGGER_H_INCLUDED
