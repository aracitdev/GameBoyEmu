#include "GameBoy.h"

GameBoy::GameBoy(): CPU(MMU)
{
    Cartridge=0;
    SpeedMultiplier = 1.0;
}

bool GameBoy::Init(uint8_t* RomData, size_t Size,sf::RenderWindow& W)
{
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
    MMU.Init(Cartridge, &GPU);
    CPU.Init();
    GPU.Init(W, CPU.IntterruptFlag, &MMU);
    StartWithBootDMG(false);
    APU.Init(&MMU);
    ProgramDebugger.Enable(&CPU, &MMU, Cartridge);
    Debug.Log("Init Done.", DebugLog::Info, "GameBoy.h");
    Window=&W;
    Window->setTitle(Head.Title);
    Time.Init(&MMU);
    In.Init(&MMU);
    UpdateSpeed();
    return true;
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

    while(1)
    {
        sf::Event event;
        while (Window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                return;
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::F1)
                {
                    if(APU.channel1->getVolume() == 100)
                        APU.channel1->setVolume(0);
                    else
                        APU.channel1->setVolume(100);
                }
                if(event.key.code == sf::Keyboard::F2)
                {
                    if(APU.channel2->getVolume() == 100)
                        APU.channel2->setVolume(0);
                    else
                        APU.channel1->setVolume(100);
                }
                if(event.key.code == sf::Keyboard::F3)
                {
                    if(APU.channel3->getVolume() == 100)
                        APU.channel3->setVolume(0);
                    else
                        APU.channel3->setVolume(100);
                }
                if(event.key.code == sf::Keyboard::RBracket)
                {
                    SpeedMultiplier /= 2;
                    UpdateSpeed();
                }
                if(event.key.code == sf::Keyboard::LBracket)
                {
                    SpeedMultiplier *= 2;
                    UpdateSpeed();
                }
                if(event.key.code == sf::Keyboard::Hyphen)
                {
                    APU.currentVolume -= 1/10.0;
                }
                if(event.key.code == sf::Keyboard::Equal)
                {
                    APU.currentVolume += 1/10.0;
                }
                if(event.key.code == sf::Keyboard::F9)
                {
                    if(GPU.FrameSkip!=0)
                        GPU.FrameSkip-=1;
                    UpdateSpeed();
                }
                if(event.key.code == sf::Keyboard::F10)
                {
                    GPU.FrameSkip+=1;
                    UpdateSpeed();
                }
            }
        }
        uint16_t Cycles=CPU.Tick();

        if(!Bit(MMU.Read(0xFF00), 5))
        {
            SetBit(!sf::Keyboard::isKeyPressed(sf::Keyboard::A), *MMU.GetPointer(0xFF00), 3);
            SetBit(!sf::Keyboard::isKeyPressed(sf::Keyboard::S), *MMU.GetPointer(0xFF00), 2);
            SetBit(!sf::Keyboard::isKeyPressed(sf::Keyboard::Z), *MMU.GetPointer(0xFF00), 1);
            SetBit(!sf::Keyboard::isKeyPressed(sf::Keyboard::X), *MMU.GetPointer(0xFF00), 0);
        }
        if(!Bit(MMU.Read(0xFF00), 4))
        {
            SetBit(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down), *MMU.GetPointer(0xFF00),3);
            SetBit(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up), *MMU.GetPointer(0xFF00),2);
            SetBit(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left), *MMU.GetPointer(0xFF00),1);
            SetBit(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right), *MMU.GetPointer(0xFF00),0);
        }
        for(uint32_t counter=0; counter <Cycles; counter+=4)
        {
            Time.Tick(4);   //per cycle perfect ticking test
            GPU.Tick(4);
        }
        APU.Tick(4);    //nothing that should be cycle perfect in the APU
        ProgramDebugger.Tick();
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
