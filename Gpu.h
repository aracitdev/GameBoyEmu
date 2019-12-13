#ifndef GPU_H_INCLUDED
#define GPU_H_INCLUDED
#include "MemoryMap.h"
#include "Memory.h"
#include "Cpu.h"
#include "Mmu.h"
#include <SFML/Graphics.hpp>

extern const uint16_t ClocksPerHBLANK;
extern const uint16_t ClocksPerScanlineOEM;
extern const uint16_t ClocksPerScanlineVRAM;
extern const uint16_t ClocksPerScanline;
extern const uint16_t ClocksPerVBLANK;
extern const uint16_t ScalinesPerFrame;
extern const uint32_t ClocksPerFrame;

extern const uint8_t GameboyScreenX;
extern const uint8_t GameboyScreenY;
extern const uint16_t BgScreenX;
extern const uint16_t BgScreenY;

extern const char* ColorStrings[];
extern const sf::Color ColorSet[];


enum class Color
{
    White,
    LightGray,
    DarkGray,
    Black
};

extern const char* ColorStrings[4];

enum class VideoMode
{
    ACCESS_OAM,
    ACCESS_VRAM,
    HBLANK,
    VBLANK
};

extern const sf::Color ColorSet[5];
#include "Video/Pallete.h"
#include "Video/Tile.h"

class Mmu;

class Gpu
{
public:

    Gpu();
    void Write(uint16_t Address, uint8_t Value);
    uint8_t Read(uint16_t Address);
    uint8_t* GetPointer(uint16_t Address);

    void DrawScanline(void);

    void Tick(uint16_t AddedCycles);
    void Render(bool shouldUpdate=true);
    void DoDMATransfer(void);
    void Clear(void);
    void Init(sf::RenderWindow& W, uint8_t* I, Mmu* M);

    std::array<Color, 8> GetTileScanline(uint8_t Scanline, uint8_t TileNumber);

    void DumpCharMemory(std::ostream& out);

    uint8_t* GetCharMemory(uint8_t T);

    uint8_t* GetCharMemory(uint8_t T, bool B);

    void DumpCharMemoryAsImage(std::string filename);


    uint8_t BGMap[MemoryMap::BGMap1Size + MemoryMap::BGMap2Size];
    uint8_t OEM[MemoryMap::OemSize];
    uint8_t CharMemory[MemoryMap::CRamSize];

    sf::Image Image;
    sf::Texture InternalTexture;
    sf::RenderWindow* Window;

    uint8_t* LcdStatusRegister;
    uint8_t* LCDC;
    uint8_t* InterruptFlag;
    uint8_t* ScrollX;
    uint8_t* ScrollY;

    uint16_t CurrentScanline;
    uint16_t CurrentCycles=0;
    VideoMode CurrentMode;
    sf::Sprite Sprite;
    Gpu* GPU;
    Mmu* MMU;
    bool DmaTransferStarted;
    uint8_t FrameSkip=2;
    uint8_t CurrentFrame=0;
private:
};


#endif // GPU_H_INCLUDED
