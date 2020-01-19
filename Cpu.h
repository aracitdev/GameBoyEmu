/**
 * \file Cpu.h
 * \author Sean C
 * \version 1.0
 * Defines the implementation of the cpu emulation.
 */


#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <fstream>

#include "MemoryMap.h"
#include "Mmu.h"
#include "BitFunctions.h"
#include "Instruction/OpCodes.h"
#include "Refference.h"
#include "Instruction/OpCodeTable.h"


extern uint16_t InterruptVector[]; /**<Contains a list of positions where interrupts return to*/

extern const char* IntterruptTypes[]; /**<Contains a list of human readable interrupt names*/

class Cpu
{
public:

/**
 * \enum InterruptTypes
 * Enumeration of the different types of interrupts
 */

    enum InterruptTypes
    {
        VBLANK=0,  /**<Screen draw interrupt*/
        LCDSTAT=1, /**<LY is at the value specified in the LCDSTAT interrupt bits*/
        TIMER=2,   /**<TIMER interrupt from set bits*/
        SERIAL=3,  /**<Unimplemented, but serial data communications*/
        JOYPAD=4   /**<Usually unused, but interrupts on a button press*/
    };

    uint8_t* CpuFlags=(uint8_t*)(&AF); //flags of the cpu
    //Bits are like this:
    //  7   6   5   4   3   2   1   0
    //  Z   N   H   C   0   0   0   0
    //  Z- Zero Flag        (Set when zero result for some operations)
    //  N- Subtract Flag    (Set when a subtraction occurs)
    //  H- Half Carry Flag  (Set when the first 4 bits overflows)
    //  C- Carry Flag       (Set when there is an 8 bit overflow)

/**
 * \fn Cpu(Mmu& m)
 * \param m A reference to the MMU
 * Initializes the Cpu to a zero state.
 */
    Cpu(Mmu& m);

/**
 * \fn void Init(void)
 * Initializes the Cpu for running by getting register pointers.
 */
    void Init(void);


/**
 * \fn void RequestInterrupt(InterruptTypes I)
 * \param I The type of interrupt to set
 * Sets the interrupts register to cause an interrupt on the next cpu tick
 * of the type specified.
 */
    void RequestInterrupt(InterruptTypes I);

    //Pair Registers
    uint16_t AF= 0x01B0; /**<Default value of AF register, Accumulator/Flags*/
    uint16_t BC= 0x0013; /**<Default value of BC*/
    uint16_t DE= 0x00D8; /**<Default value of DE*/
    uint16_t HL= 0x014D; /**<Default value of HL*/
    ConstRef Const;      /**<Used in ResolveValue for immediates*/
    ConditionalRef Cond; /**<Used in ResolveValue for instructions that depend on conditions*/

    MemRef DeRef;        /**<Used in ResolveValue for instructions that depend on a DeRefference*/

    RegRef AFRef;        /**<Reg refference to the AF Register*/
    RegRef BCRef;        /**<Reg refference to the BC Register*/
    RegRef DERef;        /**<Reg refference to the DE Register*/
    RegRef HLRef;        /**<Reg refference to the HL Register*/
    RegRef SPRef;        /**<Reg refference to the SP Register*/
    RegRef PCRef;        /**<Reg refference to the PC Register*/

    //Pointers to single registers
    //Note: Registers are stored in little endian
    //Example: A = &AF + 1, F= &AF
    uint8_t* A=(uint8_t*)&AF+1; /**<Pointer to the A byte of AF*/
    uint8_t* F=(uint8_t*)&AF;   /**<Pointer to the F byte of AF*/
    RegRef ARef;        /**<Register reference to just A*/
    RegRef FRef;        /**<Register reference to just F*/


    uint8_t* B=(uint8_t*)&BC+1; /**<Pointer to the B byte of BC*/
    uint8_t* C=(uint8_t*)&BC;   /**<Pointer to the C byte of BC*/

    RegRef BRef;        /**<Register reference to just B*/
    RegRef CRef;        /**<Register reference to just C*/

    uint8_t* D=(uint8_t*)&DE+1; /**<Pointer to the D byte of DE*/
    uint8_t* E=(uint8_t*)&DE;   /**<Pointer to the E byte of DE*/

    RegRef DRef;        /**<Register reference to just D*/
    RegRef ERef;        /**<Register reference to just E*/

    uint8_t* H=(uint8_t*)&HL+1; /**<Pointer to the H byte of HL*/
    uint8_t* L=(uint8_t*)&HL; /**<Pointer to the L byte of HL*/


    RegRef HRef;        /**<Register reference to just H*/
    RegRef LRef;        /**<Register reference to just L*/

