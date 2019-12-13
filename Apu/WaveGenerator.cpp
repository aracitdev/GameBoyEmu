#include "WaveGenerator.h"

const uint16_t WaveVolumes[]= {0,255,255 /2,255/4};

float WaveGenerator::GetFrequency(void)
{
    uint16_t x=(uint16_t)(((uint16_t)(*TLFreqMSB & 0x7)) << 8) + *FreqLSB;
    return 65536/(2048-x);
}

float WaveGenerator::GetPeriod(void)
{
    float Frequency = GetFrequency();
    if(Frequency == 0)
        return 0;
    return 1.0 / Frequency;
}

WaveGenerator::WaveGenerator(uint32_t sampleRates)
{
    sampleRate=sampleRates;
    initialize(1, sampleRate);
    enabled=false;
    viewer=nullptr;
    sampleReturn.resize(sampleRates);
}

//BEWARB: BEAN SOUP
//TODO: Make better soup
bool WaveGenerator::onGetData(Chunk& data)
{
    float Period = GetPeriod();
    if(Bit(*TLFreqMSB,7))
    {
        //if the sound was triggered
        SetBit(false,*TLFreqMSB,7); //disable the trigger so we dont restart
        enabled=true;               //enable the sound
        if(*Length == 0)
            *Length = 255;
    }
    while(enabled && Bit(*TLFreqMSB,6) && *clocks * 1/4194304 > 1 / 256.0) //is the length counter enabled and a clock has occured?
    {
        *clocks -= 256. / 4194304;
        (*Length --);
        if(*Length == 0)   //has the length counter expired?
            enabled=false;      //it has
    }
    SetBit(enabled,*GlobalAudio, channel);
    if(!enabled || Period == 0 || !Bit(*GlobalAudio,7))    //we aren't enabled, so just return some garbage
    {
        data.samples =& sampleReturn[0];     //output a completely zero waveform
        for(uint32_t i=0; i<1000; i++)
            sampleReturn[i]=0;
        data.sampleCount = 1000;
        if(viewer)
            viewer->AddSamples(sampleReturn, data.sampleCount);
        Changed = true;
        return true;
    }
    if(!HasChanged())
    {
        data.samples = &sampleReturn[0];
        data.sampleCount = lastSampleCount;
    }
    LastFrequency = GetFrequency();
    LastVolume = BitField(*Volume, 5,6);
    Changed = false;
    uint32_t samplesPerWave= Period * sampleRate; //get one wave
    uint16_t currentVolume = WaveVolumes[LastVolume] * 2;
    const uint32_t wavesPerChunk = sampleRate / 20 / samplesPerWave;

    uint8_t waveMax=0x0F;
    for(uint32_t i=0; i < std::min(samplesPerWave * wavesPerChunk, (uint32_t)sampleReturn.size()); i++)
    {
        uint32_t currentSample=round((float)(i % samplesPerWave) / (float)(samplesPerWave) * 32.0);
        uint8_t sample = currentSample %2 == 0 ? BitField(wavePattern[currentSample/2],4,7) : BitField(wavePattern[currentSample/2],0,3);
        sampleReturn[i]=(float)sample / ((float)waveMax) * currentVolume * (*APUVolume);
        //    std::cout <<sampleReturn[i]<<" " <<(uint16_t)currentVolume <<" "<<(uint16_t)sample<<"\n";
    }
    samplesSinceStart += std::min(samplesPerWave * wavesPerChunk, (uint32_t)sampleReturn.size());
    data.samples =& sampleReturn[0];
    data.sampleCount =  std::min(samplesPerWave * wavesPerChunk, (uint32_t)sampleReturn.size());
    lastSampleCount = data.sampleCount;
    if(viewer)
        viewer->AddSamples(sampleReturn, data.sampleCount);
    return true;
}

bool WaveGenerator::HasChanged(void)
{
    return LastFrequency != GetFrequency() || LastVolume != BitField(*Volume, 5,6) || Changed;  //has any value changed?
}

void WaveGenerator::onSeek(sf::Time timeOffset)
{
}
