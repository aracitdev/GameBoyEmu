#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED
#include <fstream>

template <class A=size_t>
class DynamicMemory
{
public:
    DynamicMemory(size_t sz)
    {
        Buffer=nullptr;
        Size=sz;
        CreateNew(sz);
    }

    DynamicMemory()
    {
        Buffer=nullptr;
        Size=0;
    }

    void CreateNew(size_t sz)
    {
        Destroy();
        Size=sz;
        Buffer=new uint8_t[Size];
    }

    void Destroy(void)
    {
        if(Buffer != nullptr)
            delete[] Buffer;
        Buffer=nullptr;
    }

    ~DynamicMemory()
    {
        Destroy();
    }


    uint8_t* GetPointer(void)
    {
        return Buffer;
    }

    uint8_t* GetPointer(A Address)
    {
        return &Buffer[Address];
    }

    uint8_t* GetEndPointer(void)
    {
        return Buffer+Size;
    }

    uint8_t GetValue(A Address) const
    {
        return Buffer[Address];
    }

    void SetValue(A Address, uint8_t Value)
    {
        Buffer[Address]=Value;
    }


    void Write(std::ostream& out)
    {
        out.write((char*)Buffer, Size);
    }

    void Read(std::ifstream& in)
    {
        in.read((char*)Buffer,Size);
    }

    void Clear(uint8_t Values)
    {
        for(uint32_t counter=0; counter<Size; counter++)
            Buffer[counter]=Values;
    }

    size_t size(void) const
    {
        return Size;
    }

    bool InRange(A Address)
    {
        return Address < Size;
    }

private:
    size_t Size;
    uint8_t* Buffer;

};

template <size_t sz, class A=size_t>
class StaticMemory
{
public:


    uint8_t* GetPointer(void)
    {
        return Buffer;
    }

    uint8_t* GetPointer(A Address)
    {
        return &Buffer[Address];
    }

    uint8_t* GetEndPointer(void)
    {
        return Buffer+Size;
    }

    uint8_t GetValue(A Address) const
    {
        return Buffer[Address];
    }

    void SetValue(A Address, uint8_t Value)
    {
        Buffer[Address]=Value;
    }

    void SetValues(A Address, uint8_t* Values, size_t Size)
    {
        for(size_t counter=0; counter<Size; counter++)
            SetValue(Address + counter, Values[counter]);
    }


    void Write(std::ostream& out)
    {
        out.write(Buffer, Size);
    }

    void Read(std::ifstream& in)
    {
        in.read(Buffer,Size);
    }

    void Clear(uint8_t Values)
    {
        for(uint32_t counter=0; counter<Size; counter++)
            Buffer[counter]=Values;
    }

    size_t size(void) const
    {
        return Size;
    }

    bool InRange(A Address)
    {
        return Address < Size;
    }

private:

    uint8_t Buffer[sz];
    const size_t Size=sz;
};

#endif // MEMORY_H_INCLUDED
