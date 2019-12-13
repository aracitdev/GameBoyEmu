#include "Memory.h"

bool LD(Cpu* C, OpCodeEntry* Op)
{
    Refference* To=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* From=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    To->Set(From->Get());
    return true;
}

bool LDSPHL(Cpu* C, OpCodeEntry* Op)
{
    Refference* To=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* From=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    uint8_t UValue=From->Get();
    int8_t Value=*((int8_t*)&UValue);
    uint16_t StackValue=C->SP;
    int Result = (int)(StackValue + Value);
    C->SetZeroFlag(false);
    C->SetSubtractFlag(false);
    C->SetHalfCaryFlag(((StackValue ^ Value ^ (Result & 0xFFFF)) & 0x10) == 0x10);
    C->SetCarryFlag(((StackValue ^ Value ^ (Result & 0xFFFF)) & 0x100) == 0x100);
    To->Set((uint16_t)(Value + StackValue));
    return true;
}

bool LDW(Cpu* C, OpCodeEntry* Op)
{
    Refference* To=C->ResolveValue(Op->Types[0],Op->Dir[0]);
    Refference* From=C->ResolveValue(Op->Types[1],Op->Dir[1]);
    To->Set(From->Get16());
    return true;
}

bool PUSH(Cpu* C, OpCodeEntry* Op)
{
    Refference* From=C->ResolveValue(Op->Types[0],Op->Dir[0]);
    C->Push(From->Get16());
    return true;
}

bool POP(Cpu* C, OpCodeEntry* Op)
{
    Refference* To=C->ResolveValue(Op->Types[0],Op->Dir[0]);
    uint16_t Value;
    C->Pop(Value);
    To->Set(Value);
    return true;
}

bool SCF(Cpu* C, OpCodeEntry* Op)
{
    C->SetCarryFlag(true);
    C->SetHalfCaryFlag(false);
    C->SetSubtractFlag(false);
    return true;
}

bool LDH(Cpu* C, OpCodeEntry* Op)
{
    Refference* To=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* From=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    To->Set(From->Get());
    return true;
}

bool LDD(Cpu* C, OpCodeEntry* Op)
{
    Refference* To=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* From=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    To->Set(From->Get());
    (C->HL)--;
    return true;
}

bool LDI(Cpu* C, OpCodeEntry* Op)
{
    Refference* To=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* From=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    To->Set(From->Get());
    (C->HL)++;
    return true;
}
