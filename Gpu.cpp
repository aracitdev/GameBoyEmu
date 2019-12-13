#include "Gpu.h"

const uint16_t ClocksPerHBLANK = 204;
const uint16_t ClocksPerScanlineOAM = 80;
const uint16_t ClocksPerScanlineVRAM = 172;
const uint16_t ClocksPerScanline = (ClocksPerScanlineOAM + ClocksPerScanlineVRAM + ClocksPerHBLANK);
const uint16_t ClocksPerVBLANK = 4560;
const uint16_t ScalinesPerFrame = 144;
const uint32_t ClocksPerFrame = (ClocksPerScanline * ScalinesPerFrame) + ClocksPerVBLANK;

const uint8_t GameboyScreenX=160;
const uint8_t GameboyScreenY=144;
const uint16_t BgScreenX=32*8;
const uint16_t BgScreenY=32*8;

const char* ColorStrings[4]={"White","LightGray","DarkGray","Black"};
const sf::Color ColorSet[5]={sf::Color(0x01,0x01,0x01,0x00), sf::Color(0x80, 0x80, 0x80), sf::Color(0x60,0x60,0x60), sf::Color(0,0,0), sf::Color(1,1,1,0)};


Gpu::Gpu()
{
    CurrentMode=VideoMode::ACCESS_OAM;
    Image.create(GameboyScreenX, GameboyScreenY);
}

void Gpu::Write(uint16_t Address, uint8_t Value)
{
    if(Address >= MemoryMap::BGMap1Start && Address <= MemoryMap::BGMap2End)
        BGMap[Address - MemoryMap::BGMap1Start]=Value;
    else
    if(Address >= MemoryMap::OemStart && Address <= MemoryMap::OemEnd)
        OEM[Address - MemoryMap::OemStart]=Value;
    else
    if(Address >= MemoryMap::CRamStart && Address <= MemoryMap::CRamEnd)
        CharMemory[Address - MemoryMap::CRamStart]=Value;
    else
        std::cout <<"Failed.\n";
}

uint8_t Gpu::Read(uint16_t Address)
{
    if(Address >= MemoryMap::BGMap1Start && Address <= MemoryMap::BGMap2End)
        return BGMap[Address - MemoryMap::BGMap1Start];
    else
    if(Address >= MemoryMap::OemStart && Address <= MemoryMap::OemEnd)
        return OEM[Address - MemoryMap::OemStart];
    else
    if(Address >= MemoryMap::CRamStart && Address <= MemoryMap::CRamEnd)
        return CharMemory[Address - MemoryMap::CRamStart];
    std::cout <<"Failed to read.\n";
    return 0;
}

uint8_t* Gpu::GetPointer(uint16_t Address)
{
    if(Address >= MemoryMap::BGMap1Start && Address <= MemoryMap::BGMap2End)
        return &(BGMap[Address - MemoryMap::BGMap1Start]);
    else
    if(Address >= MemoryMap::OemStart && Address <= MemoryMap::OemEnd)
        return &(OEM[Address - MemoryMap::OemStart]);
    else
    if(Address >= MemoryMap::CRamStart && Address <= MemoryMap::CRamEnd)
        return &(CharMemory[Address - MemoryMap::CRamStart]);
    return 0;
}


