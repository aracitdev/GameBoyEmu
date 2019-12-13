#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

class Input
{
public:

    void Init(Mmu* M)
    {
        MMU=M;
        KeyReg=MMU->HardwareRegisters;
        KeyReg=0;
    }

    void Tick(void)
    {
    }

private:
    Mmu* MMU;
    uint8_t* KeyReg;
    uint8_t PriorKeyReg;
};

#endif // INPUT_H_INCLUDED
