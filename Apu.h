#ifndef APU_H_INCLUDED
#define APU_H_INCLUDED
#include "Debugger/WaveformViewer.h"
#include "Apu/SquareGenerator.h"
#include "Apu/WaveGenerator.h"
#include "Mmu.h"

class Apu
{
public:

    Apu();

    ~Apu();

    void Init(Mmu* in);

    void Tick(uint16_t AddedCycles);

    void EnableWaveformViewer(uint32_t SizeX, uint32_t SizeY, uint32_t Resolution, uint32_t samplesPerVertex, uint32_t updateFreqClocks);

    void DisableWaveformViewer(void);

    bool SaveState(std::ofstream& out);
    bool LoadState(std::ifstream& in);

    SquareGenerator* channel1;
    SquareGenerator* channel2;
    WaveGenerator* channel3;
    WaveformViewer* channel1View;
    WaveformViewer* channel2View;
    WaveformViewer* channel3View;


    float currentVolume=1.0;
private:
    sf::RenderWindow* waveformViewerWindow;
    uint16_t channel1Clocks;
    uint16_t channel2Clocks;
    uint16_t channel3Clocks;
    uint32_t updateFrequency;
    uint32_t clocksSinceUpdate;
    Mmu* MMU;
};

#endif // APU_H_INCLUDED
