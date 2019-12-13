#ifndef DEBUGLOG_H_INCLUDED
#define DEBUGLOG_H_INCLUDED
#include <vector>
#include <algorithm>
#include <fstream>

template <typename I> std::string GetHex(I w, size_t hex_len = sizeof(I)<<1);

template <typename I> void GetHex(I w, std::ostream& ss, size_t hex_len = sizeof(I)<<1);

class DebugLog
{
public:


    ~DebugLog();

    enum DebugLevels
    {
        Info,
        Debug,
        MinorError,
        FatalError
    };

    const static char* DebugLevelNames[];

    void AddManagedStream(std::ostream* Managed);

    void AddStream(std::ostream* UnManaged);

    void Log(const char* Message, DebugLevels Level, const char* FileName);

    void RemoveManagedStream(std::ostream* out);

    void RemoveStream(std::ostream* out);

    std::vector<std::ostream*> GetStreamsList(void);

private:
    std::vector<std::ostream*> ManagedStreams;
    std::vector<std::ostream*> Streams;
};


extern DebugLog Debug;
#endif // DEBUG_H_INCLUDED
