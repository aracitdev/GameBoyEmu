#include "OpCodeTable.h"

const uint32_t OpCodeCount=256;

OpCodeEntry OpCodes[OpCodeCount]
{
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,       4, 4},  //0x00 NOOP
    {OpTypes::LDW, OperandTypes::BC, OperandTypes::Immediate16, OperandMem::Const, OperandMem::Const,   12, 12},//0x01 LD BC d16
    {OpTypes::LD, OperandTypes::BC, OperandTypes::A,OperandMem::Indirected, OperandMem::Const,           8, 8},  //0x02 LD (BC) A
    {OpTypes::INCW, OperandTypes::BC, OperandTypes::None,OperandMem::Const, OperandMem::Const,           8, 8}, //0x03 INC BC
    {OpTypes::INC, OperandTypes::B, OperandTypes::None,OperandMem::Const, OperandMem::Const,             4, 4}, //0x04 INC B
    {OpTypes::DEC, OperandTypes::B, OperandTypes::None,OperandMem::Const, OperandMem::Const,             4, 4}, //0x05 DEC B
    {OpTypes::LD, OperandTypes::B, OperandTypes::Immediate8,OperandMem::Const, OperandMem::Const,        8, 8}, //0x06 LD B d8
    {OpTypes::RLCA,OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x07 RCLA
    {OpTypes::LDW, OperandTypes::Address16, OperandTypes::SP, OperandMem::Indirected, OperandMem::Const,20,20},//0x08 LD (a16) SP
    {OpTypes::ADDW, OperandTypes::HL, OperandTypes::BC, OperandMem::Const, OperandMem::Const,            8, 8}, //0x09 ADD HL BC
    {OpTypes::LD, OperandTypes::A, OperandTypes::BC, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0x0A LD A (BC)
    {OpTypes::DECW,OperandTypes::BC, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8, 8}, //0x0B DEC BC
    {OpTypes::INC, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x0C INC C
    {OpTypes::DEC, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x0D DEC C
    {OpTypes::LD, OperandTypes::C, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const ,      8, 8}, //0x0E LD C d8
    {OpTypes::RRCA, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const ,          4, 4}, //0x0F RRCA

    //0x10
    {OpTypes::STOP, OperandTypes::Immediate8, OperandTypes::None, OperandMem::Const, OperandMem::Const,  4, 4}, //0x10 STOP 0
    {OpTypes::LDW, OperandTypes::DE, OperandTypes::Immediate16, OperandMem::Const, OperandMem::Const,  12, 12}, //0x11 LD DE d16
    {OpTypes::LD, OperandTypes::DE, OperandTypes::A, OperandMem::Indirected, OperandMem::Const ,         8, 8}, //0x12 LD (DE) A
    {OpTypes::INCW, OperandTypes::DE, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8, 8}, //0x13 INC DE
    {OpTypes::INC, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x14 INC D
    {OpTypes::DEC, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x15 DEC D
    {OpTypes::LD, OperandTypes::D, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,       8, 8}, //0x16 LD D d8
    {OpTypes::RLA, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x17 RLA
    {OpTypes::JPR,OperandTypes::ImmediateS8, OperandTypes::None, OperandMem::Const, OperandMem::Const,  12,12}, //0x18 JP s8
    {OpTypes::ADDW, OperandTypes::HL, OperandTypes::DE, OperandMem::Const, OperandMem::Const,            8, 8}, //0x19 ADD HL DE
    {OpTypes::LD, OperandTypes::A, OperandTypes::DE, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0x1A LD A (DE)
    {OpTypes::DECW, OperandTypes::DE, OperandTypes::None, OperandMem::Const, OperandMem::Const     ,     8, 8}, //0x1B DEC DE
    {OpTypes::INC, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const ,           4, 4}, //0x1C INC E
    {OpTypes::DEC, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x1D DEC E
    {OpTypes::LD, OperandTypes::E, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,       8, 8}, //0x1E LD E d8
    {OpTypes::RRA, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x1F RRA

    //0x20
    {OpTypes::JPR, OperandTypes::CNZ, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,   8, 12}, //JR NZ d8
    {OpTypes::LDW, OperandTypes::HL, OperandTypes::Immediate16, OperandMem::Const, OperandMem::Const,  12, 12}, //0x21 LD HL d16
    {OpTypes::LDI, OperandTypes::HL, OperandTypes::A, OperandMem::Indirected, OperandMem::Const ,         8, 8}, //0x22 LD (HL) A
    {OpTypes::INCW, OperandTypes::HL, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8, 8}, //0x23 INC HL
    {OpTypes::INC, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x24 INC H
    {OpTypes::DEC, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x25 DEC H
    {OpTypes::LD, OperandTypes::H, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,       8, 8}, //0x26 LD H d8
    {OpTypes::DAA, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4, 4}, //0x27 DAA
    {OpTypes::JPR, OperandTypes::CZ, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,     8,12}, //0x28 JR Z d8
    {OpTypes::ADDW, OperandTypes::HL, OperandTypes::HL, OperandMem::Const, OperandMem::Const,            8, 8}, //0x29 ADD HL HL
    {OpTypes::LDI, OperandTypes::A, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0x2A LD A (HL)
    {OpTypes::DECW, OperandTypes::HL, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8, 8}, //0x2 DEC HL
    {OpTypes::INC, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const ,           4, 4}, //0x2C INC L
    {OpTypes::DEC, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x2D DEC L
    {OpTypes::LD, OperandTypes::L, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,       8, 8}, //0x2E LD L d8
    {OpTypes::CPL, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4, 4}, //0x2F CFF


    //0x30
    {OpTypes::JPR, OperandTypes::CNC, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,   8, 12}, //JR NC d8
    {OpTypes::LDW, OperandTypes::SP, OperandTypes::Immediate16, OperandMem::Const, OperandMem::Const,  12, 12}, //0x31 LD SP d16
    {OpTypes::LDD, OperandTypes::HL, OperandTypes::A, OperandMem::Indirected, OperandMem::Const ,         8, 8}, //0x32 LD (HL) A
    {OpTypes::INCW, OperandTypes::SP, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8, 8}, //0x33 INC SP
    {OpTypes::INC, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,    12, 12}, //0x34 INC (HL)
    {OpTypes::DEC, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,    12, 12}, //0x35 DEC (HL)
    {OpTypes::LD, OperandTypes::HL, OperandTypes::Immediate8, OperandMem::Indirected, OperandMem::Const,12,12}, //0x36 LD (HL) d8
    {OpTypes::SCF, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4, 4}, //0x37 SCF
    {OpTypes::JPR, OperandTypes::CC, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,     8,12}, //0x38 JR C d8
    {OpTypes::ADDW, OperandTypes::HL, OperandTypes::SP, OperandMem::Const, OperandMem::Const,            8, 8}, //0x39 ADD HL SP
    {OpTypes::LDD, OperandTypes::A, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0x3A LD A (HL)
    {OpTypes::DECW, OperandTypes::SP, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8, 8}, //0x3B DEC SP
    {OpTypes::INC, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const ,           4, 4}, //0x3C INC A
    {OpTypes::DEC, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,            4, 4}, //0x3D DEC A
    {OpTypes::LD, OperandTypes::A, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,       8, 8}, //0x3E LD A d8
    {OpTypes::CCF, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4, 4}, //0x3F CFF

    //0x40
    {OpTypes::LD, OperandTypes::B, OperandTypes::B, OperandMem::Const, OperandMem::Const,                4, 4}, //0x40 LD B B
    {OpTypes::LD, OperandTypes::B, OperandTypes::C, OperandMem::Const, OperandMem::Const,                4, 4}, //0x41 LD B C
    {OpTypes::LD, OperandTypes::B, OperandTypes::D, OperandMem::Const, OperandMem::Const,                4, 4}, //0x42 LD B D
    {OpTypes::LD, OperandTypes::B, OperandTypes::E, OperandMem::Const, OperandMem::Const,                4, 4}, //0x43 LD B E
    {OpTypes::LD, OperandTypes::B, OperandTypes::H, OperandMem::Const, OperandMem::Const,                4, 4}, //0x44 LD B H
    {OpTypes::LD, OperandTypes::B, OperandTypes::L, OperandMem::Const, OperandMem::Const,                4, 4}, //0x45 LD B L
    {OpTypes::LD, OperandTypes::B, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0x46 LD B (HL)
    {OpTypes::LD, OperandTypes::B, OperandTypes::A, OperandMem::Const, OperandMem::Const,                4, 4}, //0x47 LD B A
    {OpTypes::LD, OperandTypes::C, OperandTypes::B, OperandMem::Const, OperandMem::Const,                4, 4}, //0x48 LD C B
    {OpTypes::LD, OperandTypes::C, OperandTypes::C, OperandMem::Const, OperandMem::Const,                4, 4}, //0x49 LD C C
    {OpTypes::LD, OperandTypes::C, OperandTypes::D, OperandMem::Const, OperandMem::Const,                4, 4}, //0x4A LD C D
    {OpTypes::LD, OperandTypes::C, OperandTypes::E, OperandMem::Const, OperandMem::Const,                4, 4}, //0x4B LD C E
    {OpTypes::LD, OperandTypes::C, OperandTypes::H, OperandMem::Const, OperandMem::Const,                4, 4}, //0x4C LD C H
    {OpTypes::LD, OperandTypes::C, OperandTypes::L, OperandMem::Const, OperandMem::Const,                4, 4}, //0x4D LD C L
    {OpTypes::LD, OperandTypes::C, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0x4E LD C (HL)
    {OpTypes::LD, OperandTypes::C, OperandTypes::A, OperandMem::Const, OperandMem::Const,                4, 4}, //0x4F LD C A


    //0x50
    {OpTypes::LD, OperandTypes::D, OperandTypes::B, OperandMem::Const, OperandMem::Const,                4, 4}, //0x50 LD D B
    {OpTypes::LD, OperandTypes::D, OperandTypes::C, OperandMem::Const, OperandMem::Const,                4, 4}, //0x51 LD D C
    {OpTypes::LD, OperandTypes::D, OperandTypes::D, OperandMem::Const, OperandMem::Const,                4, 4}, //0x52 LD D D
    {OpTypes::LD, OperandTypes::D, OperandTypes::E, OperandMem::Const, OperandMem::Const,                4, 4}, //0x53 LD D E
    {OpTypes::LD, OperandTypes::D, OperandTypes::H, OperandMem::Const, OperandMem::Const,                4, 4}, //0x54 LD D H
    {OpTypes::LD, OperandTypes::D, OperandTypes::L, OperandMem::Const, OperandMem::Const,                4, 4}, //0x55 LD D L
    {OpTypes::LD, OperandTypes::D, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0x56 LD D (HL)
    {OpTypes::LD, OperandTypes::D, OperandTypes::A, OperandMem::Const, OperandMem::Const,                4, 4}, //0x57 LD D A
    {OpTypes::LD, OperandTypes::E, OperandTypes::B, OperandMem::Const, OperandMem::Const,                4, 4}, //0x58 LD E B
    {OpTypes::LD, OperandTypes::E, OperandTypes::C, OperandMem::Const, OperandMem::Const,                4, 4}, //0x59 LD E C
    {OpTypes::LD, OperandTypes::E, OperandTypes::D, OperandMem::Const, OperandMem::Const,                4, 4}, //0x5A LD E D
    {OpTypes::LD, OperandTypes::E, OperandTypes::E, OperandMem::Const, OperandMem::Const,                4, 4}, //0x5B LD E E
    {OpTypes::LD, OperandTypes::E, OperandTypes::H, OperandMem::Const, OperandMem::Const,                4, 4}, //0x5C LD E H
    {OpTypes::LD, OperandTypes::E, OperandTypes::L, OperandMem::Const, OperandMem::Const,                4, 4}, //0x5D LD E L
    {OpTypes::LD, OperandTypes::E, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0x5E LD E (HL)
    {OpTypes::LD, OperandTypes::E, OperandTypes::A, OperandMem::Const, OperandMem::Const,                4, 4}, //0x5F LD E A


    //0x60
    {OpTypes::LD, OperandTypes::H, OperandTypes::B, OperandMem::Const, OperandMem::Const,                4, 4}, //0x60 LD D B
    {OpTypes::LD, OperandTypes::H, OperandTypes::C, OperandMem::Const, OperandMem::Const,                4, 4}, //0x61 LD D C
    {OpTypes::LD, OperandTypes::H, OperandTypes::D, OperandMem::Const, OperandMem::Const,                4, 4}, //0x62 LD D D
    {OpTypes::LD, OperandTypes::H, OperandTypes::E, OperandMem::Const, OperandMem::Const,                4, 4}, //0x63 LD D E
    {OpTypes::LD, OperandTypes::H, OperandTypes::H, OperandMem::Const, OperandMem::Const,                4, 4}, //0x64 LD D H
    {OpTypes::LD, OperandTypes::H, OperandTypes::L, OperandMem::Const, OperandMem::Const,                4, 4}, //0x65 LD D L
    {OpTypes::LD, OperandTypes::H, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0x66 LD D (HL)
    {OpTypes::LD, OperandTypes::H, OperandTypes::A, OperandMem::Const, OperandMem::Const,                4, 4}, //0x67 LD D A
    {OpTypes::LD, OperandTypes::L, OperandTypes::B, OperandMem::Const, OperandMem::Const,                4, 4}, //0x68 LD E B
    {OpTypes::LD, OperandTypes::L, OperandTypes::C, OperandMem::Const, OperandMem::Const,                4, 4}, //0x69 LD E C
    {OpTypes::LD, OperandTypes::L, OperandTypes::D, OperandMem::Const, OperandMem::Const,                4, 4}, //0x6A LD E D
    {OpTypes::LD, OperandTypes::L, OperandTypes::E, OperandMem::Const, OperandMem::Const,                4, 4}, //0x6B LD E E
    {OpTypes::LD, OperandTypes::L, OperandTypes::H, OperandMem::Const, OperandMem::Const,                4, 4}, //0x6C LD E H
    {OpTypes::LD, OperandTypes::L, OperandTypes::L, OperandMem::Const, OperandMem::Const,                4, 4}, //0x6D LD E L
    {OpTypes::LD, OperandTypes::L, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0x6E LD E (HL)
    {OpTypes::LD, OperandTypes::L, OperandTypes::A, OperandMem::Const, OperandMem::Const,                4, 4}, //0x6F LD E A


    //0x70
    {OpTypes::LD, OperandTypes::HL, OperandTypes::B, OperandMem::Indirected, OperandMem::Const,          8, 8}, //0x70 LD (HL) B
    {OpTypes::LD, OperandTypes::HL, OperandTypes::C, OperandMem::Indirected, OperandMem::Const,          8, 8}, //0x71 LD (HL) C
    {OpTypes::LD, OperandTypes::HL, OperandTypes::D, OperandMem::Indirected, OperandMem::Const,          8, 8}, //0x72 LD (HL) D
    {OpTypes::LD, OperandTypes::HL, OperandTypes::E, OperandMem::Indirected, OperandMem::Const,          8, 8}, //0x73 LD (HL) E
    {OpTypes::LD, OperandTypes::HL, OperandTypes::H, OperandMem::Indirected, OperandMem::Const,          8, 8}, //0x74 LD (HL) H
    {OpTypes::LD, OperandTypes::HL, OperandTypes::L, OperandMem::Indirected, OperandMem::Const,          8, 8}, //0x75 LD (HL) L
    {OpTypes::HALT, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,       4, 4}, //0x76 HAULT
    {OpTypes::LD, OperandTypes::HL, OperandTypes::A, OperandMem::Indirected, OperandMem::Const,          8, 8}, //0x77 LD (HL) A
    {OpTypes::LD, OperandTypes::A, OperandTypes::B, OperandMem::Const, OperandMem::Const,                4, 4}, //0x78 LD A B
    {OpTypes::LD, OperandTypes::A, OperandTypes::C, OperandMem::Const, OperandMem::Const,                4, 4}, //0x79 LD A C
    {OpTypes::LD, OperandTypes::A, OperandTypes::D, OperandMem::Const, OperandMem::Const,                4, 4}, //0x7A LD A D
    {OpTypes::LD, OperandTypes::A, OperandTypes::E, OperandMem::Const, OperandMem::Const,                4, 4}, //0x7B LD A E
    {OpTypes::LD, OperandTypes::A, OperandTypes::H, OperandMem::Const, OperandMem::Const,                4, 4}, //0x7C LD A H
    {OpTypes::LD, OperandTypes::A, OperandTypes::L, OperandMem::Const, OperandMem::Const,                4, 4}, //0x7D LD A L
    {OpTypes::LD, OperandTypes::A, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0x7E LD A (HL)
    {OpTypes::LD, OperandTypes::A, OperandTypes::A, OperandMem::Const, OperandMem::Const,                4, 4}, //0x7F LD A A

    {OpTypes::ADD, OperandTypes::A, OperandTypes::B, OperandMem::Const, OperandMem::Const,               4, 4}, //0x80 ADD A B
    {OpTypes::ADD, OperandTypes::A, OperandTypes::C, OperandMem::Const, OperandMem::Const,               4, 4}, //0x81 ADD A C
    {OpTypes::ADD, OperandTypes::A, OperandTypes::D, OperandMem::Const, OperandMem::Const,               4, 4}, //0x82 ADD A D
    {OpTypes::ADD, OperandTypes::A, OperandTypes::E, OperandMem::Const, OperandMem::Const,               4, 4}, //0x83 ADD A E
    {OpTypes::ADD, OperandTypes::A, OperandTypes::H, OperandMem::Const, OperandMem::Const,               4, 4}, //0x84 ADD A H
    {OpTypes::ADD, OperandTypes::A, OperandTypes::L, OperandMem::Const, OperandMem::Const,               4, 4}, //0x85 ADD A L
    {OpTypes::ADD, OperandTypes::A, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,         8, 8}, //0x86 ADD A (HL)
    {OpTypes::ADD, OperandTypes::A, OperandTypes::A, OperandMem::Const, OperandMem::Const,               4, 4}, //0x87 ADD A A
    {OpTypes::ADC, OperandTypes::A, OperandTypes::B, OperandMem::Const, OperandMem::Const,               4, 4}, //0x88 ADD A B
    {OpTypes::ADC, OperandTypes::A, OperandTypes::C, OperandMem::Const, OperandMem::Const,               4, 4}, //0x89 ADD A C
    {OpTypes::ADC, OperandTypes::A, OperandTypes::D, OperandMem::Const, OperandMem::Const,               4, 4}, //0x8A ADD A D
    {OpTypes::ADC, OperandTypes::A, OperandTypes::E, OperandMem::Const, OperandMem::Const,               4, 4}, //0x8B ADD A E
    {OpTypes::ADC, OperandTypes::A, OperandTypes::H, OperandMem::Const, OperandMem::Const,               4, 4}, //0x8C ADD A H
    {OpTypes::ADC, OperandTypes::A, OperandTypes::L, OperandMem::Const, OperandMem::Const,               4, 4}, //0x8D ADD A L
    {OpTypes::ADC, OperandTypes::A, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,         8, 8}, //0x8E ADD A (HL)
    {OpTypes::ADC, OperandTypes::A, OperandTypes::A, OperandMem::Const, OperandMem::Const,               4, 4}, //0x8F ADD A A

    {OpTypes::SUB, OperandTypes::A, OperandTypes::B, OperandMem::Const, OperandMem::Const,               4, 4}, //0x90 SUB B
    {OpTypes::SUB, OperandTypes::A, OperandTypes::C, OperandMem::Const, OperandMem::Const,               4, 4}, //0x91 SUB C
    {OpTypes::SUB, OperandTypes::A, OperandTypes::D, OperandMem::Const, OperandMem::Const,               4, 4}, //0x92 SUB D
    {OpTypes::SUB, OperandTypes::A, OperandTypes::E, OperandMem::Const, OperandMem::Const,               4, 4}, //0x93 SUB E
    {OpTypes::SUB, OperandTypes::A, OperandTypes::H, OperandMem::Const, OperandMem::Const,               4, 4}, //0x94 SUB H
    {OpTypes::SUB, OperandTypes::A, OperandTypes::L, OperandMem::Const, OperandMem::Const,               4, 4}, //0x95 SUB L
    {OpTypes::SUB, OperandTypes::A, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,         8, 8}, //0x96 SUB (HL)
    {OpTypes::SUB, OperandTypes::A, OperandTypes::A, OperandMem::Const, OperandMem::Const,               4, 4}, //0x97 SUB A
    {OpTypes::SBC, OperandTypes::A, OperandTypes::B, OperandMem::Const, OperandMem::Const,               4, 4}, //0x98 SBC B
    {OpTypes::SBC, OperandTypes::A, OperandTypes::C, OperandMem::Const, OperandMem::Const,               4, 4}, //0x99 SBC C
    {OpTypes::SBC, OperandTypes::A, OperandTypes::D, OperandMem::Const, OperandMem::Const,               4, 4}, //0x9A SBC D
    {OpTypes::SBC, OperandTypes::A, OperandTypes::E, OperandMem::Const, OperandMem::Const,               4, 4}, //0x9B SBC E
    {OpTypes::SBC, OperandTypes::A, OperandTypes::H, OperandMem::Const, OperandMem::Const,               4, 4}, //0x9C SBC H
    {OpTypes::SBC, OperandTypes::A, OperandTypes::L, OperandMem::Const, OperandMem::Const,               4, 4}, //0x9D SBC L
    {OpTypes::SBC, OperandTypes::A, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,         8, 8}, //0x9E SBC (HL)
    {OpTypes::SBC, OperandTypes::A, OperandTypes::A, OperandMem::Const, OperandMem::Const,               4, 4}, //0x9F SBC A


    {OpTypes::AND, OperandTypes::A, OperandTypes::B, OperandMem::Const, OperandMem::Const,               4, 4}, //0xA0 AND B
    {OpTypes::AND, OperandTypes::A, OperandTypes::C, OperandMem::Const, OperandMem::Const,               4, 4}, //0xA1 AND C
    {OpTypes::AND, OperandTypes::A, OperandTypes::D, OperandMem::Const, OperandMem::Const,               4, 4}, //0xA2 AND D
    {OpTypes::AND, OperandTypes::A, OperandTypes::E, OperandMem::Const, OperandMem::Const,               4, 4}, //0xA3 AND E
    {OpTypes::AND, OperandTypes::A, OperandTypes::H, OperandMem::Const, OperandMem::Const,               4, 4}, //0xA4 AND H
    {OpTypes::AND, OperandTypes::A, OperandTypes::L, OperandMem::Const, OperandMem::Const,               4, 4}, //0xA5 AND L
    {OpTypes::AND, OperandTypes::A, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,         8, 8}, //0xA6 AND (HL)
    {OpTypes::AND, OperandTypes::A, OperandTypes::A, OperandMem::Const, OperandMem::Const,               4, 4}, //0xA7 AND A
    {OpTypes::XOR, OperandTypes::A, OperandTypes::B, OperandMem::Const, OperandMem::Const,               4, 4}, //0xA8 XOR B
    {OpTypes::XOR, OperandTypes::A, OperandTypes::C, OperandMem::Const, OperandMem::Const,               4, 4}, //0xA9 XOR C
    {OpTypes::XOR, OperandTypes::A, OperandTypes::D, OperandMem::Const, OperandMem::Const,               4, 4}, //0xAA XOR D
    {OpTypes::XOR, OperandTypes::A, OperandTypes::E, OperandMem::Const, OperandMem::Const,               4, 4}, //0xAB XOR E
    {OpTypes::XOR, OperandTypes::A, OperandTypes::H, OperandMem::Const, OperandMem::Const,               4, 4}, //0xAC XOR H
    {OpTypes::XOR, OperandTypes::A, OperandTypes::L, OperandMem::Const, OperandMem::Const,               4, 4}, //0xAD XOR L
    {OpTypes::XOR, OperandTypes::A, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,         8, 8}, //0xAE XOR (HL)
    {OpTypes::XOR, OperandTypes::A, OperandTypes::A, OperandMem::Const, OperandMem::Const,               4, 4}, //0xAF XOR A

    {OpTypes::OR, OperandTypes::A, OperandTypes::B, OperandMem::Const, OperandMem::Const,                4, 4}, //0xB0 OR B
    {OpTypes::OR, OperandTypes::A, OperandTypes::C, OperandMem::Const, OperandMem::Const,                4, 4}, //0xB1 OR C
    {OpTypes::OR, OperandTypes::A, OperandTypes::D, OperandMem::Const, OperandMem::Const,                4, 4}, //0xB2 OR D
    {OpTypes::OR, OperandTypes::A, OperandTypes::E, OperandMem::Const, OperandMem::Const,                4, 4}, //0xB3 OR E
    {OpTypes::OR, OperandTypes::A, OperandTypes::H, OperandMem::Const, OperandMem::Const,                4, 4}, //0xB4 OR H
    {OpTypes::OR, OperandTypes::A, OperandTypes::L, OperandMem::Const, OperandMem::Const,                4, 4}, //0xB5 OR L
    {OpTypes::OR, OperandTypes::A, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0xB6 OR (HL)
    {OpTypes::OR, OperandTypes::A, OperandTypes::A, OperandMem::Const, OperandMem::Const,                4, 4}, //0xB7 OR A
    {OpTypes::CP, OperandTypes::A, OperandTypes::B, OperandMem::Const, OperandMem::Const,                4, 4}, //0xB8 CP B
    {OpTypes::CP, OperandTypes::A, OperandTypes::C, OperandMem::Const, OperandMem::Const,                4, 4}, //0xB9 CP C
    {OpTypes::CP, OperandTypes::A, OperandTypes::D, OperandMem::Const, OperandMem::Const,                4, 4}, //0xBA CP D
    {OpTypes::CP, OperandTypes::A, OperandTypes::E, OperandMem::Const, OperandMem::Const,                4, 4}, //0xBB CP E
    {OpTypes::CP, OperandTypes::A, OperandTypes::H, OperandMem::Const, OperandMem::Const,                4, 4}, //0xBC CP H
    {OpTypes::CP, OperandTypes::A, OperandTypes::L, OperandMem::Const, OperandMem::Const,                4, 4}, //0xBD CP L
    {OpTypes::CP, OperandTypes::A, OperandTypes::HL, OperandMem::Const, OperandMem::Indirected,          8, 8}, //0xBE CP (HL)
    {OpTypes::CP, OperandTypes::A, OperandTypes::A, OperandMem::Const, OperandMem::Const,                4, 4}, //0xBF CP A

    {OpTypes::RET, OperandTypes::CNZ, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,20}, //0xC0 RET NZ
    {OpTypes::POP, OperandTypes::BC, OperandTypes::None, OperandMem::Const, OperandMem::Const,          12,12}, //0xC1 POP BC
    {OpTypes::JP, OperandTypes::CNZ, OperandTypes::Address16, OperandMem::Const, OperandMem::Const,     12,16}, //0xC2 JP NZ a16
    {OpTypes::JP, OperandTypes::Immediate16, OperandTypes::None, OperandMem::Const, OperandMem::Const,  16,16}, //0xC3 JP a16
    {OpTypes::CALL, OperandTypes::CNZ, OperandTypes::Address16, OperandMem::Const, OperandMem::Const,   12,24}, //0xC4 CALL NZ a16
    {OpTypes::PUSH, OperandTypes::BC, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8, 8}, //0xC5 PUSH BC
    {OpTypes::ADD, OperandTypes::A, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,      8, 8}, //0xC6 ADD A d8
    {OpTypes::RST, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,     16 ,16,0}, //0xC7 RST 00H
    {OpTypes::RET, OperandTypes::CZ, OperandTypes::None, OperandMem::Const, OperandMem::Const,           0,20}, //0xC8 RET Z
    {OpTypes::RET, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,        16,16}, //0xC9 RET
    {OpTypes::JP, OperandTypes::CZ, OperandTypes::Address16, OperandMem::Const, OperandMem::Const,      12,16}, //0xCA JP Z a16
    {OpTypes::CB, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,          4, 4}, //0xCB CBC
    {OpTypes::CALL, OperandTypes::CZ, OperandTypes::Address16, OperandMem::Const, OperandMem::Const,      12,16}, //0xCC JP Z a16
    {OpTypes::CALL, OperandTypes::Immediate16, OperandTypes::None, OperandMem::Const,OperandMem::Const, 24,24}, //0xCD CALL a16
    {OpTypes::ADC, OperandTypes::A, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,      8, 8}, //0xCE ADC d8
    {OpTypes::RST, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,    16,16,0x8}, //0xCF RST 08H

    {OpTypes::RET, OperandTypes::CNC, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8, 20}, //0xD0 RET NC
    {OpTypes::POP, OperandTypes::DE, OperandTypes::None, OperandMem::Const, OperandMem::Const,          12,12}, //0xD1 POP DE
    {OpTypes::JP, OperandTypes::CNC, OperandTypes::Address16, OperandMem::Const, OperandMem::Const,     12,16}, //0xD2 JP NC a16
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,       4,  4}, //0xD3
    {OpTypes::CALL, OperandTypes::CNC, OperandTypes::Address16, OperandMem::Const, OperandMem::Const,   12,24}, //0xD4 CALL NC a16
    {OpTypes::PUSH, OperandTypes::DE, OperandTypes::None, OperandMem::Const, OperandMem::Const,         16,16}, //0xD5 PUSH DE
    {OpTypes::SUB, OperandTypes::A, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,      8, 8}, //0xD6 SUB A d8
    {OpTypes::RST, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,   16,16,0x10}, //0xD7 RST 10H
    {OpTypes::RET, OperandTypes::CC, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,20}, //0xD8 RET C
    {OpTypes::RETI, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,       16,16}, //0xD9 RETI
    {OpTypes::JP, OperandTypes::CC, OperandTypes::Address16, OperandMem::Const, OperandMem::Const,       12,16}, //0xDA JP C a16
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,        4, 4}, //0xDB
    {OpTypes::CALL, OperandTypes::CC, OperandTypes::Address16, OperandMem::Const, OperandMem::Const,    12,24}, //0xDC CALL C a16
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,        4, 4}, //0xDD
    {OpTypes::SBC, OperandTypes::A, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,      8, 8}, //0xDE SBC A d8
    {OpTypes::RST, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,    16,16,0x18}, //0xDF RST 18H

    {OpTypes::LDH, OperandTypes::Address8, OperandTypes::A, OperandMem::Indirected, OperandMem::Const,  12,12}, //0xE0 LDH (a8) A
    {OpTypes::POP, OperandTypes::HL, OperandTypes::None, OperandMem::Const, OperandMem::Const,          12,12}, //0xE1 POP HL
    {OpTypes::LD, OperandTypes::C, OperandTypes::A, OperandMem::Indirected, OperandMem::Const,            8,8}, //0xE2 LD (C) A
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4,4}, //0xE3
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4,4}, //0xE4
    {OpTypes::PUSH, OperandTypes::HL, OperandTypes::None, OperandMem::Const, OperandMem::Const,         16,16}, //0xE5 PUSH HL
    {OpTypes::AND, OperandTypes::A, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,      8, 8}, //0xE6 AND A d8
    {OpTypes::RST, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,    16,16,0x20}, //0xE7 RST 20H
    {OpTypes::ADDWS, OperandTypes::SP, OperandTypes::ImmediateS8, OperandMem::Const, OperandMem::Const,  16,16}, //0xE8 ADD SP s8
    {OpTypes::JP, OperandTypes::HL, OperandTypes::None, OperandMem::Const, OperandMem::Const,        4,4}, //0xE9 JP (HL) (MODIFIED)
    {OpTypes::LD, OperandTypes::Address16, OperandTypes::A, OperandMem::Indirected, OperandMem::Const,  16,16}, //0xEA LD (a16) A
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4,4}, //0xEB
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4,4}, //0xEC
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4,4}, //0xED
    {OpTypes::XOR, OperandTypes::A, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,       8,8}, //0xEE XOR d8
    {OpTypes::RST, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,   16,16,0x28}, //0xEF RST 28H

    {OpTypes::LDH, OperandTypes::A, OperandTypes::Address8, OperandMem::Const, OperandMem::Indirected,  12,12}, //0xF0 LDH A (a8)
    {OpTypes::POP, OperandTypes::AF, OperandTypes::None, OperandMem::Const, OperandMem::Const,          12,12}, //0xF1 POP AF
    {OpTypes::LD, OperandTypes::A, OperandTypes::C, OperandMem::Const, OperandMem::Indirected,            8,8}, //0xF2 LD A (C)
    {OpTypes::DI, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,           4,4}, //0xF3 DI
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4,4}, //0xF4
    {OpTypes::PUSH, OperandTypes::AF, OperandTypes::None, OperandMem::Const, OperandMem::Const,         16,16}, //0xF5 PUSH AF
    {OpTypes::OR, OperandTypes::A, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,        8,8}, //0xF6 OR d8
    {OpTypes::RST, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,   16,16,0x30}, //0xF7 RST 30H
    {OpTypes::LDF8, OperandTypes::HL, OperandTypes::ImmediateS8, OperandMem::Const, OperandMem::Const, 12,12 }, //0xF8 LD HL SP + r8
    {OpTypes::LDW, OperandTypes::SP, OperandTypes::HL, OperandMem::Const, OperandMem::Const,            8,8  }, //0xF9 LD HL SP
    {OpTypes::LD, OperandTypes::A, OperandTypes::Address16, OperandMem::Const, OperandMem::Indirected,  12,12}, //0xFA LD A (a16)
    {OpTypes::EI, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,          4, 4}, //0xF EI
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4,4}, //0xFC
    {OpTypes::NOOP, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,         4,4}, //0xFD
    {OpTypes::CP, OperandTypes::A, OperandTypes::Immediate8, OperandMem::Const, OperandMem::Const,        8,8}, //0xFE CP d8
    {OpTypes::RST, OperandTypes::None, OperandTypes::None, OperandMem::Const, OperandMem::Const,   16,16,0x38}  //0xFF RST 38H

};

OpCodeEntry CBCodes[]=
{
    {OpTypes::RLC, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x00 RLC B
    {OpTypes::RLC, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x01 RLC C
    {OpTypes::RLC, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x02 RLC D
    {OpTypes::RLC, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x03 RLC E
    {OpTypes::RLC, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x04 RLC H
    {OpTypes::RLC, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x05 RLC L
    {OpTypes::RLC, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,    16, 16}, //0x06 RLC (HL)
    {OpTypes::RLC, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x07 RLC A
    {OpTypes::RRC, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x08 RRC B
    {OpTypes::RRC, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x09 RRC C
    {OpTypes::RRC, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x0A RRC D
    {OpTypes::RRC, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x0B RRC E
    {OpTypes::RRC, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x0C RRC H
    {OpTypes::RRC, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x0D RRC L
    {OpTypes::RRC, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,    16, 16}, //0x0E RRC (HL)
    {OpTypes::RRC, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x0F RRC A


    {OpTypes::RL, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x10 RL B
    {OpTypes::RL, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x11 RL C
    {OpTypes::RL, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x12 RL D
    {OpTypes::RL, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x13 RL E
    {OpTypes::RL, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x14 RL H
    {OpTypes::RL, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x15 RL L
    {OpTypes::RL, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,    16, 16}, //0x16 RL (HL)
    {OpTypes::RL, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x17 RL A
    {OpTypes::RR, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x18 RR B
    {OpTypes::RR, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x19 RR C
    {OpTypes::RR, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x1A RR D
    {OpTypes::RR, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x1B RR E
    {OpTypes::RR, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x1C RR H
    {OpTypes::RR, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x1D RR L
    {OpTypes::RR, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,    16, 16}, //0x1E RR (HL)
    {OpTypes::RR, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,           8,  8}, //0x1F RR A


    {OpTypes::SLA, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x20 SLA B
    {OpTypes::SLA, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x21 SLA C
    {OpTypes::SLA, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x22 SLA D
    {OpTypes::SLA, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x23 SLA E
    {OpTypes::SLA, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x24 SLA H
    {OpTypes::SLA, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x25 SLA L
    {OpTypes::SLA, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,   16, 16}, //0x26 SLA (HL)
    {OpTypes::SLA, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x27 SLA A
    {OpTypes::SRA, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x28 SRA B
    {OpTypes::SRA, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x29 SRA C
    {OpTypes::SRA, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x2A SRA D
    {OpTypes::SRA, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x2B SRA E
    {OpTypes::SRA, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x2C SRA H
    {OpTypes::SRA, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x2D SRA L
    {OpTypes::SRA, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,   16, 16}, //0x2E SRA (HL)
    {OpTypes::SRA, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x2F SRA A



    {OpTypes::SWAP, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8}, //0x30 SWAP B
    {OpTypes::SWAP, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8}, //0x31 SWAP C
    {OpTypes::SWAP, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8}, //0x32 SWAP D
    {OpTypes::SWAP, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8}, //0x33 SWAP E
    {OpTypes::SWAP, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8}, //0x34 SWAP H
    {OpTypes::SWAP, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8}, //0x35 SWAP L
    {OpTypes::SWAP, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16}, //0x36 SWAP (HL)
    {OpTypes::SWAP, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8}, //0x37 SWAP A
    {OpTypes::SRL, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x38 SRL B
    {OpTypes::SRL, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x39 SRL C
    {OpTypes::SRL, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x3A SRL D
    {OpTypes::SRL, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x3B SRL E
    {OpTypes::SRL, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x3C SRL H
    {OpTypes::SRL, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x3D SRL L
    {OpTypes::SRL, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,   16, 16}, //0x3E SRL (HL)
    {OpTypes::SRL, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,          8,  8}, //0x3F SRL A

    {OpTypes::BIT, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x0
    {OpTypes::BIT, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x1
    {OpTypes::BIT, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x2
    {OpTypes::BIT, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x3
    {OpTypes::BIT, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x4
    {OpTypes::BIT, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x5
    {OpTypes::BIT, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 0}, //0x6
    {OpTypes::BIT, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x7
    {OpTypes::BIT, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0x8
    {OpTypes::BIT, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0x9
    {OpTypes::BIT, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xA
    {OpTypes::BIT, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xB
    {OpTypes::BIT, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xC
    {OpTypes::BIT, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xD
    {OpTypes::BIT, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 1}, //0xE
    {OpTypes::BIT, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xF


    {OpTypes::BIT, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x0
    {OpTypes::BIT, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x1
    {OpTypes::BIT, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x2
    {OpTypes::BIT, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x3
    {OpTypes::BIT, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x4
    {OpTypes::BIT, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x5
    {OpTypes::BIT, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 2}, //0x6
    {OpTypes::BIT, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x7
    {OpTypes::BIT, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0x8
    {OpTypes::BIT, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0x9
    {OpTypes::BIT, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xA
    {OpTypes::BIT, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xB
    {OpTypes::BIT, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xC
    {OpTypes::BIT, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xD
    {OpTypes::BIT, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 3}, //0xE
    {OpTypes::BIT, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xF


    {OpTypes::BIT, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x0
    {OpTypes::BIT, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x1
    {OpTypes::BIT, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x2
    {OpTypes::BIT, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x3
    {OpTypes::BIT, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x4
    {OpTypes::BIT, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x5
    {OpTypes::BIT, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 4}, //0x6
    {OpTypes::BIT, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x7
    {OpTypes::BIT, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0x8
    {OpTypes::BIT, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0x9
    {OpTypes::BIT, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xA
    {OpTypes::BIT, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xB
    {OpTypes::BIT, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xC
    {OpTypes::BIT, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xD
    {OpTypes::BIT, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 5}, //0xE
    {OpTypes::BIT, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xF


    {OpTypes::BIT, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x0
    {OpTypes::BIT, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x1
    {OpTypes::BIT, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x2
    {OpTypes::BIT, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x3
    {OpTypes::BIT, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x4
    {OpTypes::BIT, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x5
    {OpTypes::BIT, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 6}, //0x6
    {OpTypes::BIT, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x7
    {OpTypes::BIT, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0x8
    {OpTypes::BIT, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0x9
    {OpTypes::BIT, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xA
    {OpTypes::BIT, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xB
    {OpTypes::BIT, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xC
    {OpTypes::BIT, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xD
    {OpTypes::BIT, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 7}, //0xE
    {OpTypes::BIT, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xF


    {OpTypes::RES, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x0
    {OpTypes::RES, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x1
    {OpTypes::RES, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x2
    {OpTypes::RES, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x3
    {OpTypes::RES, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x4
    {OpTypes::RES, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x5
    {OpTypes::RES, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 0}, //0x6
    {OpTypes::RES, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x7
    {OpTypes::RES, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0x8
    {OpTypes::RES, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0x9
    {OpTypes::RES, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xA
    {OpTypes::RES, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xB
    {OpTypes::RES, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xC
    {OpTypes::RES, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xD
    {OpTypes::RES, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 1}, //0xE
    {OpTypes::RES, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xF


    {OpTypes::RES, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x0
    {OpTypes::RES, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x1
    {OpTypes::RES, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x2
    {OpTypes::RES, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x3
    {OpTypes::RES, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x4
    {OpTypes::RES, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x5
    {OpTypes::RES, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 2}, //0x6
    {OpTypes::RES, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x7
    {OpTypes::RES, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0x8
    {OpTypes::RES, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0x9
    {OpTypes::RES, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xA
    {OpTypes::RES, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xB
    {OpTypes::RES, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xC
    {OpTypes::RES, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xD
    {OpTypes::RES, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 3}, //0xE
    {OpTypes::RES, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xF


    {OpTypes::RES, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x0
    {OpTypes::RES, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x1
    {OpTypes::RES, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x2
    {OpTypes::RES, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x3
    {OpTypes::RES, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x4
    {OpTypes::RES, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x5
    {OpTypes::RES, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 4}, //0x6
    {OpTypes::RES, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x7
    {OpTypes::RES, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0x8
    {OpTypes::RES, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0x9
    {OpTypes::RES, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xA
    {OpTypes::RES, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xB
    {OpTypes::RES, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xC
    {OpTypes::RES, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xD
    {OpTypes::RES, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 5}, //0xE
    {OpTypes::RES, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xF


    {OpTypes::RES, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x0
    {OpTypes::RES, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x1
    {OpTypes::RES, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x2
    {OpTypes::RES, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x3
    {OpTypes::RES, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x4
    {OpTypes::RES, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x5
    {OpTypes::RES, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 6}, //0x6
    {OpTypes::RES, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x7
    {OpTypes::RES, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0x8
    {OpTypes::RES, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0x9
    {OpTypes::RES, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xA
    {OpTypes::RES, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xB
    {OpTypes::RES, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xC
    {OpTypes::RES, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xD
    {OpTypes::RES, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 7}, //0xE
    {OpTypes::RES, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xF


    {OpTypes::SET, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x0
    {OpTypes::SET, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x1
    {OpTypes::SET, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x2
    {OpTypes::SET, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x3
    {OpTypes::SET, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x4
    {OpTypes::SET, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x5
    {OpTypes::SET, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 0}, //0x6
    {OpTypes::SET, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 0}, //0x7
    {OpTypes::SET, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0x8
    {OpTypes::SET, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0x9
    {OpTypes::SET, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xA
    {OpTypes::SET, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xB
    {OpTypes::SET, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xC
    {OpTypes::SET, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xD
    {OpTypes::SET, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 1}, //0xE
    {OpTypes::SET, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 1}, //0xF


    {OpTypes::SET, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x0
    {OpTypes::SET, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x1
    {OpTypes::SET, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x2
    {OpTypes::SET, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x3
    {OpTypes::SET, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x4
    {OpTypes::SET, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x5
    {OpTypes::SET, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 2}, //0x6
    {OpTypes::SET, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 2}, //0x7
    {OpTypes::SET, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0x8
    {OpTypes::SET, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0x9
    {OpTypes::SET, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xA
    {OpTypes::SET, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xB
    {OpTypes::SET, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xC
    {OpTypes::SET, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xD
    {OpTypes::SET, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 3}, //0xE
    {OpTypes::SET, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 3}, //0xF


    {OpTypes::SET, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x0
    {OpTypes::SET, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x1
    {OpTypes::SET, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x2
    {OpTypes::SET, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x3
    {OpTypes::SET, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x4
    {OpTypes::SET, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x5
    {OpTypes::SET, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 4}, //0x6
    {OpTypes::SET, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 4}, //0x7
    {OpTypes::SET, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0x8
    {OpTypes::SET, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0x9
    {OpTypes::SET, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xA
    {OpTypes::SET, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xB
    {OpTypes::SET, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xC
    {OpTypes::SET, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xD
    {OpTypes::SET, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 5}, //0xE
    {OpTypes::SET, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 5}, //0xF


    {OpTypes::SET, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x0
    {OpTypes::SET, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x1
    {OpTypes::SET, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x2
    {OpTypes::SET, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x3
    {OpTypes::SET, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x4
    {OpTypes::SET, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x5
    {OpTypes::SET, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 6}, //0x6
    {OpTypes::SET, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 6}, //0x7
    {OpTypes::SET, OperandTypes::B, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0x8
    {OpTypes::SET, OperandTypes::C, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0x9
    {OpTypes::SET, OperandTypes::D, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xA
    {OpTypes::SET, OperandTypes::E, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xB
    {OpTypes::SET, OperandTypes::H, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xC
    {OpTypes::SET, OperandTypes::L, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xD
    {OpTypes::SET, OperandTypes::HL, OperandTypes::None, OperandMem::Indirected, OperandMem::Const,  16, 16, 7}, //0xE
    {OpTypes::SET, OperandTypes::A, OperandTypes::None, OperandMem::Const, OperandMem::Const,         8,  8, 7}, //0xF

};