void Gpu::DrawScanline(void)
{
    Palette P;
    P.Load(MMU->HardwareRegisters[0x47]);
    uint16_t AddressOffset= Bit(*LCDC, 3)? (0x9C00 - 0x9800):0;
    uint8_t ScrolledPosX=0;
    uint8_t ScrolledPosY=0;
    uint8_t  BGMapX=0;
    uint8_t BGMapY=0;
    uint8_t TileX=0;
    uint8_t TileY=0;
    uint8_t TilePixelX=0;
    uint8_t TilePixelY=0;
    uint8_t TileNumber=0;
    uint8_t SpriteSize= Bit(MMU->Read(0xFF40), 2);
    uint8_t SpriteTileX=8;
    uint8_t SpriteTileY = SpriteSize ? 16 :8;
    uint8_t TileColor=0;
    Palette SpritePallete;
    SpritePallete.Load(Bit(OEM[3], 4) ? MMU->HardwareRegisters[0x48] : MMU->HardwareRegisters[0x49]);
    for(uint32_t counterx=0; counterx<GameboyScreenX; counterx++)
    {
        ScrolledPosX=counterx + (*ScrollX);
        ScrolledPosY=CurrentScanline + (*ScrollY);
        BGMapX=ScrolledPosX % BgScreenX;
        BGMapY=ScrolledPosY % BgScreenY;
        TileX=BGMapX/8;
        TileY=BGMapY/8;
        TilePixelX=BGMapX%8;
        TilePixelY=BGMapY%8;
        TileNumber=BGMap[TileX + 32 * TileY + AddressOffset];
        TileColor = (uint8_t)Tile::GetPixel(TilePixelX, TilePixelY, GetCharMemory(TileNumber),P);
        Image.setPixel(counterx, CurrentScanline, ColorSet[TileColor]);
        if(Bit(*LCDC, 5))   //is the window enabled?
        {
            uint16_t WindowAddressOffset= Bit(*LCDC, 6)? (0x9C00 - 0x9800):0;
            uint8_t scrollX= MMU->HardwareRegisters[0x4B] - 7;
            uint8_t scrollY= MMU->HardwareRegisters[0x4A];
            if(counterx >= scrollX && CurrentScanline >= scrollY)   //is it visible?
            {
                uint8_t WTileX= (counterx - scrollX) / 8;
                uint8_t WTileY= (CurrentScanline - scrollY) / 8;
                uint8_t WTilePixelX = (counterx - scrollX) % 8;
                uint8_t WTilePixelY = (CurrentScanline - scrollY) % 8;
                if(WTileX < 32 && WTileY < 32)
                {
                    uint8_t WTileNumber = BGMap[WTileX + 32 * WTileY + WindowAddressOffset];
                    uint8_t WTileColor = (uint8_t)Tile::GetPixel(WTilePixelX, WTilePixelY, GetCharMemory(WTileNumber),P);
                    Image.setPixel(counterx, CurrentScanline, ColorSet[WTileColor]);
                }
            }
        }

        for(uint32_t countersprite=0; countersprite <40; countersprite++)
        {
            uint8_t* OemPos=OEM + 0x04 * countersprite;
            uint8_t SpritePriority=Bit(OemPos[3],7);
            uint8_t ScreenPosX = OemPos[1] - 8;
            uint8_t ScreenPosY = OemPos[0] - 16;
            if((!TileColor || !SpritePriority) &&
               ScreenPosY <= CurrentScanline && ScreenPosY  + SpriteTileY  >= CurrentScanline&&
               ScreenPosX <= counterx && ScreenPosX + SpriteTileX >= counterx)
            {
                uint8_t PixelX = Bit(OemPos[3], 5) ? SpriteTileX - (counterx - ScreenPosX) : counterx - ScreenPosX;
                uint8_t PixelY = Bit(OemPos[3], 6) ? SpriteTileY - (CurrentScanline - ScreenPosY) : CurrentScanline - ScreenPosY;
                uint8_t TileNumber= PixelY >=8 ? OemPos[2] | 0x01: OemPos[2] & 0xFE;
                PixelY %=8;
                uint8_t* TileData=GetCharMemory(TileNumber, true);
                uint8_t TileColor = (uint8_t)Tile::GetPixel(PixelX, PixelY, TileData, SpritePallete);
                if(TileColor)
                    Image.setPixel(counterx, CurrentScanline,ColorSet[(uint16_t)TileColor]);
            }

        }
        //Image.setPixel(counterx * 8 + ColorSetC, CurrentScanline, sf::Color(0x00,0x00,0x00));
    }
    CurrentScanline++;
}

void Gpu::Tick(uint16_t AddedCycles)
{
    DoDMATransfer();
    if(!Bit(*LCDC,7)) //LCD not enabled
    {
        CurrentScanline=0;
    }
    CurrentCycles+=AddedCycles;
    switch(CurrentMode)
    {
    case VideoMode::ACCESS_OAM:
        if(CurrentCycles > ClocksPerScanlineOAM)
        {
            CurrentCycles %= ClocksPerScanlineOAM;
            SetBit(true, *LcdStatusRegister, 1);
            SetBit(false,*LcdStatusRegister, 0);
            CurrentMode=VideoMode::ACCESS_VRAM;
        }
        break;
    case VideoMode::ACCESS_VRAM:
        if(CurrentCycles > ClocksPerScanlineVRAM)
        {
            CurrentCycles %= ClocksPerScanlineVRAM;
            CurrentMode=VideoMode::HBLANK;
            if(Bit(*LcdStatusRegister,3))   //HBLANK INTERRUPT
                SetBit(true,*InterruptFlag,1);

            if(CurrentScanline == MMU->Read(0xFF5))
            {
                if(Bit(*LcdStatusRegister,6) )
                    SetBit(true, *InterruptFlag, 1);
                SetBit(true, *LcdStatusRegister, 2);
            }
            else
                SetBit(false, *LcdStatusRegister, 2);

            SetBit(false, *LcdStatusRegister, 1);
            SetBit(false,*LcdStatusRegister, 0);
        }
        break;
    case VideoMode::HBLANK:
        if(CurrentCycles < ClocksPerHBLANK)
        {
            CurrentCycles %= ClocksPerHBLANK;
            if(FrameSkip == CurrentFrame)
                DrawScanline();
            else
                CurrentScanline++;
            if(CurrentScanline == 144)
            {
                CurrentMode=VideoMode::VBLANK;
                SetBit(false, *LcdStatusRegister, 1);
                SetBit(true,*LcdStatusRegister, 0);
                SetBit(true,*InterruptFlag,0);
            }
            else
            {
                SetBit(true, *LcdStatusRegister, 1);
                SetBit(false, *LcdStatusRegister, 0);
                CurrentMode = VideoMode::ACCESS_OAM;
            }
        }
        break;
    case VideoMode::VBLANK:
        if(CurrentCycles > ClocksPerScanline)
        {
            CurrentCycles %=ClocksPerScanline;
            CurrentScanline++;
            if (CurrentScanline == 154)
            {
                if(CurrentFrame == FrameSkip)
                {
                    CurrentFrame=0;
                    Render();
                    Clear();
                }
                else
                {
                    CurrentFrame++;
                }
                CurrentScanline=0;
                CurrentMode = VideoMode::ACCESS_OAM;
                SetBit(true,*LcdStatusRegister, 1);
                SetBit(false, *LcdStatusRegister,0);
            }
        }
        break;
    }
    MMU->Write(0xFF44, CurrentScanline);
}

