#include "Cpu.h"

uint16_t InterruptVector[]=
{
    0x40,
    0x48,
    0x50,
    0x58,
    0x60
};


const char* IntterruptTypes[]=
{
    "VBLANK","LCDSTAT","TIMER","SERIAL","JOYPAD"
};

void Cpu::Init(void)
{
    IntterruptFlag=MMU->GetPointer(0xFF0F);
    IntterruptsEnabled=MMU->GetPointer(0xFFFF);
    *IntterruptsEnabled=0x00;
}

Cpu::Cpu(Mmu& m)  : Const(0, &m), Cond(0, &m), DeRef(0, &m), AFRef(AF, &m), BCRef(BC, &m), DERef(DE, &m), HLRef(HL, &m), SPRef(SP, &m), PCRef(PC, &m),
                  ARef(*A, &m), FRef(*CpuFlags, &m), BRef(*B, &m), CRef(*C, &m), DRef(*D, &m), ERef(*E,&m), HRef(*H, &m),
                  LRef(*L, &m)
{
     MMU=&m;
}

void Cpu::SetZeroFlag(bool Value)
{
    SetBit(Value, *CpuFlags, 7);
}

void Cpu::SetSubtractFlag(bool Value)
{
    SetBit(Value, *CpuFlags, 6);
}

void Cpu::SetHalfCaryFlag(bool Value)
{
    SetBit(Value, *CpuFlags, 5);
}

void Cpu::SetCarryFlag(bool Value)
{
    SetBit(Value, *CpuFlags, 4);
}

bool Cpu::ZeroFlag(void)
{
    return Bit(*CpuFlags, 7);
}

bool Cpu::SubtractFlag(void)
{
    return Bit(*CpuFlags, 6);
}

bool Cpu::HalfCarryFlag(void)
{
    return Bit(*CpuFlags,5);
}

bool Cpu::CarryFlag(void)
{
    return Bit(*CpuFlags, 4);
}

uint8_t Cpu::GetByte(void)
{
    uint8_t ReturnV= MMU->Read(PC);
    PC++;
    return ReturnV;
}

int8_t Cpu::GetSignedByte(void)
{
    uint8_t Byte=GetByte();
    return *((int8_t*) (&Byte));
}

uint16_t Cpu::GetWord(void)
{
    uint16_t Low=GetByte();
    uint16_t High=GetByte();
    return (High << 8) + Low;
}

MemRef* Cpu::Resolve(uint16_t Address)
{
    return new MemRef(Address, MMU);
}

void Cpu::Push(uint16_t Value)
{
    SP--;
    uint8_t High=(Value >> 8) & 0xff;
    MMU->Write(SP, High);
    SP--;
    uint8_t Low =Value & 0xff;
    MMU->Write(SP, Low);
}

void Cpu::Pop(uint16_t& Value)
{
    uint16_t Low=MMU->Read(SP);
    SP++;
    uint16_t High=MMU->Read(SP);
    SP++;
    Value=(High << 8) | Low;
}

