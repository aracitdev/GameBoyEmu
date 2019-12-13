#include "OpFuncs.h"

OperationFunc OperationList[(const uint32_t)OpTypes::RRA + 1]=
{
    LD,LDW, LDD, LDI, PUSH, POP, ADD, ADDW, SUB, NOOP, INC, INCW, DEC, DECW, OR, XOR, AND, SBC, ADC, CP, NOOP, HALT, STOP, CB,
    LDH, JP, JPR, RST, RET, CALL, RLC, RRC, DAA, CPL, CCF, SCF, RL, RR, RETI, LDSPHL, EI, DI, ADDWS,
    SLA, SRA, SRL, SWAP, BIT, SET, RES, RLCA, RLA, RRCA, RRA
};
