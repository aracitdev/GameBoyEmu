#ifndef WAVEGENERATOR_H_INCLUDED
#define WAVEGENERATOR_H_INCLUDED
#include <math.h>
#include <cstdint>
#include <SFML/Audio.hpp>
#include "../Debugger/WaveformViewer.h"
#include "../BitFunctions.h"

extern const uint16_t WaveVolumes[];

class WaveGenerator : public sf::SoundStream
{
public:

    float GetFrequency(void);

    float GetPeriod(void);

    WaveGenerator(uint32_t sampleRates);

    virtual bool onGetData(Chunk& data);

    bool HasChanged(void);

    //Last State Variables
    float LastFrequency;    //the last frequency value
    uint8_t LastVolume;     //the last volume index
    uint32_t lastSampleCount;
    bool Changed;           //used to immediately recalculate it (for cases of enabling)


    virtual void onSeek(sf::Time timeOffset);



    uint32_t samplesSinceStart;
    uint32_t sampleRate;
    uint8_t* wavePattern;
    const uint8_t wavePatternLength=(0xFF3F-0xFF30);

    uint8_t* Enabled;   //Enabled E--- ----
    uint8_t* Length;
    uint8_t* Volume;    //Volume -VV- ----
    uint8_t* FreqLSB;
    uint8_t* TLFreqMSB;     //Trigger, Length Enabled, Frequency MSB TL-- -FFF
    bool enabled;
    uint8_t* GlobalAudio; //Channels on/ off M--- 3210
    uint8_t channel;
    uint16_t* clocks;
    float* APUVolume;
    WaveformViewer* viewer;
private:
    std::vector<sf::Int16> sampleReturn;
};

#endif // WAVEGENERATOR_H_INCLUDED
