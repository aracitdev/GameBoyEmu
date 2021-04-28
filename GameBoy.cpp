#include "GameBoy.h"

GameBoy::GameBoy(): CPU(MMU)
{
    GameView=nullptr;
    Cartridge=0;
    SpeedMultiplier = 1.0;
}

GameBoy::~GameBoy()
{
    if(GameView)
        delete GameView;
}

bool GameBoy::Init(uint8_t* RomData, size_t Size,sf::RenderWindow& W, const std::string& filenm)
{
    currentState=0;
    fileName=filenm;
    CartHeader Head;
    Head.Create(RomData);
    CGB = Head.CBG;
    switch(Head.Type)
    {
    case CartridgeType::ROMOnly:
        Cartridge=new RomOnly(RomData, Size);
        break;

    case CartridgeType::MBC1:
        Cartridge=new MBC1(RomData, Size);
        break;
    case CartridgeType::MBC5:
        Cartridge=new MBC5(RomData,Size);
        break;
    case CartridgeType::MBC3:
        Cartridge=new MBC3(RomData,Size);
        break;
    default:
        Debug.Log((std::string("Cart type ") +ToString(Head.Type) + std::string(" not handled.\n")).c_str(), DebugLog::FatalError, "GameBoy.h");
        return false;
        break;
    }
    std::cout <<"Loaded cartridge type "<<ToString(Head.Type)<<"\n";
    MMU.Init(Cartridge, &GPU);
    CPU.Init();
    GPU.Init(W, CPU.IntterruptFlag, &MMU);
    Config.LoadConfig("config.xml");
    StartWithBootDMG(Config.RunBootrom);
    APU.Init(&MMU);
    ProgramDebugger.Enable(&CPU, &MMU, Cartridge, &Time);
    Debug.Log("Init Done.", DebugLog::Info, "GameBoy.h");
    Window=&W;
    GameView=new sf::View(sf::FloatRect(0,0,160,144));
    Window->create(sf::VideoMode(Config.WindowX, Config.WindowY),  Head.Title, Config.fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    UpdateWindowView();
    Time.Init(&MMU);
    GPU.FrameSkip = Config.FrameSkip;
    UpdateSpeed();
    return true;
}

void GameBoy::UpdateWindowView(void)
{
    if(!GameView)
        return;
    float Ratio = (float)Window->getSize().x /(float)(Window->getSize().y);
    float xAspectChange=0;
    float yAspectChange=0;
    if(Ratio > (144.0f / 160.0f))
    {
        float NewWindowX = ((float)Window->getSize().y * (160.0f / 144.0f)); //the y is the greatest, so push the x aspect to fit it
        xAspectChange = ((float)Window->getSize().x - NewWindowX) / (float)(Window->getSize().x); //the ammount of the window that is not actually window
    }
    else
    {
        float NewWindowY = ((float)Window->getSize().x * (144.0f / 160.0f)); //x is the greatest, so push the y to fit it
        yAspectChange = ((float)Window->getSize().y - NewWindowY) / (float)(Window->getSize().y);
    }
    GameView->setViewport(sf::FloatRect(xAspectChange/2, yAspectChange/2, 1-(xAspectChange), 1-(yAspectChange)));
    Window->setView(*GameView);
}

void GameBoy::UpdateSpeed(void)
{
    if(SpeedMultiplier >= 16)
        SpeedMultiplier = 16;
    if(SpeedMultiplier <= 1/16.0)
        SpeedMultiplier = 1/16.0;
    GPU.Window->setFramerateLimit(60 / (GPU.FrameSkip + 1) / SpeedMultiplier);
}


std::pair<uint16_t,uint8_t> DMGStartValues[]=
{
   {0x00,0x01}, //A
   {0x00,0xB0}, //F
   {0x00,0x00}, //B
   {0x00,0x13}, //C
   {0x00,0x00}, //D
   {0x00,0xD8}, //E
   {0x00,0x01}, //H
   {0x00,0x4D}, //L
   {0x00,0xFE}, //SP (0xFF + V)
   {0xFF05,0x00},   // TIMA
   {0xFF06,0x00},   // TMA
   {0xFF07,0x00},   // TAC
   {0xFF10,0x80},   // NR10
   {0xFF11,0xBF},   // NR11
   {0xFF12,0xF3},   // NR12
   {0xFF14,0xBF},   // NR14
   {0xFF16,0x3F},   // NR21
   {0xFF17,0x00},   // NR22
   {0xFF19,0xBF},   // NR24
   {0xFF1A,0x7F},   // NR30
   {0xFF1B,0xFF},   // NR31
   {0xFF1C,0x9F},   // NR32
   {0xFF1E,0xBF},   // NR33
   {0xFF20,0xFF},   // NR41
   {0xFF21,0x00},   // NR42
   {0xFF22,0x00},   // NR43
   {0xFF23,0xBF},   // NR30
   {0xFF24,0x77},   // NR50
   {0xFF25,0xF3},   // NR51
   {0xFF26,0xF1},// $F0-SGB ; NR52
   {0xFF40,0x91},   // LCDC
   {0xFF42,0x00},   // SCY
   {0xFF43,0x00},   // SCX
   {0xFF45,0x00},   // LYC
   {0xFF47,0xFC},   // BGP
   {0xFF48,0xFF},   // OBP0
   {0xFF49,0xFF},   // OBP1
   {0xFF4A,0x00},   // WY
   {0xFF4B,0x00},   // WX
   {0xFFFF,0x00}   // IE
};

std::pair<uint16_t,uint8_t> CGBStartValues[]=
{
   {0x00,0xFF}, //A (Identifies as CGB)
   {0x00,0xB0}, //F
   {0x00,0x00}, //B
   {0x00,0x13}, //C
   {0x00,0x00}, //D
   {0x00,0xD8}, //E
   {0x00,0x01}, //H
   {0x00,0x4D}, //L
   {0x00,0xFE}, //SP (0xFF + V)
   {0xFF05,0x00},   // TIMA
   {0xFF06,0x00},   // TMA
   {0xFF07,0x00},   // TAC
   {0xFF10,0x80},   // NR10
   {0xFF11,0xBF},   // NR11
   {0xFF12,0xF3},   // NR12
   {0xFF14,0xBF},   // NR14
   {0xFF16,0x3F},   // NR21
   {0xFF17,0x00},   // NR22
   {0xFF19,0xBF},   // NR24
   {0xFF1A,0x7F},   // NR30
   {0xFF1B,0xFF},   // NR31
   {0xFF1C,0x9F},   // NR32
   {0xFF1E,0xBF},   // NR33
   {0xFF20,0xFF},   // NR41
   {0xFF21,0x00},   // NR42
   {0xFF22,0x00},   // NR43
   {0xFF23,0xBF},   // NR30
   {0xFF24,0x77},   // NR50
   {0xFF25,0xF3},   // NR51
   {0xFF26,0xF1},// $F0-SGB ; NR52
   {0xFF40,0x91},   // LCDC
   {0xFF42,0x00},   // SCY
   {0xFF43,0x00},   // SCX
   {0xFF45,0x00},   // LYC
   {0xFF47,0xFC},   // BGP
   {0xFF48,0xFF},   // OBP0
   {0xFF49,0xFF},   // OBP1
   {0xFF4A,0x00},   // WY
   {0xFF4B,0x00},   // WX
   {0xFFFF,0x00}   // IE
};

void GameBoy::StartWithBootDMG(bool enabled) //TODO: This is a really bad way of doing this alltogether
{
    CPU.PC = enabled ? 0x0000 : 0x0100;
    std::pair<uint16_t, uint8_t>* DataSet = CGB ? CGBStartValues : DMGStartValues;
    size_t Size = CGB ? sizeof(CGBStartValues) / sizeof(CGBStartValues[0]) : sizeof(DMGStartValues) / sizeof(DMGStartValues[0]);
    *(MMU.BootRomEnabled) = enabled ? 0x00 : 0x01;
    if(!enabled)
        return;
    *CPU.A = DataSet[0].second;
    *CPU.F = DataSet[1].second;
    *CPU.B = DataSet[2].second;
    *CPU.C = DataSet[3].second;
    *CPU.D = DataSet[4].second;
    *CPU.E = DataSet[5].second;
    *CPU.H = DataSet[6].second;
    *CPU.L = DataSet[7].second;
    CPU.SP = DataSet[8].second + 0xFF00;
    for(uint32_t i=9; i < Size; i++)
    {
        MMU.Write(DataSet[i].first, DataSet[i].second);
    }
}


void GameBoy::Run(void)
{
    sf::Clock Sync;
    uint32_t TCycles=0;
    //PNS = GB.MMU.GetPointer(0xFF11);   //sweep period, negate, shift -PPP NSSS
    Debug.Log("Running Main Loop.", DebugLog::Debug, "GameBoy.cpp");
    while(1)
    {
        sf::Event ev;
        while (Window->pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed)
            {
                return;
            }
            else
            if(ev.type == sf::Event::Resized)
            {
                UpdateWindowView();
            }
            else
            if(Config.IsPressed(BindingEntry::EXIT))
            {
                return;
            }
            if(Config.IsPressed(BindingEntry::CHANNEL_1,ev))
            {
                if(APU.channel1->getVolume() == 100)
                    APU.channel1->setVolume(0);
                else
                    APU.channel1->setVolume(100);
            }
            else
            if(Config.IsPressed(BindingEntry::CHANNEL_2,ev))
            {
                if(APU.channel2->getVolume() == 100)
                    APU.channel2->setVolume(0);
                else
                    APU.channel1->setVolume(100);
            }
            else
            if(Config.IsPressed(BindingEntry::CHANNEL_3,ev))
            {
                if(APU.channel3->getVolume() == 100)
                    APU.channel3->setVolume(0);
                else
                    APU.channel3->setVolume(100);
            }
            else
            if(Config.IsPressed(BindingEntry::SPEED_UP,ev))
            {
                SpeedMultiplier /= 2;   //speed up
                UpdateSpeed();
            }
            else
            if(Config.IsPressed(BindingEntry::SPEED_DOWN,ev))
            {
                SpeedMultiplier *= 2;   //slow down
                UpdateSpeed();
            }
            else
            if(Config.IsPressed(BindingEntry::DECREASE_VOLUME, ev))
                APU.currentVolume -= 1/10.0;
            else
            if(Config.IsPressed(BindingEntry::INCREASE_VOLUME, ev))
                APU.currentVolume += 1/10.0;
            else
            if(Config.IsPressed(BindingEntry::DECREASE_FRAMESKIP, ev))
            {
                if(GPU.FrameSkip!=0)
                    GPU.FrameSkip-=1;
                UpdateSpeed();
            }
            else
            if(Config.IsPressed(BindingEntry::INCREASE_FRAMESKIP,ev))
            {
                GPU.FrameSkip+=1;
                UpdateSpeed();
            }
            else
            if(Config.IsPressed(BindingEntry::SAVESTATE_0))
                currentState=0;
            else
            if(Config.IsPressed(BindingEntry::SAVESTATE_1))
                currentState=1;
            else
            if(Config.IsPressed(BindingEntry::SAVESTATE_2))
                currentState=2;
            else
            if(Config.IsPressed(BindingEntry::SAVESTATE_3))
                currentState=3;
            else
            if(Config.IsPressed(BindingEntry::SAVESTATE_4))
                currentState=4;
            else
            if(Config.IsPressed(BindingEntry::SAVESTATE_5))
                currentState=5;
            else
            if(Config.IsPressed(BindingEntry::SAVESTATE_6))
                currentState=6;
            else
            if(Config.IsPressed(BindingEntry::SAVESTATE_7))
                currentState=7;
            else
            if(Config.IsPressed(BindingEntry::SAVESTATE_8))
                currentState=8;
            else
            if(Config.IsPressed(BindingEntry::SAVESTATE_9))
                currentState=9;
            else
            if(Config.IsPressed(BindingEntry::LOAD_SAVESTATE))
            {
                std::string file = fileName + std::to_string(currentState) + std::string(".state");
                LoadState(file);
            }
            else
            if(Config.IsPressed(BindingEntry::SAVE_SAVESTATE))
            {
                std::string file= fileName + std::to_string(currentState) + std::string(".state");
                SaveState(file);
            }
        }
        uint16_t Cycles=CPU.Tick();

        if(!Bit(MMU.Read(0xFF00), 5))
        {
            SetBit(!Config.IsPressed(BindingEntry::START), *MMU.GetPointer(0xFF00), 3);
            SetBit(!Config.IsPressed(BindingEntry::SELECT), *MMU.GetPointer(0xFF00), 2);
            SetBit(!Config.IsPressed(BindingEntry::B), *MMU.GetPointer(0xFF00), 1);
            SetBit(!Config.IsPressed(BindingEntry::A), *MMU.GetPointer(0xFF00), 0);
        }
        if(!Bit(MMU.Read(0xFF00), 4))
        {
            SetBit(!Config.IsPressed(BindingEntry::DPAD_DOWN), *MMU.GetPointer(0xFF00),3);
            SetBit(!Config.IsPressed(BindingEntry::DPAD_UP), *MMU.GetPointer(0xFF00),2);
            SetBit(!Config.IsPressed(BindingEntry::DPAD_LEFT), *MMU.GetPointer(0xFF00),1);
            SetBit(!Config.IsPressed(BindingEntry::DPAD_RIGHT), *MMU.GetPointer(0xFF00),0);
        }
        for(uint32_t counter=0; counter <Cycles; counter+=4)
        {
            Time.Tick(4);   //per cycle perfect ticking test
            GPU.Tick(4);
        }
        APU.Tick(Cycles);    //nothing that should be cycle perfect in the APU
        ProgramDebugger.Tick(Cycles);
        if(ProgramDebugger.StepEnabled)
            GPU.DumpCharMemoryAsImage("Char.bmp");
        TCycles+=Cycles;
        if(TCycles > 4194304)
        {
            //std::cout <<"Took " <<Sync.getElapsedTime().asSeconds() << " second for 1 s time.\n";
            Sync.restart();
            TCycles %= 4194304;
        }
    }
}


bool GameBoy::SaveState(const std::string& filename)
{
    std::ofstream out;
    out.open(filename.c_str(), std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);
    if(!out.is_open())
        return false;
    Cartridge->SaveState(out);
    MMU.SaveState(out);
    CPU.SaveState(out);
    Time.SaveState(out);
    APU.SaveState(out);
    GPU.SaveState(out);
    std::cout <<"State saved\n";
    std::cout <<"PC " <<CPU.PC<<"\n";
    return true;
}

bool GameBoy::LoadState(const std::string& filename)
{
    std::ifstream in;
    in.open(filename.c_str(), std::ifstream::in | std::ifstream::binary);
    if(!in.is_open())
        return false;
    Cartridge->LoadState(in);
    MMU.LoadState(in);
    CPU.LoadState(in);
    Time.LoadState(in);
    APU.LoadState(in);
    GPU.LoadState(in);
    std::cout <<"State loaded\n";
    std::cout <<"PC " <<CPU.PC<<"\n";
    return true;
}
