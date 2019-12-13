#ifndef WAVEFORMVIEWER_H_INCLUDED
#define WAVEFORMVIEWER_H_INCLUDED
#include <sfml/Graphics.hpp>

class WaveformViewer: public sf::Drawable, public sf::Transformable
{
public:
    //resolution is number of vertexes
    WaveformViewer(uint32_t Resolution, uint32_t samplesPerVertex, uint32_t maxWave)
    {
        resolution=Resolution;
        SamplesPerVertex=samplesPerVertex;
        InternalVertexes.resize(Resolution);
        Vertexes=new sf::VertexBuffer(sf::LineStrip,sf::VertexBuffer::Stream);
        Vertexes->create(Resolution);
        SetColor(sf::Color::Black);
        maxWaveScale = maxWave;
        for(uint32_t counter=0; counter < InternalVertexes.size(); counter++)
            InternalVertexes[counter].color = Color;
    }

    ~WaveformViewer()
    {
        delete Vertexes;
    }

    void SetSize(uint32_t x1, uint32_t y1)  //note the size should only be set if all are clear
    {
        x=x1;
        y=y1;
    }

    void AddSamples(std::vector<sf::Int16>& values)
    {
        AddSamples(values, values.size());
    }


    void AddSamples(std::vector<sf::Int16>& values, size_t valuesSize)
    {
        int32_t AverageValue;
        uint32_t VertexesToBeAdded = valuesSize / SamplesPerVertex + valuesSize % SamplesPerVertex ? 1:0;
        uint32_t ExtraSamples = valuesSize % SamplesPerVertex;
        if(VertexesToBeAdded == 0)
            return;
        if(ExtraSamples == 0)
            ExtraSamples  = SamplesPerVertex;
        InternalVertexes.erase(InternalVertexes.begin(), InternalVertexes.begin() + VertexesToBeAdded);
        std::vector<sf::Vertex> ToAdd(VertexesToBeAdded);
        for(uint32_t counters=0; counters < VertexesToBeAdded; counters++)
        {
            uint32_t SamplesThisRun = counters + 1 == VertexesToBeAdded ? ExtraSamples: SamplesPerVertex;
            AverageValue=0;
            for(uint32_t counter=0; counter < SamplesThisRun; counter++)
                AverageValue+=values[counter];
            AverageValue/=SamplesThisRun;
                                        //y/2 is center, y/2 +  y * AverageValue / 2 / maxWaveScale
                                        //AverageValue / maxWaveScale is percent of max, y/2 is max in either direction
            ToAdd[counters].position.y = ( y/2 * (1 + AverageValue / maxWaveScale));   //start from the center, add average / max / 2
            ToAdd[counters].color = Color;  //set the color while we are here
        }
        InternalVertexes.insert(InternalVertexes.end(), ToAdd.begin(), ToAdd.end());    //tape the added vectors on

        float InverseX = 1.0 / InternalVertexes.size();
        for(uint32_t counter=0; counter < InternalVertexes.size(); counter++)   //we then scale all the x
        {   //don't update colors here so we can get some cool effects :P
            InternalVertexes[counter].position.x = InverseX * counter * x;    //scale the x to the size
        }

        Vertexes->update(&InternalVertexes[0], InternalVertexes.size(), 0); //update the vertex array
    }

    void AddVertexes(uint32_t Amplitude, uint32_t VertexN)
    {
        InternalVertexes.erase(InternalVertexes.begin(), InternalVertexes.begin() + VertexN);
        std::vector<sf::Vertex> ToAdd(VertexN);
        for(uint32_t counters=0; counters < ToAdd.size(); counters++)
        {
                                        //y/2 is center, y/2 +  y * AverageValue / 2 / maxWaveScale
                                        //AverageValue / maxWaveScale is percent of max, y/2 is max in either direction
            ToAdd[counters].position.y = ( y/2 * (1 + Amplitude / maxWaveScale));   //start from the center, add average / max / 2
            ToAdd[counters].color = Color;  //set the color while we are here
        }
        InternalVertexes.insert(InternalVertexes.end(), ToAdd.begin(), ToAdd.end());    //tape the added vectors on
        float InverseX = 1.0 / InternalVertexes.size();
        for(uint32_t counter=0; counter < InternalVertexes.size(); counter++)   //we then scale all the x
        {   //don't update colors here so we can get some cool effects :P
            InternalVertexes[counter].position.x = InverseX * counter * x;    //scale the x to the size
        }

        Vertexes->update(&InternalVertexes[0], InternalVertexes.size(), 0); //update the vertex array
    }

    void SetColor(sf::Color color)
    {
        Color=color;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the entity's transform -- combine it with the one that was passed by the caller
        states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

        target.draw(*Vertexes, states);
    }

    uint32_t SamplesPerVertex;
private:


    std::vector<sf::Vertex> InternalVertexes;
    sf::VertexBuffer* Vertexes;
    uint32_t x;
    uint32_t y;
    sf::Color Color;
    uint32_t resolution;
    uint32_t maxWaveScale;  //the expected max value of the waveform
};

#endif // WAVEFORMVIEWER_H_INCLUDED
