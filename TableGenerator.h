#ifndef TABLEGENERATOR_H_INCLUDED
#define TABLEGENERATOR_H_INCLUDED
#include "Instruction/OpCodes.h"
#include "DebugLog.h"
#include "Instruction/OpCodeTable.h"
#include <fstream>

extern const char* OperandTypeNames[];
extern const char* OpTypeNames[];

void Inverse(const OpCodeEntry& Op, std::ostream& out, char C=',');

void Dump(std::ostream& out);

void CSVDump(std::ostream& out);

#endif // TABLEGENERATOR_H_INCLUDED
