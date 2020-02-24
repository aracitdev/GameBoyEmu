/**
 * \file Gpu.h
 * \author Sean C
 * \version 1.0
 * Defines the implementation of the gpu emulation.
 */

#ifndef GPU_H_INCLUDED
#define GPU_H_INCLUDED
#include <fstream>
#include <string>
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


/**
 * \enum Color
 * Enumeration for the different possible colors for gameboys.
 */
enum class Color
{
    White,
    LightGray,
    DarkGray,
    Black
};

extern const char* ColorStrings[4];

/**
 * \enum VideoMode
 * Enumeration for the different current video modes
 */
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


/**
 * \class Gpu
 * Defines the implementation for the gpu and image emulation
 */
class Gpu
{
public:

/**
 * \fn Gpu()
 * Initializes the gpu to its default state.
 */
    Gpu();

/**
 * \fn void Write(uint16_t Address, uint8_t Value)
 * \param Address the address to write to (Absolute)
 * \param Value the value to write to address
 * Writes a value to gpu memory.
 */
    void Write(uint16_t Address, uint8_t Value);

/**
 * \fn uint8_t Read(uint16_t Address)
 * \param Address the address to read from (Absolute)
 * \return The byte read from gpu memory.
 * Reads a value from the gpu memory.
 */
    uint8_t Read(uint16_t Address);

/**
 * \fn uint8_t* GetPointer(uint16_t Address)
 * \param Address the address to get a pointer of (Absolute)
 * \return The pointer to the address.
 * Gets a pointer to gpu memory of address.
 */
    uint8_t* GetPointer(uint16_t Address);

/**
 * \fn void DrawScanline(void)
 * Draws a single scanline to the internal image, including sprites and tiles.
 */
    void DrawScanline(void);

/**
 * \fn void Tick(uint16_t AddedCycles)
 * \param AddedCycles The number of cycles since the last call.
 * Ticks the gpu by AddedCycles and handles any updates
 */
    void Tick(uint16_t AddedCycles);

/**
 * \fn void Render(bool shouldUpdate)
 * \param ShouldUpdate whether the texture should update or not.
 * Renders the texture of the gameboy video to the screen.
 */
    void Render(bool shouldUpdate=true);

/**
 * \fn void DoDMATransfer(void)
 * Handles a DMA transfer (video memory transfer)
 */
    void DoDMATransfer(void);

/**
 * \fn void Clear(void)
 * Clears the ameboy screen texture for the next update.
 */
    void Clear(void);

/**
 * \fn void Init(sf::RenderWindow& W, uint8_t* I, Mmu* M)
 * \param W The window to display to.
 * \param I A pointer to the CPU interrupts flag.
 * \param M A pointer to the memory manager unit.
 * Initializes the gpu for drawing.
 */
    void Init(sf::RenderWindow& W, uint8_t* I, Mmu* M);

/**
 * \fn bool SaveState(std::ofstream& out)
 * \param out The stream to save to
 * \return True on success, false on failure.
 * Saves the state of the gpu to out.
 */
    bool SaveState(std::ofstream& out);

/**
 * \fn bool LoadState(std::ifstream& in)
 * \param in The stream to load from.
 * \return True on success, false on failure.
 * Loads the gpu state from in.
 */
    bool LoadState(std::ifstream& in);

    std::array<Color, 8> GetTileScanline(uint8_t Scanline, uint8_t TileNumber);

    void DumpCharMemory(std::ostream& out);

    uint8_t* GetCharMemory(uint8_t T);

    uint8_t* GetCharMemory(uint8_t T, bool B);

    void DumpCharMemoryAsImage(std::string filename);


    uint8_t BGMap[MemoryMap::BGMap1Size + MemoryMap::BGMap2Size]; /**<Memory for the background tileimags*/
    uint8_t OEM[MemoryMap::OemSize];    /**<Sprite data memory*/
    uint8_t CharMemory[MemoryMap::CRamSize]; /**<Memory for the tile images*/

    sf::Image Image;    /**<The gameboy screen image*/
    sf::Texture InternalTexture; /**<A texture for drawing Image (the gameboy screen image)*/
    sf::RenderWindow* Window; /**<A pointer to the window to be drawn to*/

    uint8_t* LcdStatusRegister; /**<A pointer to the LCD status register*/
    uint8_t* LCDC; /**<A pointer to the LCD control register*/
    uint8_t* InterruptFlag; /**<A pointer to the cpu interrupts flag*/
    uint8_t* ScrollX; /**< A pointer to the scrollX io register*/
    uint8_t* ScrollY; /**< A pointer to the scrollY io register*/

    uint16_t CurrentScanline; /**<The current scanline the GPU is on*/
    uint16_t CurrentCycles=0; /**<The number of cycles since the last video mode change*/
    VideoMode CurrentMode; /**<The current mode of the gpu*/
    sf::Sprite Sprite; /**<The sprite used to draw the the gameboy screen*/
    Mmu* MMU;   /**<A pointer to the MMU*/
    bool DmaTransferStarted; /**<Whether or not a DMA transfer is queued*/
    uint8_t FrameSkip=2; /**<The frames to skip between updates of the screen*/
    uint8_t CurrentFrame=0; /**<The current number of frames skipped since the last draw*/
private:
};


#endif // GPU_H_INCLUDED
