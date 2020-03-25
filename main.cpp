#include <iostream>
#include "DebugLog.h"
DebugLog Debug;
#include "GameBoy.h"
#include "TableGenerator.h"
#include <fstream>

uint8_t* GetFileBuffer(const std::string& file, size_t& FileSize)
{
    std::ifstream f(file.c_str(), std::ios::binary | std::ios::ate);
    if(!f.is_open())
    {
        FileSize = 0;
        return nullptr;
    }
    FileSize = f.tellg();
    f.seekg(0, std::ios::beg);

    uint8_t* buffer= new uint8_t[FileSize];
    f.read((char*)buffer, FileSize);
    return buffer;
}

std::ostream* CreateFileStream(const std::string& file)
{
    std::ofstream* returnv=new std::ofstream(file.c_str());
    if(!returnv)
        return nullptr;
    if(!returnv->is_open())
    {
        delete returnv;
        return nullptr;
    }
    return returnv;
}

int main()
{
    std::ofstream out;
    out.open("Table.csv", std::ostream::out | std::ostream::trunc);
    //CSVDump(out);
    out.close();

    Debug.AddStream(&std::cout);
    Debug.AddManagedStream(CreateFileStream("Log.txt"));

    std::cout <<"Dump over.\nEnter file name.\n";
    size_t FileSize;
    std::string filename;
    getline(std::cin, filename);
    uint8_t* Buffer=GetFileBuffer(filename.c_str(), FileSize);
    if(!Buffer)
    {
        Debug.Log("Failed to open the file specified.", DebugLog::FatalError, "main.cpp");
        return 0;
    }
    GameBoy GB;
    sf::RenderWindow Window;
    if(!GB.Init(Buffer, FileSize, Window, filename))
    {
        Debug.Log("Failed to initialize the gameboy emulator", DebugLog::FatalError, "main.cpp");
        return 0;
    }
    GB.Cartridge->Head.Dump(std::cout);
    if(GB.Cartridge->ContainsSRAM())
    {
        std::ifstream file;
        file.open((filename + std::string(".sav")).c_str(), std::ifstream::in | std::ifstream::binary);
        if(!file.is_open())
            GB.Cartridge->LoadRam(file);
        file.close();
    }
    GB.Run();

    if(GB.Cartridge->ContainsSRAM())
    {
        //save the SRAM
        std::ofstream file;
        file.open((filename + std::string(".sav")).c_str(), std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);
        if(file.is_open())
            GB.Cartridge->SaveRam(file);
        else
            std::cout <<"Failed to open " <<filename <<".sav for saving SRAM\n";
        file.close();
    }
    return 0;
}
