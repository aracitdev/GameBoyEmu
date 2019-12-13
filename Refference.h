#ifndef REFFERENCE_H_INCLUDED
#define REFFERENCE_H_INCLUDED
#include <cstdint>

class Mmu;

enum class RefferenceTypes
{
    Conditional,
    Memory,
    Register,
    Constant
};

class Refference
{
public:

    void SetMmu(Mmu* M);


    virtual uint8_t Get(void)=0;
    virtual uint16_t Get16(void)=0;
    virtual void Set(uint8_t)=0;
    virtual void Set(uint16_t)=0;
    virtual Refference* DeRef(void)=0;


    RefferenceTypes Type;
protected:
    Mmu* Mem;

};

class MemRef: public Refference
{

public:
    MemRef(uint16_t Value, Mmu* M);

    virtual uint8_t Get(void);
    virtual uint16_t Get16(void);

    virtual void Set(uint8_t v);
    virtual void Set(uint16_t v);
    virtual Refference* DeRef(void);

    void SetAddress(uint16_t Ad);

    uint16_t Adr;
};

class RegRef: public Refference
{
public:

    RegRef(uint8_t& Value, Mmu* M);

    RegRef(uint16_t& Value, Mmu* M);

    virtual uint8_t Get(void);
    virtual uint16_t Get16(void);
    virtual void Set(uint8_t v);

    virtual void Set(uint16_t v);
    virtual Refference* DeRef(void);



private:
    uint8_t* Int;
};

class ConstRef: public Refference
{
public:
    ConstRef(int32_t V, Mmu* M);

    virtual uint8_t Get(void);

    virtual uint16_t Get16(void);
    virtual void Set(uint8_t v);

    virtual void Set(uint16_t v);

    virtual Refference* DeRef(void);


private:
    int32_t Value;
};

class ConditionalRef: public Refference
{
public:
    ConditionalRef(bool V, Mmu* M);

    virtual uint8_t Get(void);
    virtual uint16_t Get16(void);


    virtual void Set(uint8_t v);

    virtual void Set(uint16_t v);

    virtual Refference* DeRef(void);


private:
    bool Value;
};

#endif // REFFERENCE_H_INCLUDED
