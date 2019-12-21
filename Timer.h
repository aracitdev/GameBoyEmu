#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include "Mmu.h"


class Timer
{
public:

    void Init(Mmu* MMu);

    void HandleLockedTimer(uint32_t Cycles);

    void HandleTIMA(uint32_t Cycles);

    void Tick(uint32_t Cycles);

    bool SaveState(std::ofstream& out);
    bool LoadState(std::ifstream& in);

private:

    const uint32_t CPUClockCyclesHz = 4194304;
    const uint32_t LockedClockCycleHz = 16384;
    const float CPUCyclesToLockedCycles = LockedClockCycleHz / CPUClockCyclesHz;

    uint32_t ClockCycles[4] = {4096, 262144, 65536, 16384};
    uint8_t TimaBit[4]={9,7,3,5};   //the bit to check change for to increase TIMA
    //float ConversionTable[4] = {4096.0f / CPUClockCyclesHz, 262144.0f / CPUClockCyclesHz, 65536.0f / CPUClockCyclesHz, 16384.0f / CPUClockCyclesHz};
    float CPUConversionTable[4];


    uint32_t GlobalTimerValue;  //TOTAL CLOCKS
    uint8_t LastTimeConfig;
    bool ShouldTimaReset=false;   //should TIMA reset to the mod next cycle

    Mmu* MMU;
};

#endif // TIMER_H_INCLUDED
