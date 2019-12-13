#ifndef PALLETE_H_INCLUDED
#define PALLETE_H_INCLUDED
#include "../BitFunctions.h"

enum class Color;

class Palette
{

public:

    void Load(uint8_t PaletteByte);

    Color GetColor(uint8_t BitSet);

private:

    Color Colors[4];

};


#endif // PALLETE_H_INCLUDED
