#include "Pallete.h"
#include "../Gpu.h"

void Palette::Load(uint8_t PaletteByte)
{
    for(uint8_t counter=0; counter<4; counter++)
        Colors[counter]=(Color)BitField(PaletteByte, counter * 2, counter * 2 + 1);
}

Color Palette::GetColor(uint8_t BitSet)
{
    return Colors[BitSet];
}
