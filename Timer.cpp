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
    DivClocks+=Cycles;
    while(Cycles >= 256 * 4)    //my timing is based around 4 ticks = 1 cycles
    {
        DivClocks-=Cycles;
        uint8_t Div = MMU->Read(0xFF04);
        Div++;
        MMU->Write(0xFF04, Div);
    }

    uint8_t Tac=MMU->Read(0xFF07);
    if(Tac & 0x04)
    {
        TimaClocks+=Cycles;
        uint32_t Freq = ClockCycles[Tac & 0x03];
        while(TimaClocks >= Freq)
        {
            TimaClocks-=Freq;
            uint8_t Tima = MMU->Read(0xFF05);
            if(Tima == 0xFF)
            {
                Tima = MMU->Read(0xFF06);
                SetBit(true, MMU->HardwareRegisters[0x0F], 2);  //request interrupt
            }
            else
                Tima++;
            MMU->Write(0xFF05, Tima);
        }
    }
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
