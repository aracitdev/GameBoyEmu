#include "Arithmetic.h"

bool CheckSubHalfCarry(uint8_t a, uint8_t b)
{
    return (((a & 0xF) - (b & 0xF))) < 0;
}

bool CheckAddHalfCarry(uint8_t a, uint8_t b)
{
    return (((a & 0xf) + (b & 0xf)) & 0x10) == 0x10;
}

bool CheckWAddHalfCarry(uint16_t a, uint16_t b, uint16_t r)
{
    return (a ^ b ^ (r & 0xFFFF)) & 0x1000;
}

bool INC(Cpu* C, OpCodeEntry* Op)
{
    Refference* Ref=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t Value=Ref->Get();
    C->SetHalfCaryFlag(CheckAddHalfCarry(Value, 1));
    Value++;
    Ref->Set(Value);
    C->SetZeroFlag(Value == 0);
    C->SetSubtractFlag(false);
    return true;
}

bool DEC(Cpu* C, OpCodeEntry* Op)
{
    Refference* Ref=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t Value=Ref->Get();
    C->SetHalfCaryFlag(CheckSubHalfCarry(Value,1));
    Value--;
    Ref->Set(Value);
    C->SetZeroFlag(Value == 0);
    C->SetSubtractFlag(true);
    return true;
}

bool INCW(Cpu* C, OpCodeEntry* Op)
{
    Refference* Ref=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint16_t Value=Ref->Get16();
    Value++;
    Ref->Set(Value);
    return true;
}


bool DECW(Cpu* C, OpCodeEntry* Op)
{
    Refference* Ref=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint16_t Value=Ref->Get16();
    Value--;
    Ref->Set(Value);
    return true;
}

//this one is only used with HL
bool ADDW(Cpu* C, OpCodeEntry* Op)
{
    Refference* ORef=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* Ref=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    uint16_t Value1=ORef->Get16();
    uint16_t Value2=Ref->Get16();
    uint32_t ValueO= Value1 + Value2;
    C->SetSubtractFlag(false);
    C->SetHalfCaryFlag(CheckWAddHalfCarry(Value1, Value2, ValueO));
    C->SetCarryFlag((ValueO & 0x10000) != 0);
    ORef->Set((uint16_t)ValueO);
    return true;
}

bool ADDWS(Cpu* C, OpCodeEntry* Op)
{
    Refference* ORef=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* Ref=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    uint16_t Value1=ORef->Get16();
    uint8_t Value2f=Ref->Get();
    int8_t Value2=*((int8_t*)&Value2f);
    int Result= Value1 + Value2;
    C->SetZeroFlag(false);
    C->SetSubtractFlag(false);
    C->SetHalfCaryFlag(((Value1 ^ Value2 ^ (Result & 0xFFFF)) & 0x10) == 0x10);
    C->SetCarryFlag(((Value1 ^ Value2 ^ (Result & 0xFFFF)) & 0x100) == 0x100);
    ORef->Set((uint16_t)Result);
    return true;
}

bool ADD(Cpu* C, OpCodeEntry* Op)
{
    Refference* ORef=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* Ref=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    uint8_t Value1=ORef->Get();
    uint8_t Value2=Ref->Get();
    uint16_t ValueO=Value1+Value2;
    ORef->Set((uint8_t)(ValueO));
    C->SetZeroFlag((uint8_t)ValueO == 0);
    C->SetSubtractFlag(false);
    C->SetHalfCaryFlag(CheckAddHalfCarry(Value1, Value2));
    C->SetCarryFlag(ValueO > 255);

    return true;
}

bool SUB(Cpu* C, OpCodeEntry* Op)
{
    Refference* ORef=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* Ref=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    uint8_t Value1=ORef->Get();
    uint8_t Value2=Ref->Get();
    uint16_t ValueO=Value1-Value2;
    ORef->Set((uint8_t)ValueO);
    C->SetZeroFlag((uint8_t)ValueO == 0);
    C->SetSubtractFlag(true);
    C->SetHalfCaryFlag(CheckSubHalfCarry(Value1, Value2));
    C->SetCarryFlag(Value2 > Value1);
    return true;
}

bool XOR(Cpu* C, OpCodeEntry* Op)
{
    Refference* ORef=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* Ref=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    uint8_t Value1=ORef->Get();
    uint8_t Value2=Ref->Get();
    uint8_t ValueO=Value1 ^ Value2;
    ORef->Set(ValueO);
    C->SetZeroFlag(ValueO == 0);
    C->SetSubtractFlag(false);
    C->SetHalfCaryFlag(false);
    C->SetCarryFlag(false);
    return true;
}


bool AND(Cpu* C, OpCodeEntry* Op)
{
    Refference* ORef=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* Ref=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    uint8_t Value1=ORef->Get();
    uint8_t Value2=Ref->Get();
    uint16_t ValueO=Value1 & Value2;
    ORef->Set((uint8_t)ValueO);
    C->SetZeroFlag(ValueO == 0);
    C->SetSubtractFlag(false);
    C->SetHalfCaryFlag(true);
    C->SetCarryFlag(false);
    return true;
}


