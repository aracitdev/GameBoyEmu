#include "DebugLog.h"

template <typename I> std::string GetHex(I w, size_t hex_len)
{
    static const char* digits = "0123456789ABCDEF";
    std::string rc(hex_len,'0');
    for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}

template <typename I> void GetHex(I w, std::ostream& ss, size_t hex_len)
{
    ss <<std::string("0x");
    static const char* digits = "0123456789ABCDEF";
    for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
        ss << digits[(w>>j) & 0x0f];
}

template std::string GetHex<uint32_t>(uint32_t,size_t);
template std::string GetHex<uint16_t>(uint16_t,size_t);
template std::string GetHex<uint8_t> (uint8_t,size_t);
template void GetHex<uint32_t>(uint32_t,std::ostream&, size_t);
template void GetHex<uint16_t>(uint16_t,std::ostream&, size_t);
template void GetHex<uint8_t>(uint8_t,std::ostream&, size_t);


DebugLog::~DebugLog()
{
    for(uint32_t counter=0; counter<ManagedStreams.size(); counter++)
        if(ManagedStreams[counter])
            delete ManagedStreams[counter];
    ManagedStreams.clear();
}



void DebugLog::AddManagedStream(std::ostream* Managed)
{
    ManagedStreams.push_back(Managed);
}

void DebugLog::AddStream(std::ostream* UnManaged)
{
    Streams.push_back(UnManaged);
}

void DebugLog::Log(const char* Message, DebugLevels Level, const char* FileName)
{
    for(uint32_t counter=0; counter<ManagedStreams.size(); counter++)
        *(ManagedStreams[counter]) <<std::string(FileName) <<':'<<std::string(DebugLevelNames[(uint8_t)Level])<<':'<<std::string(Message)<<'\n';
    for(uint32_t counter=0; counter<Streams.size(); counter++)
        *(Streams[counter]) <<std::string(FileName) <<':'<<std::string(DebugLevelNames[(uint8_t)Level])<<':'<<std::string(Message)<<'\n';
}

void DebugLog::RemoveManagedStream(std::ostream* out)
{
    auto it=std::find(ManagedStreams.begin(), ManagedStreams.end(), out);
    if(it != ManagedStreams.end())
    {
        delete *it;
        ManagedStreams.erase(it);
    }
}

void DebugLog::RemoveStream(std::ostream* out)
{
    auto it=std::find(Streams.begin(), Streams.end(), out);
    if(it != Streams.end())
    {
        Streams.erase(it);
    }
}

std::vector<std::ostream*> DebugLog::GetStreamsList(void)
{
    std::vector<std::ostream*> ReturnV;
    ReturnV.insert(ReturnV.begin(), ManagedStreams.begin(), ManagedStreams.end());
    ReturnV.insert(ReturnV.begin(), Streams.begin(), Streams.end());
    return ReturnV;
}

const char* DebugLog::DebugLevelNames[]= {"Info", "Debug", "MinorError", "FatalError"};

//DebugLog Debug;
