#include "Refference.h"
#include "Mmu.h"

void Refference::SetMmu(Mmu* M)
{
    Mem=M;
}

MemRef::MemRef(uint16_t Value, Mmu* M)
{
    Adr=Value;
    Mem=M;
    Type=RefferenceTypes::Memory;
}

uint8_t MemRef::Get(void)
{
    return Mem->Read(Adr);
}

uint16_t MemRef::Get16(void)
{
    uint16_t Low=Mem->Read(Adr);
    uint16_t High=Mem->Read(Adr+1);
    return (High << 8) | Low;
}

void MemRef::Set(uint8_t v)
{
    Mem->Write(Adr, v);
}

void MemRef::Set(uint16_t v)
{
    Mem->Write(Adr, v & 0xff);
    Mem->Write(Adr+1, (v >> 8) & 0xff);
}

Refference* MemRef::DeRef(void)
{
    uint16_t Ref=Get16();
    return new MemRef(Ref, Mem);
}

void MemRef::SetAddress(uint16_t Ad)
{
    Adr=Ad;
}


RegRef::RegRef(uint8_t& Value, Mmu* M)
{
    Int=&Value;
    Mem=M;
    Type=RefferenceTypes::Register;
}

RegRef::RegRef(uint16_t& Value, Mmu* M)
{
    Int=(uint8_t*)&Value;
    Mem=M;
    Type=RefferenceTypes::Register;
}

uint8_t RegRef::Get(void)
{
    return *Int;
}

uint16_t RegRef::Get16(void)
{
    return *((uint16_t*)Int);
}

void RegRef::Set(uint8_t v)
{
    *Int=v;
}

void RegRef::Set(uint16_t v)
{
    *((uint16_t*)(Int))=v;
}

Refference* RegRef::DeRef(void)
{
    return new MemRef(*((uint16_t*)Int), Mem);
}



ConstRef::ConstRef(int32_t V, Mmu* M)
{
    Value=V;
    Mem=M;
    Type=RefferenceTypes::Constant;
}

uint8_t ConstRef::Get(void)
{
    return Value;
}

uint16_t ConstRef::Get16(void)
{
    return Value;
}

void ConstRef::Set(uint8_t v)
{
    Value=v;
}

void ConstRef::Set(uint16_t v)
{
    Value=v;
}

Refference* ConstRef::DeRef(void)
{
    return new MemRef(Value, Mem);
}


ConditionalRef::ConditionalRef(bool V, Mmu* M)
{
    Value=V;
    Mem=M;
    Type=RefferenceTypes::Conditional;
}

uint8_t ConditionalRef::Get(void)
{
    return Value ? 1: 0;
}

uint16_t ConditionalRef::Get16(void)
{
    return Value ? 1: 0;
}


void ConditionalRef::Set(uint8_t v)
{
    Value=v;
}

void ConditionalRef::Set(uint16_t v)
{
    Value=v;
}

Refference* ConditionalRef::DeRef(void)
{
    return new MemRef(Value, Mem);
}

