#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED
#include "../Cpu.h"


bool NOOP(Cpu*, OpCodeEntry*);

bool JP(Cpu* C, OpCodeEntry* Op);

bool JPR(Cpu* C, OpCodeEntry* Op);

bool CALL(Cpu* C, OpCodeEntry* Op);

bool RET(Cpu* C, OpCodeEntry* Op);

bool EI(Cpu* C, OpCodeEntry* Op);

bool DI(Cpu* C, OpCodeEntry* Op);

bool HALT(Cpu* C, OpCodeEntry* Op);

bool STOP(Cpu* C, OpCodeEntry* Op);

bool CB(Cpu* C, OpCodeEntry* Op);
bool RETI(Cpu* C, OpCodeEntry* Op);

#endif // CONTROL_H_INCLUDED
