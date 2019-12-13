#include "SquareGenerator.h"

const float dutyPaterns[]= {1,2,4,6};

SquareGenerator::SquareGenerator(uint32_t sampleRates)
{
    viewer=nullptr;
    sampleRate=sampleRates;
    initialize(1, sampleRate);
    enabled=false;
    sampleReturn.resize(sampleRate);
}

float SquareGenerator::GetFrequency(void)
{
    uint16_t x=(uint16_t)(((uint16_t)(*TLFreqMSB & 0x7)) << 8) + *FreqLSB;
    return 131072.0/(2048.0-x);
}

float SquareGenerator::GetPeriod(void)
{
    float Frequency = GetFrequency();
    if(Frequency == 0)
        return 0;
    return 1.0 / Frequency;
}

//BEWARB: The flying spaghetti monster lurks ahead.
//TODO: Slay the spaghetti monster.
bool SquareGenerator::onGetData(Chunk& data)
{
    float Period = GetPeriod();
    if(Bit(*TLFreqMSB,7))
    {
        //if the sound was triggered
        SetBit(false,*TLFreqMSB,7); //disable the trigger so we dont restart
        enabled=true;               //enable the sound
        if((*DutyLL & 63) == 0)
            DutyLL += 63;
    }
    while(enabled && Bit(*TLFreqMSB,6) && *clocks * 1/4194304 > 1 / 256.0) //is the length counter enabled and a clock has occured?
    {
        *clocks -= 256. / 4194304;
        (*DutyLL --);
        if((*DutyLL & 63) == 0)   //has the length counter expired?
            enabled=false;      //it has
    }
    SetBit(enabled,*GlobalAudio, channel);
    if(!enabled || Period == 0 || !Bit(*GlobalAudio,7))    //we aren't enabled, so just return some garbage
    {
        data.samples =&sampleReturn[0];     //output a completely zero waveform
        for(uint32_t i=0; i<1000; i++)
            sampleReturn[i]=0;
        data.sampleCount = 1000;
        if(viewer)
            viewer->AddVertexes(0, 1);
        return true;
    }
    uint32_t samplesPerWave= Period * sampleRate; //get one wave
    float duty = dutyPaterns[BitField(*DutyLL, 6,7)] / 8.0;
    currentVolume = ((float)BitField(*VolumeAPeriod,4,7)) / (float)(0xF) * 255 * 2;
    const uint32_t wavesPerChunk = sampleRate / 20 / samplesPerWave;
    for(uint32_t i=0; i < std::min(samplesPerWave * wavesPerChunk, (uint32_t)sampleReturn.size()); i++)
    {
        if(samplesPerWave * duty < i % samplesPerWave)
            sampleReturn[i]=0;
        else
            sampleReturn[i]= currentVolume * (*APUVolume);
    }
    data.samples = &sampleReturn[0];     //output a completely zero waveform
    data.sampleCount =  std::min(samplesPerWave * wavesPerChunk, (uint32_t)sampleReturn.size());
    if(viewer)
        viewer->AddSamples(sampleReturn, data.sampleCount);
    return true;
}

void SquareGenerator::onSeek(sf::Time timeOffset)
{
}
