#include "Control.h"

bool NOOP(Cpu*, OpCodeEntry*){return true;}

bool JP(Cpu* C, OpCodeEntry* Op)
{
    Refference* Cond=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* JumpLoc=nullptr;
    if(Cond->Type == RefferenceTypes::Conditional)
    {
        JumpLoc=C->ResolveValue(Op->Types[1], Op->Dir[1]);
        if(!Cond->Get())
            return false; //the condition was false
    }
    else
        JumpLoc=Cond;
    C->PC=JumpLoc->Get16();
    return true;
}

bool JPR(Cpu* C, OpCodeEntry* Op)
{
    Refference* Cond=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* JumpLoc=nullptr;
    if(Cond->Type == RefferenceTypes::Conditional)
    {
        JumpLoc=C->ResolveValue(Op->Types[1], Op->Dir[1]); //we do this before just in case it was an extra byte
        if(!Cond->Get())
        {
            return false; //the condition was false
        }
    }
    else
        JumpLoc=Cond;
    uint8_t OffSetT=JumpLoc->Get();
    int8_t OffSet=*((int8_t*)(&OffSetT));   //convert it to a signed byte
    C->PC+=OffSet;  //add it
    return true;
}

bool CALL(Cpu* C, OpCodeEntry* Op)
{
    Refference* Cond=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    Refference* JumpLoc=nullptr;
    if(Cond->Type == RefferenceTypes::Conditional)
    {
        JumpLoc=C->ResolveValue(Op->Types[1], Op->Dir[1]);
        if(!Cond->Get())
            return false; //the condition was false
    }
    else
        JumpLoc=Cond;
    C->Push(C->PC);
    C->PC=JumpLoc->Get16();
    return true;
}

bool RET(Cpu* C, OpCodeEntry* Op)
{
    Refference* Cond=C->ResolveValue(Op->Types[0], Op->Dir[0]);
    if(Cond && Cond->Type == RefferenceTypes::Conditional && !Cond->Get())
        return false;
    C->Pop(C->PC);
    return true;
}

bool EI(Cpu* C, OpCodeEntry* Op)
{
    C->IEnabled=true;
    return true;
}

bool DI(Cpu* C, OpCodeEntry* Op)
{
    C->IEnabled=false;
    return true;
}

bool HALT(Cpu* C, OpCodeEntry* Op)
{
    C->Halted=true;
    return true;
}

bool STOP(Cpu* C, OpCodeEntry* Op)
{
    C->Stopped=true;
    return true;
}

bool CB(Cpu* C, OpCodeEntry* Op)
{
    Debug.Log("CB\n", DebugLog::Info, "Control.h");
    return true;
}

bool RETI(Cpu* C, OpCodeEntry* Op)
{
    C->Pop(C->PC);
    EI(C,Op);
    return true;
}