bool OR(Cpu* C, OpCodeEntry* Op)
{
    Refference* ORef=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* Ref=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    uint8_t Value1=ORef->Get();
    uint8_t Value2=Ref->Get();
    uint16_t ValueO=Value1 | Value2;
    ORef->Set((uint8_t)ValueO);
    C->SetZeroFlag(ValueO == 0);
    C->SetSubtractFlag(false);
    C->SetHalfCaryFlag(false);
    C->SetCarryFlag(false);
    return true;
}

bool RST(Cpu* C, OpCodeEntry* Op)
{
    C->Push(C->PC);
    C->PC=Op->Ex;
    return true;
}

bool ADC(Cpu* C, OpCodeEntry* Op)
{
    Refference* ORef=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* Ref=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    uint8_t Value1=ORef->Get();
    uint8_t Value2=Ref->Get();
    uint16_t Carry=C->CarryFlag() ? 1 : 0;
    uint8_t ValueO=Value1 + Value2 + Carry;
    unsigned int ValueOF=Value1 + Value2 + Carry;
    ORef->Set((uint8_t)ValueO);
    C->SetZeroFlag(ValueO == 0);
    C->SetSubtractFlag(false);
    C->SetHalfCaryFlag(((Value1 & 0xf) + (Value2 & 0xf) + Carry) > 0xf);
    C->SetCarryFlag(ValueOF > 0xff);
    return true;
}


bool SBC(Cpu* C, OpCodeEntry* Op)
{
    Refference* ORef=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* Ref=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    uint8_t Value1=ORef->Get();
    uint8_t Value2=Ref->Get();
    uint8_t Cary=C->CarryFlag() ? 1 : 0;
    int32_t R=Value1-Value2 - Cary;
    uint8_t ValueO=Value1-Value2-Cary;
    ORef->Set((uint8_t)ValueO);
    C->SetZeroFlag(ValueO == 0);
    C->SetSubtractFlag(true);
    C->SetHalfCaryFlag(((Value1 & 0xf) - (Value2 & 0xf) - Cary) < 0);
    C->SetCarryFlag(R < 0);
    return true;
}

bool CP(Cpu* C, OpCodeEntry* Op)
{
    Refference* ORef=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* Ref=C->ResolveValue(Op->Types[1], Op->Dir[1]);
    uint8_t Value1=ORef->Get();
    uint8_t Value2=Ref->Get();
    uint8_t ValueO=Value1-Value2;
    C->SetZeroFlag(ValueO == 0);
    C->SetSubtractFlag(true);
    C->SetHalfCaryFlag(CheckSubHalfCarry(Value1, Value2));
    C->SetCarryFlag(Value2 > Value1);
    return true;
}

bool RLC(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t Carry = Bit(Reg->Get(), 7);
    uint8_t Trunc = Bit(Reg->Get(), 7);
    uint8_t Result = (uint8_t)((Reg->Get() << 1) | Trunc);

    C->SetCarryFlag(Carry);
    C->SetZeroFlag(Result == 0);
    C->SetHalfCaryFlag(false);
    C->SetSubtractFlag(false);

    Reg->Set(Result);
    return true;
}

bool RLCA(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t Carry = Bit(Reg->Get(), 7);
    uint8_t Trunc = Bit(Reg->Get(), 7);
    uint8_t Result = (uint8_t)((Reg->Get() << 1) | Trunc);

    C->SetCarryFlag(Carry);
    C->SetZeroFlag(false);
    C->SetHalfCaryFlag(false);
    C->SetSubtractFlag(false);

    Reg->Set(Result);
    return true;
}

bool RL(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t Carry = C->CarryFlag() ? 1 : 0;
    uint8_t Value = Reg->Get();

    bool will_carry = Bit(Value, 7);
    C->SetCarryFlag(will_carry);

    uint8_t Result = (uint8_t)(Value << 1);
    Result |= Carry;

    C->SetZeroFlag(Result == 0);

    C->SetSubtractFlag(false);
    C->SetHalfCaryFlag(false);
    Reg->Set(Result);
    return true;
}


bool RLA(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t Carry = C->CarryFlag() ? 1 : 0;
    uint8_t Value = Reg->Get();

    bool IsCarry = Bit(Value, 7);
    C->SetCarryFlag(IsCarry);

    uint8_t Result = (uint8_t)(Value << 1);
    Result |= Carry;

    C->SetZeroFlag(false);

    C->SetSubtractFlag(false);
    C->SetHalfCaryFlag(false);
    Reg->Set(Result);
    return true;
}