void Gpu::Render(bool shouldUpdate)
{
    //DumpCharMemoryAsImage("Char.bmp");
    if(shouldUpdate)
        InternalTexture.loadFromImage(Image);
    Sprite.setTexture(InternalTexture);
    Sprite.setPosition(sf::Vector2f(0,0));
    Window->draw(Sprite);
    Window->display();
}

void Gpu::DoDMATransfer(void)
{
    if(DmaTransferStarted)
    {
        for(uint32_t counter=0; counter < (0x9F); counter++)
        {
            MMU->Write(0xFE00 + counter, MMU->Read(0x100 * MMU->HardwareRegisters[0x46] + counter));
        }
        MMU->HardwareRegisters[0x46]=0;
        DmaTransferStarted=false;
    }
}

void Gpu::Clear(void)
{
    for(uint32_t counterx=0; counterx < GameboyScreenX; counterx++)
        for(uint32_t countery=0; countery < GameboyScreenY; countery++)
        Image.setPixel(counterx, countery, sf::Color::White);
    Window->clear(sf::Color::White);
}

void Gpu::Init(sf::RenderWindow& W, uint8_t* I, Mmu* M)
{
    DmaTransferStarted=false;
    Window=&W;
    InterruptFlag=I;
    MMU=M;

    LcdStatusRegister=MMU->GetPointer(0xFF41);
    LCDC=MMU->GetPointer(0xFF40);
    *LCDC=0x91;
    ScrollY=MMU->GetPointer(0xFF42);
    ScrollX=MMU->GetPointer(0xFF43);
    MMU->Write(0xFF45, 0);
    *ScrollX=0;
    *ScrollY=0;
    CurrentScanline=0;

    for(uint32_t counter=0; counter < MemoryMap::BGMap1Size + MemoryMap::BGMap2Size; counter++)
        BGMap[counter]=0;

}

std::array<Color, 8> Gpu::GetTileScanline(uint8_t Scanline, uint8_t TileNumber)
{
    Palette P;
    return Tile::GetScanline(Scanline, GetCharMemory(TileNumber), P);
}

void Gpu::DumpCharMemory(std::ostream& out)
{
    out.write((char*)CharMemory, MemoryMap::CRamSize);
}

uint8_t* Gpu::GetCharMemory(uint8_t T)
{
    if(Bit(*LCDC, 4))
    {
        return MMU->GetPointer(0x8000) + T * 16;
    }
    else
    {
        return MMU->GetPointer( (T>=128)? 0x8800 : 0x9000 ) + (T % 128) * 16 ;
    }
}

uint8_t* Gpu::GetCharMemory(uint8_t T, bool B)
{
    if(B)
    {
        return MMU->GetPointer(0x8000) + T * 16;
    }
    else
    {
        return MMU->GetPointer((T>=128)?0x8800 : 0x9000) + (T % 128) * 16;
    }
}

void Gpu::DumpCharMemoryAsImage(std::string filename)
{
    sf::Image Out;
    Out.create(8*16,8*16);
    for(uint16_t counter=0; counter<256; counter++)
    {
        for(uint16_t scanline=0; scanline < 8; scanline++)
        {
            std::array<Color, 8> Array=GetTileScanline(scanline,counter);
            for(uint16_t counterx=0; counterx<8; counterx++)
                Out.setPixel((counter % 16) * 8+counterx, scanline + (counter / 16)* 8, ColorSet[(uint16_t)Array[counterx]]);
        }
    }
    Out.saveToFile(filename);
}