    uint16_t PC;    /**<Program counter register*/
    uint16_t SP=0xFFFE; /**<Stack pointer register*/



/**
 * \fn void SetZeroFlag(bool Value)
 * \param Value the value to set the zero flag to
 * Sets the zero flag bit of the F register to value.
 */
    void SetZeroFlag(bool Value);

/**
 * \fn void SetSubtractFlag(bool Value)
 * \param Value the value to set the subtract flag to
 * Sets the subtract flag bit of the F register to value.
 */
    void SetSubtractFlag(bool Value);

/**
 * \fn void SetHalfCarryFlag(bool Value)
 * \param Value the value to set the half carry flag to
 * Sets the half carry flag bit of the F register to value.
 */
    void SetHalfCaryFlag(bool Value);

/**
 * \fn void SetCarryFlag(bool Value)
 * \param Value the value to set the carry flag to
 * Sets the carry flag bit of the F register to value.
 */
    void SetCarryFlag(bool Value);

/**
 * \fn bool ZeroFlag(void)
 * \return The value of the zero flag.
 * Gets the value of the zero flag from F.
 */
    bool ZeroFlag(void);

/**
 * \fn bool SubtractFlag(void)
 * \return The value of the subtract flag.
 * Gets the value of the subtract flag from F.
 */
    bool SubtractFlag(void);

/**
 * \fn bool HalfCarryFlag(void)
 * \return The value of the half carry flag.
 * Gets the value of the half carry flag from F.
 */
    bool HalfCarryFlag(void);

/**
 * \fn bool CarryFlag(void)
 * \return The value of the carry flag.
 * Gets the value of the carry flag from F.
 */
    bool CarryFlag(void);

    Mmu* MMU;   /**<A pointer to the MMU*/

/**
 * \fn uint8_t GetByte(void)
 * \return The value obtained from the PC.
 * Gets an unsigned byte from the address in PC, then increments the PC
 */
    uint8_t GetByte(void);


/**
 * \fn int8_t GetSignedByte(void)
 * \return The value obtained from the PC.
 * Gets a signed byte from the address in PC, then increments the PC
 */
int8_t GetSignedByte(void);

/**
 * \fn uint16_t GetWord(void)
 * \return The value obtained from the PC.
 * Gets 2 bytes from the address in the PC, incrementing the PC by 2
 * and composing them into a word, returning it.
 */
    uint16_t GetWord(void);


/**
 * \fn MemRef* Resolve(uint16_t Address)
 * \param Address The address to get a MemRef of
 * \return The reference to the address.
 * Creates a reference to the given address and returns it for usage.
 */
    MemRef* Resolve(uint16_t Address);

/**
 * \fn void Push(uint16_t Value)
 * \param Value The value to push to the stack.
 * Pushes a value to the stack and then decreases the stack pointer by 2 (the size of the value)
 */
    void Push(uint16_t Value);


/**
 * \fn void HandleInterrupts(void)
 * Used internally, handles all the interrupts.
 */
    void HandleInterrupts(void);

/**
 * \fn void Pop(uint16_t& Value)
 * \param Value A reference to save the popped values to.
 * Pops a value from the stack pointer, and increases the stack pointer by 2.
 */
    void Pop(uint16_t& Value);

/**
 * \fn uint16_t HandleCB(void)
 * \return The number of cycles this instruction took.
 * Handles the extended CB type instructions.
 */
    uint16_t HandleCB(void);

/**
 * \fn Reference* ResolveValue(OperandTypes Type, OperandMem Mem)
 * \param Type The type of operand this value is (Register, Memory, Immediate).
 * \param Mem The type of memory indirection used (Indirected, NonIndirected)
 * \return The reference to the operand.
 * Gets a reference to the operand based off of its type and indirection so
 * it can be used by operations.
 */
    Refference* ResolveValue(OperandTypes Type, OperandMem);

/**
 * \fn uint16_t Tick(void)
 * \return The number of clocks taken this cpu tick.
 * Executes one instruction at the PC, handles any interrupts (assuming the cpu is running).
 */
    uint16_t Tick(void);

    uint8_t* IntterruptsEnabled;    /**<A pointer to the InterruptsEnabled hardware register, each
                                        bit specifies whether a certain type of interrupt is enabled*/
    uint8_t* IntterruptFlag;        /**<A pointer to the InterruptFlag hardware register, each bit
                                        specifies whether there is an interrupt for that type*/
    bool IEnabled=true;             /**<Whether interrupts are enabled or not (RETI, DE, and IE affect this)*/
    bool Halted=false;              /**<Whether or not the processor is haulted (and waiting for an interrupt)*/
    bool Stopped=false;             /**<Specifies whether or not the processor is stopped (it will not restart)*/

/**
 * \fn void DumpRegisters(std::ostream& out)
 * \param out The stream to write to.
 * Writes the current value of the internal registers to a stream
 */
    void DumpRegisters(std::ostream& out);

/**
 * \fn bool SaveState(std::ofstream& out)
 * \param out The stream to save the state to.
 * \return True on success, false on failure.
 * Saves the processor state to the stream.
 */
    bool SaveState(std::ofstream& out);

/**
 * \fn bool LoadState(std::ifstream& in)
 * \param in the stream to load the state from.
 * \return True on success, false on failure.
 * Loads the state of the processor from the stream
 */
    bool LoadState(std::ifstream& in);

    uint8_t OpCode; /**<The last opcode byte run, for debugging*/
    bool OpCodeCB;  /**<Whether or not the last opcode was cb or not*/

private:
};

#include "TableGenerator.h"

#include "Instruction/Arithmetic.h"
#include "Instruction/Memory.h"
#include "Instruction/Control.h"
#include "OpFuncs.h"


#endif // CPU_H_INCLUDED
