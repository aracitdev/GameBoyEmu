#include "Timer.h"

void Timer::Init(Mmu* MMu)
{
    MMU=MMu;
    GlobalTimerValue=0;
    MMU->HardwareRegisters[0x04]=0;
    MMU->HardwareRegisters[0x05]=0; //TIMA reset
    std::cout <<"Init with " <<GlobalTimerValue<<" "<<(uint16_t)(MMU->HardwareRegisters[0x04])<<"\n";
    LastTimeConfig=MMU->HardwareRegisters[0x07];
    ShouldTimaReset=false;
    for(uint32_t counter=0; counter < 4; counter++)
        CPUConversionTable[counter]= (float)(CPUClockCyclesHz) / (float)(ClockCycles[counter]);

    std::stringstream ss;
    for(uint32_t counter=0; counter <4; counter++)
        ss << CPUConversionTable[counter] <<" clock type " <<counter<<"\n";
    Debug.Log(ss.str().c_str(), DebugLog::Debug, "Timer.h");
}

void Timer::Tick(uint32_t Cycles)
{

    uint32_t LastGlobal = GlobalTimerValue; //are last global timer before we add cycles
    if(ShouldTimaReset)
    {
        MMU->HardwareRegisters[0x05]=MMU->HardwareRegisters[0x06]; //on overflow, it sets to TMA
        SetBit(true, MMU->HardwareRegisters[0x0F], 2);
        ShouldTimaReset=false;
    }
    if(MMU->DivWritten)   //was div set?
    {
        GlobalTimerValue=0;             //reset the global clock value
        MMU->HardwareRegisters[0x04]=0;
        MMU->DivWritten=false; //NOTE: There was a bug here, when resetting the div register
                               //the number of clocks from instruction to reset it should be added
    }

    GlobalTimerValue+=Cycles;   //tick for cycles
    GlobalTimerValue= GlobalTimerValue % 0xFF00;
    MMU->HardwareRegisters[0x04] = (GlobalTimerValue & 0xFF00)>>8;   //div is equal to the upper 8 bits of the cycles 16
    uint8_t TimeConfig=MMU->HardwareRegisters[0x07];    //the current time configuration
    uint8_t ConverseNumber=TimeConfig & 0x03;   //the timer type
    uint8_t LastConverse = LastTimeConfig & 0x03;   //the last timer type
    uint8_t LastBit = TimaBit[LastConverse];    //the bit to be checked for last timer type falling edge
    uint8_t BitCheck = TimaBit[ConverseNumber]; //check for a falling edge on this bit
    bool WasOn = Bit(LastTimeConfig, 2) && Bit(LastGlobal,LastBit); //was it on before
    bool IsOn = Bit(TimeConfig, 2) && Bit(GlobalTimerValue, BitCheck);  //is it on now?
    if((WasOn && !IsOn) /*|| (Bit(TimeConfig,2) && Bit(LastGlobal,LastBit) == 0 &&
                                Bit(GlobalTimerValue,BitCheck) == 1 && Bit(LastTimeConfig,2) ==0) */) //falling edge detector
    {
        //was it on and is it not on now
        uint16_t TIMAV=MMU->HardwareRegisters[0x05]; //we got a falling edge
        TIMAV++;
        if(TIMAV > 0xFF)   //set it to interrupt next cycle
        {
            ShouldTimaReset = true;
            TIMAV=0xFF;    //when this happens, it is zero for a cycle
        }
        MMU->HardwareRegisters[0x05] = TIMAV;
    }
    LastTimeConfig = TimeConfig;
}

uint16_t Timer::GetClocks(void)
{
    return (GlobalTimerValue);
}


bool Timer::SaveState(std::ofstream& out)
{
    out.write((const char*)(&GlobalTimerValue), sizeof(GlobalTimerValue));
    out.write((const char*)(&LastTimeConfig),sizeof(LastTimeConfig));
    out.write((const char*)(&ShouldTimaReset), sizeof(ShouldTimaReset));
    return true;
}

bool Timer::LoadState(std::ifstream& in)
{
    in.read((char*)(&GlobalTimerValue), sizeof(GlobalTimerValue));
    in.read((char*)(&LastTimeConfig),sizeof(LastTimeConfig));
    in.read((char*)(&ShouldTimaReset), sizeof(ShouldTimaReset));
    return true;
}
