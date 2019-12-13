#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

enum class Color;
class Pallete;

namespace Tile
{

    std::array<Color, 8> GetScanline(uint8_t Scanline, uint8_t* PalleteBytes, Palette& P);

    Color GetPixel(uint8_t counterx, uint8_t countery,uint8_t* PalleteBytes, Palette& P);


};

#endif // TILE_H_INCLUDED
