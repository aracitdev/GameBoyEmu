#ifndef OPCODES_H_INCLUDED
#define OPCODES_H_INCLUDED
#include <cstdint>

enum class OpTypes
{
    //Memory
    LD, LDW,
    LDD, LDI,
    PUSH,POP,

    //Arithmetic
    ADD,ADDW,
    SUB,SUBW,
    INC,INCW,
    DEC,DECW,
    OR, XOR,
    AND, SBC, ADC, CP,

    //Control
    NOOP, HALT, STOP, CB,
    LDH,
    JP, //jump
    JPR,//jump relative
    RST,
    RET,
    CALL,

    //
    RLC,RRC, DAA, CPL, CCF, SCF, RL, RR, RETI, LDF8, EI, DI, ADDWS,

    //CB Funcs
    SLA, SRA, SRL, SWAP, BIT, SET, RES, RLCA, RLA, RRCA, RRA
};

enum class OperandTypes
{
    None,
    Immediate8,
    Immediate16,
    ImmediateS8,
    Address8,
    Address16,
    AF,
    BC,
    DE,
    HL,
    SP,
    CZ,
    CC,
    PC,
    CNZ,
    CNC,
    A,
    B,
    D,
    H,
    F,
    C,
    E,
    L
};

enum class OperandMem
{
    Indirected,
    Const
};

struct OpCodeEntry
{
    OpTypes Operation;
    OperandTypes Types[2];   //sometimes all are used, sometimes none
    OperandMem Dir[2];
    uint16_t Cycles;
    uint16_t BranchedCycles;
    uint8_t Ex;             //used in ops that are based on numeric ammounts rather than regs (AKA BIT FUNCTIONS,
    OpCodeEntry(OpTypes Op, OperandTypes Type1, OperandTypes Type2, OperandMem D1, OperandMem D2, uint16_t Cycle, uint16_t Br, uint8_t E=0):Operation(Op), Types{Type1,Type2}, Dir{D1,D2}, Cycles(Cycle), BranchedCycles(Br), Ex(E) {}
};


#endif // OPCODES_H_INCLUDED
