#ifndef ARITHMETICOP_H_INCLUDED
#define ARITHMETICOP_H_INCLUDED

#include <cstdint>
#include "../cpu.h"

bool CheckSubHalfCarry(uint8_t a, uint8_t b);

bool CheckAddHalfCarry(uint8_t a, uint8_t b);

bool CheckWAddHalfCarry(uint16_t a, uint16_t b, uint16_t r);

bool INC(Cpu* C, OpCodeEntry* Op);

bool DEC(Cpu* C, OpCodeEntry* Op);

bool INCW(Cpu* C, OpCodeEntry* Op);

bool DECW(Cpu* C, OpCodeEntry* Op);

//this one is only used with HL
bool ADDW(Cpu* C, OpCodeEntry* Op);

bool ADDWS(Cpu* C, OpCodeEntry* Op);

bool ADD(Cpu* C, OpCodeEntry* Op);

bool SUB(Cpu* C, OpCodeEntry* Op);

bool XOR(Cpu* C, OpCodeEntry* Op);


bool AND(Cpu* C, OpCodeEntry* Op);


bool OR(Cpu* C, OpCodeEntry* Op);

bool RST(Cpu* C, OpCodeEntry* Op);

bool ADC(Cpu* C, OpCodeEntry* Op);


bool SBC(Cpu* C, OpCodeEntry* Op);

bool CP(Cpu* C, OpCodeEntry* Op);

bool RLC(Cpu* C, OpCodeEntry* Op);

bool RLCA(Cpu* C, OpCodeEntry* Op);

bool RL(Cpu* C, OpCodeEntry* Op);


bool RLA(Cpu* C, OpCodeEntry* Op);

bool RRC(Cpu* C, OpCodeEntry* Op);

bool RR(Cpu* C, OpCodeEntry* Op);

bool RRCA(Cpu* C, OpCodeEntry* Op);

bool RRA(Cpu* C, OpCodeEntry* Op);

bool CPL(Cpu* C, OpCodeEntry* Op);

bool DAA(Cpu* C, OpCodeEntry* Op);

bool CCF(Cpu* C, OpCodeEntry* Op);

bool SWAP(Cpu* C, OpCodeEntry* Op);

bool SLA(Cpu* C, OpCodeEntry* Op);

bool SRA(Cpu* C, OpCodeEntry* Op);

bool SRL(Cpu* C, OpCodeEntry* Op);

bool BIT(Cpu* C, OpCodeEntry* Op);

bool SET(Cpu* C, OpCodeEntry* Op);


bool RES(Cpu* C, OpCodeEntry* Op);

#endif // ARITHMETIC_H_INCLUDED
