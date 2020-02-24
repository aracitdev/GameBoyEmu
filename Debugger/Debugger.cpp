#include "Debugger.h"


Cpu* CrashCPU;
Mmu* CrashMMU;
Cart* CrashCART;

void OnTerminate()
{
    std::stringstream ss;
    ss<<"Crash at: ";
    GetHex(CrashCPU->PC, ss);
    ss <<"\n";
    if(CrashCPU->OpCodeCB)
        Inverse(CBCodes[CrashCPU->OpCode], ss);
    else
        Inverse(OpCodes[CrashCPU->OpCode], ss);
    ss<<"\n";
    CrashCPU->DumpRegisters(ss);
    ss << "SCROLL Y " <<(uint32_t)CrashMMU->HardwareRegisters[0x42]<<"\n";
    Debug.Log(ss.str().c_str(), DebugLog::Debug, "Debugger.h");
    system("pause");
    int i=1;
    int i2=0;
    int i3=i/i2;    //force a crash
    i3++;
}

bool Debugger::IsAddress(std::vector<Breakpoint>& Addressses)
{
    for(uint32_t counter=0; counter<Addressses.size(); counter++)
        if(Addressses[counter].Address == CPU->PC)
            return true;
    return false;
}

void Debugger::Tick(uint32_t ticks)
{
    TotalCycles+=ticks;
    if(!Enabled)
        return;
    PWindow.Update();
    if(IsAddress(BreakPoints))
        OnBreak();
    if(IsAddress(EnableStepMode))
        StepEnabled=true;
    if(IsAddress(DisableStepMode))
        StepEnabled=false;
    if(StepEnabled)
        OnBreak();
    else if(PrintLine)
        PrintPC();
}

void Debugger::OnBreak(void)
{
    std::stringstream ss;
    ss<<"Breakpoint at: ";
    GetHex(CPU->PC, ss);
    ss <<"\n";
    ss<<"OP:";
    GetHex(CPU->OpCode, ss);
    ss<<"\n";
    if(CPU->OpCodeCB)
        Inverse(CBCodes[CPU->OpCode], ss);
    else
        Inverse(OpCodes[CPU->OpCode], ss);
    ss<<"\n";
    ss << "DIV " <<(uint32_t)MMU->HardwareRegisters[0x04] <<" TIMA " <<(uint32_t)MMU->HardwareRegisters[0x05]<<"\n";
    ss << "Clocks " <<std::bitset<16>(Time->GetClocks())<<"\n";
    ss << "Total cycles " <<TotalCycles<<"\n";
    CPU->DumpRegisters(ss);
    Debug.Log(ss.str().c_str(), DebugLog::Debug, "Debugger.h");
    system("pause");
}

void Debugger::PrintPC(void)
{
    std::stringstream ss;
    ss <<"PC: ";
    GetHex(CPU->PC,ss);
    ss <<" B: " << (uint16_t)(((MBC1*)Cartridge)->CurrentRomBank) <<" ";
    Inverse(OpCodes[CPU->OpCode], ss);
    ss <<" AF ";
    GetHex(CPU->AF,ss);
    ss <<" BC ";
    GetHex(CPU->BC,ss);
    ss <<" DE ";
    GetHex(CPU->DE,ss);
    ss <<" HL ";
    GetHex(CPU->HL, ss);
    ss <<" SP ";
    GetHex(CPU->SP,ss);
    Debug.Log(ss.str().c_str(), DebugLog::Info, "Debugger.h");
}

void Debugger::Enable(Cpu* C, Mmu* M, Cart* Crt, Timer* T)
{
    CPU=C;
    MMU=M;
    Cartridge=Crt;
    CrashCPU=CPU;
    CrashMMU=MMU;
    CrashCART=Cartridge;
    Time=T;
    std::set_terminate(OnTerminate);
    PWindow.Init(M);
    PWindow.SetEnabled(true);
    Enabled=true;
}
