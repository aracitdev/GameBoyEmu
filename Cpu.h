#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED
//#include "Memory.h"
#include <fstream>

#include "MemoryMap.h"
#include "Mmu.h"
#include "BitFunctions.h"
#include "Instruction/OpCodes.h"
#include "Refference.h"
#include "Instruction/OpCodeTable.h"


extern uint16_t InterruptVector[];

extern const char* IntterruptTypes[];

class Cpu
{
public:

    enum InterruptTypes
    {
        VBLANK,
        LCDSTAT,
        TIMER,
        SERIAL,
        JOYPAD
    };

    uint8_t* CpuFlags=(uint8_t*)(&AF); //flags of the cpu
    //Bits are like this:
    //  7   6   5   4   3   2   1   0
    //  Z   N   H   C   0   0   0   0
    //  Z- Zero Flag
    //  N- Subtract Flag
    //  H- Half Carry Flag
    //  C- Carry Flag

    Cpu(Mmu& m);

    void Init(void);

    void RequestInterrupt(InterruptTypes I);

    //Pair Registers
    uint16_t AF= 0x01B0;
    uint16_t BC= 0x0013;
    uint16_t DE= 0x00D8;
    uint16_t HL= 0x014D;
    ConstRef Const;
    ConditionalRef Cond;

    MemRef DeRef;

    RegRef AFRef;
    RegRef BCRef;
    RegRef DERef;
    RegRef HLRef;
    RegRef SPRef;
    RegRef PCRef;

    //Pointers to single registers
    uint8_t* A=(uint8_t*)&AF+1;
    uint8_t* F=(uint8_t*)&AF;
    RegRef ARef;
    RegRef FRef;


    uint8_t* B=(uint8_t*)&BC+1;
    uint8_t* C=(uint8_t*)&BC;

    RegRef BRef;
    RegRef CRef;

    uint8_t* D=(uint8_t*)&DE+1;
    uint8_t* E=(uint8_t*)&DE;

    RegRef DRef;
    RegRef ERef;

    uint8_t* H=(uint8_t*)&HL+1;
    uint8_t* L=(uint8_t*)&HL;


    RegRef HRef;
    RegRef LRef;

    uint16_t PC;    //program counter
    uint16_t SP=0xFFFE;    //stack pointer

    void SetZeroFlag(bool Value);
    void SetSubtractFlag(bool Value);
    void SetHalfCaryFlag(bool Value);
    void SetCarryFlag(bool Value);
    bool ZeroFlag(void);
    bool SubtractFlag(void);
    bool HalfCarryFlag(void);
    bool CarryFlag(void);

    Mmu* MMU;

    //Gets an unsigned byte from the program counter
    uint8_t GetByte(void);

    //Gets a signed byte from the program counter
    int8_t GetSignedByte(void);

    //Gets an unsigned word from the program counter
    uint16_t GetWord(void);

    MemRef* Resolve(uint16_t Address);

    //Push a Value onto the stack
    void Push(uint16_t Value);

    void HandleInterrupts(void);

    //Pop a value from the stack
    void Pop(uint16_t& Value);
    uint16_t HandleCB(void);

    Refference* ResolveValue(OperandTypes Type, OperandMem);

    uint16_t Tick(void);

    uint8_t* IntterruptsEnabled;
    uint8_t* IntterruptFlag;
    bool IEnabled=true;
    bool Halted=false;
    bool Stopped=false;

    void DumpRegisters(std::ostream& out);

    bool SaveState(std::ofstream& out);
    bool LoadState(std::ifstream& in);

    uint8_t OpCode;
    bool OpCodeCB;

private:
};

#include "TableGenerator.h"

#include "Instruction/Arithmetic.h"
#include "Instruction/Memory.h"
#include "Instruction/Control.h"
#include "OpFuncs.h"


#endif // CPU_H_INCLUDED