bool RRC(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t Carry=Bit(Reg->Get(),0);
    uint8_t Result= (uint8_t)(Reg->Get() >> 1);
    SetBit(Carry,Result,7);
    Reg->Set(Result);
    C->SetCarryFlag(Carry);
    C->SetZeroFlag(Result == 0);
    C->SetHalfCaryFlag(false);
    C->SetSubtractFlag(false);
    return true;
}

bool RR(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t Carry=Bit(Reg->Get(),0);
    uint8_t Result= (uint8_t)(Reg->Get() >> 1);
    SetBit(C->CarryFlag(),Result,7);
    Reg->Set(Result);
    C->SetCarryFlag(Carry);
    C->SetZeroFlag(Result == 0);
    C->SetHalfCaryFlag(false);
    C->SetSubtractFlag(false);
    return true;
}

bool RRCA(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t Carry=Bit(Reg->Get(),0);
    uint8_t Result= (uint8_t)(Reg->Get() >> 1);
    SetBit(Carry,Result,7);
    Reg->Set(Result);
    C->SetCarryFlag(Carry);
    C->SetZeroFlag(false);
    C->SetHalfCaryFlag(false);
    C->SetSubtractFlag(false);
    return true;
}

bool RRA(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t Carry=Bit(Reg->Get(),0);
    uint8_t Result= (uint8_t)(Reg->Get() >> 1);
    SetBit(C->CarryFlag(),Result,7);
    Reg->Set(Result);
    C->SetCarryFlag(Carry);
    C->SetZeroFlag(false);
    C->SetHalfCaryFlag(false);
    C->SetSubtractFlag(false);
    return true;
}

bool CPL(Cpu* C, OpCodeEntry* Op)
{
    *(C->A) = ~(*(C->A));
    C->SetSubtractFlag(true);
    C->SetHalfCaryFlag(true);
    return true;
}

bool DAA(Cpu* C, OpCodeEntry* Op)
{
    Refference* A=&C->ARef;
    uint8_t Value=A->Get();
    uint16_t Correction=C->CarryFlag() ? 0x60 : 0x00;
    if (C->HalfCarryFlag() || (!C->SubtractFlag() && ((Value & 0x0F) > 9))) {
        Correction |= 0x06;
    }
    if (C->CarryFlag() || (!C->SubtractFlag() && (Value > 0x99))) {
        Correction |= 0x60;
    }
    if (C->SubtractFlag())
    {
        Value = (uint8_t)(Value - Correction);
    }
    else
    {
        Value = (uint8_t)(Value + Correction);
    }
    if (((Correction << 2) & 0x100) != 0)
    {
        C->SetCarryFlag(true);
    }
    C->SetHalfCaryFlag(false);
    C->SetZeroFlag(Value == 0);
    A->Set(Value);
    return true;
}

bool CCF(Cpu* C, OpCodeEntry* Op)
{
    C->SetSubtractFlag(false);
    C->SetHalfCaryFlag(false);
    C->SetCarryFlag(!C->CarryFlag());
    return true;
}

bool SWAP(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t d=Reg->Get();
    uint8_t Lower= d & 0x0F;
    uint8_t Upper= d & 0xF0;
    uint8_t ReturnV=(Upper >> 4)|(Lower << 4);
    C->SetZeroFlag(!ReturnV);
    C->SetCarryFlag(false);
    C->SetHalfCaryFlag(false);
    C->SetSubtractFlag(false);
    Reg->Set(ReturnV);
    return true;
}

bool SLA(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t d= Reg->Get();
    uint8_t Carry=Bit(d,7);
    d= (uint8_t)(d << 1);
    C->SetCarryFlag(Carry);
    C->SetHalfCaryFlag(false);
    C->SetSubtractFlag(false);
    C->SetZeroFlag(d == 0);
    Reg->Set(d);
    return true;
}

bool SRA(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t d=Reg->Get();
    bool Top=Bit(d, 7);
    C->SetCarryFlag(Bit(d,0));
    d=(d >> 1);
    SetBit(Top,d,7);
    Reg->Set(d);
    C->SetZeroFlag(!d);
    C->SetHalfCaryFlag(false);
    C->SetSubtractFlag(false);
    return true;
}

bool SRL(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t d=Reg->Get();
    C->SetCarryFlag(Bit(d,0));
    d=(d >> 1);
    Reg->Set(d);
    C->SetZeroFlag(!d);
    C->SetHalfCaryFlag(false);
    C->SetSubtractFlag(false);
    return true;
}

bool BIT(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    C->SetZeroFlag(!Bit(Reg->Get(),Op->Ex));
    C->SetHalfCaryFlag(true);
    C->SetSubtractFlag(false);
    return true;
}

bool SET(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t d=Reg->Get();
    SetBit(true, d, Op->Ex);
    Reg->Set(d);
    return true;
}


bool RES(Cpu* C, OpCodeEntry* Op)
{
    Refference* Reg=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    uint8_t d=Reg->Get();
    SetBit(false, d, Op->Ex);
    Reg->Set(d);
    return true;
}
