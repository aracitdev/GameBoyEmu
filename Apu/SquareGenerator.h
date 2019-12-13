#ifndef SQUAREGENERATOR_H_INCLUDED
#define SQUAREGENERATOR_H_INCLUDED

#include <SFML/Audio.hpp>
#include <vector>
#include "../Debugger/WaveformViewer.h"
#include <cstdint>
#include "../BitFunctions.h"

extern const float dutyPaterns[];

class SquareGenerator : public sf::SoundStream
{
public:

    SquareGenerator(uint32_t sampleRates=8000);

    float GetFrequency(void);

    float GetPeriod(void);

    virtual bool onGetData(Chunk& data);

    virtual void onSeek(sf::Time timeOffset);

    bool enabled=true;
    uint8_t* PNS;   //sweep period, negate, shift -PPP NSSS
    uint8_t* DutyLL;   //duty, length load DDLL LLLL
    uint8_t* VolumeAPeriod; //volume, envelope add, period VVVV APPP
    uint8_t* FreqLSB;
    uint8_t* TLFreqMSB; //Trigger, length enabled, msb TL-- -FFF
    uint8_t* GlobalAudio;   //Channels on/ off M--- 3210
    uint8_t channel;
    uint32_t sampleRate;
    float currentVolume;
    uint16_t* clocks;
    float* APUVolume;
    WaveformViewer* viewer;
private:

    std::vector<sf::Int16> sampleReturn;
};

#endif // SQUAREGENERATOR_H_INCLUDED
