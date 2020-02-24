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

void GameBoy::StartWithBootDMG(bool enabled) //TODO: This is a really bad way of doing this alltogether
{
    *(MMU.BootRomEnabled) = enabled ? 0x00 : 0x01;
    CPU.AF = enabled ? 0x0000 : 0x01B0;
    CPU.BC = enabled ? 0x0000 : 0x0013;
    CPU.DE = enabled ? 0x0000 : 0x00D8;
    CPU.HL = enabled ? 0x0000 : 0x014D;
    CPU.SP = enabled ? 0x0000 : 0xFFFE;
    CPU.PC = enabled ? 0x0000 : 0x0100;
    *(GPU.LCDC) = enabled ? 0x00 : 0x91;
    *(GPU.LcdStatusRegister) = enabled ? 0x00 : 0x85;
    (GPU.CurrentScanline) = enabled ? 0x00: 90;
    MMU.Write(0xFF05,00); //TIMA
    MMU.Write(0xFF06,00); //TMA
    MMU.Write(0xFF07,00); //TAC
    MMU.Write(0xFF42,00); //SCY
    MMU.Write(0xFF43,00); //SCX
    MMU.Write(0xFF47,enabled ? 0x00 : 0xFC); //BGP
    MMU.Write(0xFF48,enabled ? 0x00 : 0xFF); //OBP0
    MMU.Write(0xFF49,enabled ? 0x00 : 0xFF); //OBP1
    MMU.Write(0xFF4A,0x00); //WY
    MMU.Write(0xFF4B,0x00); //WX
    MMU.Write(0xFFFF,0x00); //IE
    MMU.Write(0xFF0F,0x00); //
    MMU.Write(0xFF10, 0x80);
    MMU.Write(0xFF11, 0xBF);
    MMU.Write(0xFF12,0xF3);
    MMU.Write(0xFF14,0xBF);
    MMU.Write(0xFF14,0xBF);
    MMU.Write(0xFF16,0x3F);
    MMU.Write(0xFF17,0x00);
    MMU.Write(0xFF19,0xBF);
    MMU.Write(0xFF1A,0x7E);
    MMU.Write(0xFF1B,0xFF);
    MMU.Write(0xFF1C,0x9F);
    MMU.Write(0xFF1E,0xBF);
    MMU.Write(0xFF20,0xFF);
    MMU.Write(0xFF21,0x00);
    MMU.Write(0xFF22,0x00);
    MMU.Write(0xFF23,0xBF);
    /*[$FF05] = $00   ; TIMA
    [$FF06] = $00   ; TMA
    [$FF07] = $00   ; TAC
    [$FF10] = $80   ; NR10
    [$FF11] = $BF   ; NR11
    [$FF12] = $F3   ; NR12
    [$FF14] = $BF   ; NR14
    [$FF16] = $3F   ; NR21
    [$FF17] = $00   ; NR22
    [$FF19] = $BF   ; NR24
    [$FF1A] = $7F   ; NR30
    [$FF1B] = $FF   ; NR31
    [$FF1C] = $9F   ; NR32
    [$FF1E] = $BF   ; NR33
    [$FF20] = $FF   ; NR41
    [$FF21] = $00   ; NR42
    [$FF22] = $00   ; NR43
    [$FF23] = $BF   ; NR30
    [$FF24] = $77   ; NR50
    [$FF25] = $F3   ; NR51
    [$FF26] = $F1-GB, $F0-SGB ; NR52
    [$FF40] = $91   ; LCDC
    [$FF42] = $00   ; SCY
    [$FF43] = $00   ; SCX
    [$FF45] = $00   ; LYC
    [$FF47] = $FC   ; BGP
    [$FF48] = $FF   ; OBP0
    [$FF49] = $FF   ; OBP1
    [$FF4A] = $00   ; WY
    [$FF4B] = $00   ; WX
    [$FFFF] = $00   ; IE*/
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
    return true;
}
