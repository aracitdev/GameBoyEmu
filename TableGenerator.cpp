#include "TableGenerator.h"

const char* OperandTypeNames[]={"","d8","d16","s8","a8","a16","AF","BC","DE","HL","SP","Z","C","PC","NZ","NC","A","B","D","H","F","C","E","L"};
const char* OpTypeNames[]={"LD","LD","LDD","LDI","PUSH","POP","ADD","ADD", "SUB","SUB","INC","INC","DEC","DEC","OR","XOR","AND","SBC","ADC","CP","NOP","HAULT","STOP", "CB", "LDH", "JP", "JR","RST", "RET","CALL", "RLC", "RRC", "DAA", "CPL","CCF","SCF",
                            "RL", "RR", "RETI", "LD", "EI", "DI","ADD", "SLA", "SRA", "SRL", "SWAP", "BIT", "SET", "RES"};


void Inverse(const OpCodeEntry& Op, std::ostream& out, char C)
{
    out<<OpTypeNames[(uint16_t)Op.Operation]<<" ";
    if(Op.Types[0] == OperandTypes::None)
        return;

    if(Op.Dir[0] == OperandMem::Indirected)
        out<<"(";
    out<<OperandTypeNames[(uint16_t)Op.Types[0]];
    if(Op.Dir[0] == OperandMem::Indirected)
        out<<")";
    if(Op.Types[1] == OperandTypes::None)
        return;
    out<<C;
    if(Op.Dir[1] == OperandMem::Indirected)
        out<<"(";
    out<<OperandTypeNames[(uint16_t)Op.Types[1]];
    if(Op.Dir[1] == OperandMem::Indirected)
        out<<")";
    return;
}

void Dump(std::ostream& out)
{
    for(uint32_t counter=0; counter <  OpCodeCount; counter++)
    {
        GetHex(counter, out);
        out << ":";
        Inverse(OpCodes[counter], out);
        out << " ";
        if(OpCodes[counter].Cycles == OpCodes[counter].BranchedCycles)
            out <<OpCodes[counter].Cycles<<"\n";
        else
            out <<OpCodes[counter].BranchedCycles <<"/"<<OpCodes[counter].Cycles<<"\n";
    }
}

void CSVDump(std::ostream& out)
{
    for(uint32_t counter=0; counter < 16; counter++)
    {
        out <<',';
        GetHex(counter, out);
    }
    for(uint32_t countery=0; countery< 16; countery++)
    {
        out <<'\n';
        GetHex(countery * 16, out);
        for(uint32_t counterx=0; counterx< 16; counterx++)
        {
            out <<',';
            Inverse(OpCodes[countery * 16 + counterx], out, ' ');
        }
    }
}
