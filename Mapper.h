#ifndef MAPPER_H_INCLUDED
#define MAPPER_H_INCLUDED
#include <vector>
#include <sstream>

class Mapper
{
public:

    typedef uint16_t AddressType;
    typedef uint8_t ValueType;
    typedef std::pair<uint16_t,uint16_t> RangeType;
    typedef uint8_t (*GetValueFunc)(uint16_t, void*);
    typedef void (*SetValueFunc)(uint16_t, uint8_t, void*);

    uint8_t GetValue(uint16_t Address)
    {
        uint32_t Index=ResolveMapperIndex(Address);
        if(Index != Ranges.size())
        {
            if(ShouldSub[Index])
                Address-=Ranges[Index].first;
            return GetFuncs[Index]((Address), Map[Index]);
        }

        std::stringstream ss;
        ss<<"Failed to get unmapped address ";
        GetHex(Address,ss);
        ss <<"\nDump of addresses\n";
        Dump(ss);
        Debug.Log(ss.str().c_str(), DebugLog::MinorError, "Mapper.h");

        //return *FailValue;
    }

    uint8_t* GetPointer(uint16_t Address)
    {
        uint32_t Index=ResolveMapperIndex(Address);
        if(Index != Ranges.size())
        {
            if(ShouldSub[Index])
                Address-=Ranges[Index].first;
            return (uint8_t*)Map[Index] + Address;
        }
        return nullptr;
    }

    void SetValue(uint16_t Address, uint8_t Value)
    {
        uint32_t Index=ResolveMapperIndex(Address);
        if(Index != Ranges.size())
        {
            if(ShouldSub[Index])
                Address-=Ranges[Index].first;
            return SetFuncs[Index]((Address),Value, Map[Index]);
        }

        std::stringstream ss;
        ss<<"Failed to set unmapped address " <<Address <<". Attempting backup Address " <<Ranges[Index-1].first <<".\n";
        Debug.Log(ss.str().c_str(), DebugLog::MinorError, "Mapper.h");
        Index = Ranges.size()-1;
        if(ShouldSub[Index])
            Address-=Ranges[Index].first;
        return SetFuncs[Index]((Address),Value,Map[Index]);
    }

    void SetValues(uint16_t Address, const uint8_t* Values, uint16_t ValueSize)
    {
        for(size_t counter=0; counter<ValueSize; counter++)
            SetValue(Address + counter, Values[counter]);
    }

    void AddEntry(std::pair<uint16_t,uint16_t> Range, void* Pointer, GetValueFunc Get, SetValueFunc Set, bool Sub=true)
    {
        if(CheckInRange(Range.first) || CheckInRange(Range.second) || Range.first > Range.second)
        {
            std::stringstream ss;
            ss <<"Mapper range conflict " <<Range.first <<" "<<Range.second;
            Debug.Log(ss.str().c_str(), DebugLog::MinorError, "Mapper.h");
        }

        uint32_t Index=FindIndexToInsert(Range);
        Ranges.insert(Ranges.begin() + Index, Range);
        Map.insert(Map.begin() + Index, Pointer);
        GetFuncs.insert(GetFuncs.begin() + Index, Get);
        SetFuncs.insert(SetFuncs.begin() + Index, Set);
        ShouldSub.insert(ShouldSub.begin() + Index, Sub);
    }

    uint32_t ResolveMapperIndex(uint16_t Adr)
    {
        if(Ranges.size() == 0)
            return Ranges.size();
        return ResolveMapperIndex(Adr, Ranges.size()-1, 0);
    }

    uint32_t ResolveMapperIndex(uint16_t Adr, uint32_t UpperBounds, uint32_t LowerBounds)
    {
        uint32_t CurrentIndex=(UpperBounds-LowerBounds)/2 + LowerBounds;
        if(Ranges[CurrentIndex].first <= Adr && Ranges[CurrentIndex].second >= Adr)
            return CurrentIndex;
        if(UpperBounds == LowerBounds)
            return Ranges.size();
        if(Adr < Ranges[CurrentIndex].first)
        {
            return ResolveMapperIndex(Adr, CurrentIndex-1, LowerBounds);
        }
        if(Adr > Ranges[CurrentIndex].second)
        {
            return ResolveMapperIndex(Adr, UpperBounds, CurrentIndex+1);
        }
        return 0;
    }

    uint32_t SafeResolveMapperIndex(uint16_t Adr)
    {
        for(uint32_t counter=0; counter<Ranges.size(); counter++)
            if(Ranges[counter].first <= Adr && Ranges[counter].second >= Adr)
            return counter;
        return Ranges.size()-1;
    }

    void RemoveEntry(uint16_t Address)
    {
        uint32_t Index=ResolveMapperIndex(Address);
        Ranges.erase(Ranges.begin() + Index);
        Map.erase(Map.begin() + Index);
        GetFuncs.erase(GetFuncs.begin() + Index);
        SetFuncs.erase(SetFuncs.begin() + Index);
        ShouldSub.erase(ShouldSub.begin() + Index);
    }

    void Dump(std::ostream& ss)
    {
        for(uint32_t counter=0; counter<Ranges.size(); counter++)
        {
            GetHex(Ranges[counter].first, ss);
            ss<<":";
            GetHex(Ranges[counter].second,ss);
            ss<<": ";
            ss<<Map[counter]<<"\n";
        }
    }

protected:

    bool CheckInRange(uint16_t Address)
    {
        for(uint32_t counter=0; counter<Ranges.size(); counter++)
            if(Address >= Ranges[counter].first && Address <= Ranges[counter].second)
            return true;
        return false;
    }

    uint32_t FindIndexToInsert(std::pair<uint16_t, uint16_t> Range)
    {
        for(uint32_t counter=0; counter<Ranges.size(); counter++)
            if(Ranges[counter].first > Range.first)
            return counter;
        return Ranges.size();
    }

private:

    uint8_t* FailValue=nullptr;
    std::vector<RangeType> Ranges;
    std::vector<void*> Map;
    std::vector<GetValueFunc> GetFuncs;
    std::vector<SetValueFunc> SetFuncs;
    std::vector<bool> ShouldSub;

};



#endif // MAPPER_H_INCLUDED
