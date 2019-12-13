#ifndef MEMORYOP_H_INCLUDED
#define MEMORYOP_H_INCLUDED
#include "../Cpu.h"

bool LD(Cpu* C, OpCodeEntry* Op);
bool LDSPHL(Cpu* C, OpCodeEntry* Op);

bool LDW(Cpu* C, OpCodeEntry* Op);

bool PUSH(Cpu* C, OpCodeEntry* Op);

bool POP(Cpu* C, OpCodeEntry* Op);

bool SCF(Cpu* C, OpCodeEntry* Op);
bool LDH(Cpu* C, OpCodeEntry* Op);

bool LDD(Cpu* C, OpCodeEntry* Op);
bool LDI(Cpu* C, OpCodeEntry* Op);


#endif // MEMORY_H_INCLUDED
