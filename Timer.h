/**
 * \file Timer.h
 * \author Sean C
 * \version 1.0
 * Controls the timing of the gameboy clock register and TIMA register
 */


#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include "Mmu.h"

/**
 * \class Timer
 * Provides timer functions for the gameboy, updating TIMA
 * and other registers based on the number of clock ticks.
 */

class Timer
{
public:
/**
 * \fn void Init(Mmu* MMu)
 * \param MMu A pointer to the memory management unit.
 * Initializes the Timer and its registers from the MMU.
 */

    void Init(Mmu* MMu);

/**
 * \fn void Tick(uint32_t Cycles)
 * \param Cycles the number of cycles that ticked since the last call
 * Ticks the timer, updating the timer registers
 */
    void Tick(uint32_t Cycles);

/**
 * \fn bool SaveState(std::ofstream& out)
 * \param out The stream to save the data to.
 * \return Returns true on success, false on failure.
 * Saves the current state of the timer (excluding registers, which are already saved by the MMU)
 */
    bool SaveState(std::ofstream& out);

/**
 * \fn bool LoadState(std::ifstream& in)
 * \param in The stream to load from.
 * \return Returns true on success, false on failure.
 * Loads the current state of the timer (excluding registers, which area already loaded by the MMU)
 */
    bool LoadState(std::ifstream& in);


/**
 * \fn uint16_t GetClocks(void)
 * \return The number of current clocks on the global timer
 * Returns the number of clocks on the global timer, used for getting TIMA and other register values.
 */
    uint16_t GetClocks(void);
private:

    const uint32_t CPUClockCyclesHz = 4194304;
    const uint32_t LockedClockCycleHz = 16384;
    const float CPUCyclesToLockedCycles = LockedClockCycleHz / CPUClockCyclesHz;

    uint32_t ClockCycles[4] = {4096, 262144 , 65536 , 16384};
    uint8_t TimaBit[4]={9,7,3,5};   //the bit to check change for to increase TIMA
    float CPUConversionTable[4];


    uint32_t GlobalTimerValue;  /**<Total clocks on the timer register*/
    uint8_t LastTimeConfig; /**<The last value of the timer configuration register, used to detect if the TimaBit goes from high to low*/
    bool ShouldTimaReset=false;   /**<should TIMA reset to the mod next cycle*/

    uint32_t TimaClocks;    /**<TimaClock*/
    uint32_t DivClocks;     /**<DivClock*/

    Mmu* MMU;
};

#endif // TIMER_H_INCLUDED