Refference* Cpu::ResolveValue(OperandTypes Type, OperandMem Mem)
{
    Refference* ReturnV=nullptr;
    switch(Type)
    {
    case OperandTypes::Immediate8:
        Const.Set(GetByte());
        ReturnV= &Const;
        break;
    case OperandTypes::Address8:
        Const.Set((uint16_t)((uint16_t)GetByte() + (uint16_t)0xFF00));
        ReturnV= &Const;
        break;
    case OperandTypes::ImmediateS8:
        Const.Set(GetByte());
        ReturnV= &Const;
        break;
    case OperandTypes::A:
        ReturnV= &ARef;
        break;
    case OperandTypes::B:
        ReturnV= &BRef;
        break;
    case OperandTypes::C:
        ReturnV= &CRef;
        break;
    case OperandTypes::D:
        ReturnV= &DRef;
        break;
    case OperandTypes::E:
        ReturnV= &ERef;
        break;
    case OperandTypes::F:
        ReturnV= &FRef;
        break;
    case OperandTypes::AF:
        ReturnV= &AFRef;
        break;
    case OperandTypes::BC:
        ReturnV= &BCRef;
        break;
    case OperandTypes::DE:
        ReturnV= &DERef;
        break;
    case OperandTypes::HL:
        ReturnV= &HLRef;
        break;
    case OperandTypes::SP:
        ReturnV= &SPRef;
        break;
    case OperandTypes::PC:
        ReturnV= &PCRef;
        break;
    case OperandTypes::H:
        ReturnV= &HRef;
        break;
    case OperandTypes::L:
        ReturnV= &LRef;
        break;
    case OperandTypes::Immediate16:
        Const.Set(GetWord());
        ReturnV= &Const;
        break;
    case OperandTypes::Address16:
        Const.Set(GetWord());
        ReturnV= &Const;
        break;
    case OperandTypes::CC:
        Cond.Set((uint8_t)(CarryFlag() ? 1 : 0));
        ReturnV= &Cond;
        break;
    case OperandTypes::CNC:
        Cond.Set((uint8_t)(CarryFlag() ? 0 : 1));
        ReturnV= &Cond;
        break;
    case OperandTypes::CZ:
        Cond.Set((uint8_t)(ZeroFlag() ? 1 : 0));
        ReturnV= &Cond;
        break;
    case OperandTypes::CNZ:
        Cond.Set((uint8_t)(ZeroFlag() ? 0 : 1));
        ReturnV= &Cond;
        break;
    case OperandTypes::None:
        return nullptr;
        break;
    }
    if(Mem == OperandMem::Indirected)
    {
        if(OperandTypes::A <= Type)
            DeRef.SetAddress((uint16_t)ReturnV->Get() + 0xFF00);
        else
            DeRef.SetAddress(ReturnV->Get16());
        return &DeRef;
    }
    return ReturnV;
}


uint16_t Cpu::Tick(void)
{
    //std::cout <<"Tick.\n";
    uint16_t ReturnV=0;
    *CpuFlags = *CpuFlags & 0xF0;
    HandleInterrupts();
    if(!Halted)
    {
        OpCode=GetByte();
        if(OpCode == 0xCB)
        {
            OpCodeCB=true;
            return HandleCB();
        }
        OpCodeCB=false;
        OpCodeEntry& Op=OpCodes[OpCode];
        bool ReturnV=OperationList[(uint8_t)Op.Operation](this, &Op);
        return  ReturnV ? Op.BranchedCycles : Op.Cycles;
    }
    return 4;
}

uint16_t Cpu::HandleCB(void)
{
    OpCode=GetByte();
    OpCodeEntry& Op=CBCodes[OpCode];
    //Inverse(Op, std::cout); std::cout<<"\n";
    if(OperationList[(uint8_t)Op.Operation](this, &Op))
        return Op.BranchedCycles + 4;
    else
        return Op.Cycles + 4;
}

void Cpu::HandleInterrupts(void)
{
    uint8_t Interrupt= *IntterruptFlag & *IntterruptsEnabled;
    if(!Interrupt)  //if an interrupt has not been requested thats enabled
        return;     //we return
    Halted=false;
    if(!IEnabled)
        return;
    for(uint8_t counter=0; counter<5; counter++)
        if(Bit(Interrupt, counter))
        {
            SetBit(false,*IntterruptFlag, counter);
            Push(PC);
            PC=InterruptVector[counter];
            IEnabled=false;
            return;
        }
}

void Cpu::DumpRegisters(std::ostream& out)
{
    out <<"AF: "; GetHex(AF,out);
    out <<"\nBC: "; GetHex(BC,out);
    out <<"\nDE: "; GetHex(DE, out);
    out <<"\nHL: "; GetHex(HL, out);
    out <<"\nSP: "; GetHex(SP, out);
    out <<"\nPC: "; GetHex(PC, out);
    out <<"Z: " <<ZeroFlag() <<"N: " <<SubtractFlag() << " H: "<<HalfCarryFlag() <<" C: " <<CarryFlag();
    out <<"\n";
}

void Cpu::RequestInterrupt(InterruptTypes I)
{
    SetBit(true, *IntterruptFlag, uint8_t(I));
}
