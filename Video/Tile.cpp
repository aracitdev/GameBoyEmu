#include "../Gpu.h"

namespace Tile
{
    std::array<Color, 8> GetScanline(uint8_t Scanline, uint8_t* PalleteBytes, Palette& P)
    {
        std::array<Color, 8> ReturnV;
        for(uint8_t counterx=0; counterx<8; counterx++)
            ReturnV[counterx]=GetPixel(counterx, Scanline, PalleteBytes,P);
        return ReturnV;
    }

    Color GetPixel(uint8_t counterx, uint8_t countery,uint8_t* PalleteBytes, Palette& P)
    {
        return P.GetColor(GetTileData(counterx,countery, PalleteBytes));
        //return /*P.GetColor*/(Color)(PalleteBytes[Index] & 0x03);
    }

    uint8_t GetTileData(uint8_t counterx, uint8_t countery, uint8_t* PalleteBytes)
    {
        return (Bit(PalleteBytes[countery * 2 + 1], (7-counterx))) << 1 | Bit(PalleteBytes[countery * 2], (7-counterx));
    }

}
