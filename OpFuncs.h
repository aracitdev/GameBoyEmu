#ifndef OPFUNCS_H_INCLUDED
#define OPFUNCS_H_INCLUDED

#include "Instruction/Memory.h"


typedef bool (*OperationFunc)(Cpu*, OpCodeEntry*);

extern OperationFunc OperationList[(const uint32_t)OpTypes::RRA + 1];

#endif // OPFUNCS_H_INCLUDED
