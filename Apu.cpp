#include "Apu.h"

Apu::Apu()
{
    channel1View =nullptr;
    channel2View =nullptr;
    channel3View =nullptr;
    channel1=nullptr;
    channel2=nullptr;
    channel3=nullptr;
    waveformViewerWindow = nullptr;
}

Apu::~Apu()
{
    if(channel1View)
        delete channel1View;
    if(channel2View)
        delete channel2View;
    if(channel3View)
        delete channel3View;
    if(channel1)
        delete channel1;
    if(channel2)
        delete channel2;
    if(channel3)
        delete channel3;
    if(waveformViewerWindow)
        delete waveformViewerWindow;
}

void Apu::Destroy(void)
{
    channel1->stop();
    channel2->stop();
    channel3->stop();
    if(channel1)
        delete channel1;
    if(channel2)
        delete channel2;
    if(channel3)
        delete channel3;
    channel1 = nullptr;
    channel2 = nullptr;
    channel3 = nullptr;
}

void Apu::Stop(void)
{
    channel1->stop();
    channel2->stop();
    channel3->stop();
}

void Apu::Start(void)
{
    channel1->play();
    channel2->play();
    channel3->play();
}

void Apu::Init(Mmu* in)
{
    MMU=in;
    channel1 = new SquareGenerator(44100);
    channel2 = new SquareGenerator(44100);
    channel3 = new WaveGenerator(44100);

    channel1->DutyLL = MMU->GetPointer(0xFF11 );   //duty, length load DDLL LLLL
    channel1->VolumeAPeriod= MMU->GetPointer(0xFF12); //volume, envelope add, period VVVV APPP
    channel1->FreqLSB= MMU->GetPointer(0xFF13);
    channel1->TLFreqMSB= MMU->GetPointer(0xFF14); //Trigger, length enabled, msb TL-- -FFF
    channel1->GlobalAudio=MMU->GetPointer(0xFF26);
    channel1->channel=0;
    channel1->clocks = &channel1Clocks;
    channel1->APUVolume = &currentVolume;

    channel2->DutyLL = MMU->GetPointer(0xFF16);
    channel2->VolumeAPeriod = MMU->GetPointer(0xFF17);
    channel2->FreqLSB = MMU->GetPointer(0xFF18);
    channel2->TLFreqMSB = MMU->GetPointer(0xFF19);
    channel2->GlobalAudio=MMU->GetPointer(0xFF26);
    channel2->channel=1;
    channel2->clocks = &channel2Clocks;
    channel2->APUVolume = &currentVolume;

    channel3->Enabled = MMU->GetPointer(0xFF1A);
    channel3->Length = MMU->GetPointer(0xFF1B);
    channel3->Volume = MMU->GetPointer(0xFF1C);
    channel3->TLFreqMSB = MMU->GetPointer(0xFF1E);
    channel3->FreqLSB = MMU->GetPointer(0xFF1D);
    channel3->GlobalAudio = MMU->GetPointer(0xFF26);
    channel3->channel = 3;
    channel3->wavePattern = MMU->GetPointer(0xFF30);
    channel3->clocks = &channel3Clocks;
    channel3->APUVolume = &currentVolume;

    channel3->play();
    channel2->play();
    channel1->play();
    Debug.Log("Audio channels set up.", DebugLog::Debug, "Apu.cpp");
}

void Apu::Tick(uint16_t AddedCycles)
{
    channel1Clocks+=AddedCycles;
    channel2Clocks+=AddedCycles;
    channel3Clocks+=AddedCycles;
    /*
    clocksSinceUpdate+=AddedCycles;
    if(waveformViewerWindow && updateFrequency < clocksSinceUpdate)
    {
        sf::Event Ev;
        while(waveformViewerWindow->pollEvent(Ev)) {}
        waveformViewerWindow->clear(sf::Color::White);
        if(channel1View)
            waveformViewerWindow->draw(*channel1View);
        //if(channel2View)
        //    waveformViewerWindow->draw(*channel2View);
        //if(channel3View)
        //    waveformViewerWindow->draw(*channel3View);
        waveformViewerWindow->display();
        clocksSinceUpdate=0;
    }*/
}

void Apu::EnableWaveformViewer(uint32_t SizeX, uint32_t SizeY, uint32_t Resolution, uint32_t samplesPerVertex, uint32_t updateFreqClocks)
{
    if(channel1View)
        delete channel1View;
    if(channel2View)
        delete channel2View;
    if(channel3View)
        delete channel3View;
    if(waveformViewerWindow)
        delete waveformViewerWindow;
    channel1View = new WaveformViewer(Resolution,samplesPerVertex,255 );
    channel2View = new WaveformViewer(Resolution,samplesPerVertex,255);
    channel3View = new WaveformViewer(Resolution,samplesPerVertex,255);
    channel1View->SetSize(SizeX,SizeY);
    channel2View->SetSize(SizeX,SizeY);
    channel3View->SetSize(SizeX,SizeY);
    channel1View->setPosition(0,0);
    channel2View->setPosition(SizeX,0);
    channel3View->setPosition(0,SizeY);
    waveformViewerWindow=new sf::RenderWindow(sf::VideoMode(SizeX * 2, SizeY * 2), "Wave Viwer");
    channel1->viewer = channel1View;
    channel2->viewer = channel2View;
    channel3->viewer = channel3View;
    updateFrequency=updateFreqClocks;
    clocksSinceUpdate=0;
}

void Apu::DisableWaveformViewer(void)
{
    channel1->viewer = nullptr;
    channel2->viewer = nullptr;
    channel3->viewer = nullptr;
    if(channel1View)
        delete channel1View;
    if(channel2View)
        delete channel2View;
    if(channel3View)
        delete channel3View;
    if(waveformViewerWindow)
        delete waveformViewerWindow;
}

bool Apu::SaveState(std::ofstream& out)
{
    out.write((const char*)(&channel1Clocks), sizeof(channel1Clocks));
    out.write((const char*)(&channel2Clocks), sizeof(channel2Clocks));
    out.write((const char*)(&channel3Clocks), sizeof(channel3Clocks));
    channel3->SaveState(out);
    return true;
}

bool Apu::LoadState(std::ifstream& in)
{
    //reset the audio

    in.read((char*)(&channel1Clocks), sizeof(channel1Clocks));
    in.read((char*)(&channel2Clocks), sizeof(channel2Clocks));
    in.read((char*)(&channel3Clocks), sizeof(channel3Clocks));
    channel3->LoadState(in);
    return true;
}
