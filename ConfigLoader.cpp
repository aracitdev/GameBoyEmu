#include "ConfigLoader.h"

const char* BindingNames[]={"START","SELECT","A","B","DPAD_UP","DPAD_DOWN", "DPAD_LEFT","DPAD_RIGHT",
                            "INCREASE_FRAMESKIP","DECREASE_FRAMESKIP","INCREASE_VOLUME","DECREASE_VOLUME","CHANNEL_1","CHANNEL_2","CHANNEL_3",
                            "SPEED_UP","SPEED_DOWN","EXIT", "SAVESTATE_1","SAVESTATE_2","SAVESTATE_3","SAVESTATE_4","SAVESTATE_5","SAVESTATE_6",
                            "SAVESTATE_7","SAVESTATE_8", "SAVESTATE_9","SAVESTATE_0","LOAD_SAVESTATE","SAVE_SAVESTATE"};

const char* ButtonNames[]={ "A", "B", "C","D", "E", "F", "G", "H", "I" , "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S" ,
                            "T", "U", "V", "W", "X", "Y", "Z", "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8",
                            "Num9" , "Escape", "LControl", "LShift", "LAlt", "LSystem", "RControl", "RShift", "RAlt", "RSystem", "Menu", "LBracket",
                            "RBracket", "Semicolon", "Comma", "Period", "Quote", "Slash", "Backslash", "Tilde","Equal", "Hyphen", "Space", "Enter",
                            "Backspace", "Tab", "PageUp", "PageDown", "End", "Home", "Insert", "Delete","Add", "Subtract", "Multiply", "Divide",
                            "Left", "Right", "Up", "Down","Numpad0", "Numpad1", "Numpad2", "Numpad3","Numpad4", "Numpad5", "Numpad6", "Numpad7",
                            "Numpad8", "Numpad9", "F1", "F2","F3", "F4", "F5", "F6","F7", "F8", "F9", "F10",  "F11", "F12", "F13", "F14",
                            "F15", "Pause"};

const char* JoystickButtonNames[]={"J0","J1","J2","J3","J4","J5","J6","J7","J8","J9","J10",
                                   "J11","J12","J13","J14","J15","J16","J17","J18","J19","J20",
                                   "J21","J22","J23","J24","J25","J26","J27","J28","J29","J30","J31","J32"};

const char* JoystickAxisNames[]={"AxisX", "AxisY", "AxisZ", "AxisR", "AxisU", "AxisV", "AxisPovX", "AxisPovY"};

const BindingEntry DefaultEntry[BindingEntry::BINDING_COUNT]=
{
    BindingEntry(sf::Keyboard::A), //start
    BindingEntry(sf::Keyboard::S), //select
    BindingEntry(sf::Keyboard::X), //A
    BindingEntry(sf::Keyboard::Z), //B
    BindingEntry(sf::Keyboard::Up), //DPad Up
    BindingEntry(sf::Keyboard::Down),   //DPad Down
    BindingEntry(sf::Keyboard::Left),   //DPad Left
    BindingEntry(sf::Keyboard::Right),  //DPad Right
    BindingEntry(sf::Keyboard::F10),    //Increase FrameSkip
    BindingEntry(sf::Keyboard::F9),     //Decrease FrameSkip
    BindingEntry(sf::Keyboard::Equal),  //Increase Volume
    BindingEntry(sf::Keyboard::Hyphen), //Decrease Volume
    BindingEntry(sf::Keyboard::F1),     //Toggle channel 1 audio
    BindingEntry(sf::Keyboard::F2),     //Toggle channel 2 audio
    BindingEntry(sf::Keyboard::F3),     //Toggle channel 3 audio
    BindingEntry(sf::Keyboard::RBracket),   //speed up
    BindingEntry(sf::Keyboard::LBracket),    //slow down
    BindingEntry(sf::Keyboard::Escape),     //exit
    BindingEntry(sf::Keyboard::Num1),       //savestate 1
    BindingEntry(sf::Keyboard::Num2),       //savestate 2
    BindingEntry(sf::Keyboard::Num3),       //savestate 3
    BindingEntry(sf::Keyboard::Num4),       //savestate 4
    BindingEntry(sf::Keyboard::Num5),       //savestate 5
    BindingEntry(sf::Keyboard::Num6),       //savestate 6
    BindingEntry(sf::Keyboard::Num7),       //savestate 7
    BindingEntry(sf::Keyboard::Num8),       //savestate 8
    BindingEntry(sf::Keyboard::Num9),       //savestate 9
    BindingEntry(sf::Keyboard::Num0),       //savestate 0
    BindingEntry(sf::Keyboard::F5),         //load state
    BindingEntry(sf::Keyboard::F6)         //save state
};

BindingEntry::BindingEntry()
{
    EventType = UNBOUND;
}

BindingEntry::BindingEntry(unsigned int joyIndex, unsigned int joyBut)
{
    EventType = JOYSTICK_BUTTON;
    JoystickIndex = joyIndex;
    JoyButton = joyBut;
}

BindingEntry::BindingEntry(unsigned int joyIndex, sf::Joystick::Axis joyAx)
{
    EventType = JOYSTICK_AXIS;
    JoystickIndex = joyIndex;
    JoyAxis = joyAx;
}

BindingEntry::BindingEntry(sf::Keyboard::Key key)
{
    EventType = KEYBOARD_BUTTON;
    Keypress = key;
}

bool BindingEntry::IsPressed(float axisDeadzone)
{
    switch(EventType)
    {
    case JOYSTICK_BUTTON:
        return sf::Joystick::isButtonPressed(JoystickIndex,JoyButton);
        break;
    case JOYSTICK_AXIS:
        return abs(sf::Joystick::getAxisPosition(JoystickIndex,JoyAxis)) > axisDeadzone;
        break;
    case KEYBOARD_BUTTON:
        return sf::Keyboard::isKeyPressed(Keypress);
        break;
    default:
        break;  //to suppress no default
    }
    return false;
}

bool BindingEntry::IsPressed(sf::Event& windowEvent, float axisDeadzone)
{
    switch(EventType)
    {
    case JOYSTICK_BUTTON:
        return windowEvent.type == sf::Event::JoystickButtonPressed && windowEvent.joystickButton.button == JoyButton && windowEvent.joystickButton.joystickId == JoystickIndex;
        break;
    case JOYSTICK_AXIS:
        return windowEvent.type == sf::Event::JoystickMoved && windowEvent.joystickMove.axis == JoyAxis && windowEvent.joystickMove.joystickId == JoystickIndex && abs(windowEvent.joystickMove.position) > axisDeadzone;
        break;
    case KEYBOARD_BUTTON:
        return windowEvent.type == sf::Event::KeyPressed && windowEvent.key.code == Keypress;
        break;
    default:
        break;
    }
    return false;
}

bool ConfigLoader::LoadConfig(const std::string& fileName)
{
    LoadDefaults();
    if(doc.LoadFile(fileName.c_str()) != tinyxml2::XML_SUCCESS)
        return false;
    tinyxml2::XMLElement* BindingsRoot=doc.FirstChildElement("Bindings");
    if(BindingsRoot)
        LoadBindings(BindingsRoot);
    tinyxml2::XMLElement* frameskip=doc.FirstChildElement("FrameSkip");
    if(frameskip)
    {
        if(frameskip->QueryUnsignedText(&FrameSkip) != tinyxml2::XML_SUCCESS)
            FrameSkip = 0;
    }
    tinyxml2::XMLElement* dead=doc.FirstChildElement("DeadZone");
    if(dead)
    {
        if(frameskip->QueryFloatText(&DeadZone) != tinyxml2::XML_SUCCESS)
            DeadZone = 50;
    }
    tinyxml2::XMLElement* boot=doc.FirstChildElement("RunBootrom");
    if(boot)
    {
        unsigned in;
        if(frameskip->QueryUnsignedText(&in) != tinyxml2::XML_SUCCESS)
            RunBootrom=false;
        else
            RunBootrom=in;
    }
    tinyxml2::XMLElement* fullscreenin=doc.FirstChildElement("Fullscreen");
    if(fullscreenin)
    {
        unsigned in;
        if(fullscreenin->QueryUnsignedText(&in) != tinyxml2::XML_SUCCESS)
            fullscreen=false;
        else
            fullscreen=in;
    }
    tinyxml2::XMLElement* winX=doc.FirstChildElement("WindowX");
    tinyxml2::XMLElement* winY=doc.FirstChildElement("WindowY");
    if(winX && winY)
    {
        if(winX->QueryUnsignedText(&WindowX) != tinyxml2::XML_SUCCESS || winY->QueryUnsignedText(&WindowY) != tinyxml2::XML_SUCCESS)
        {
            WindowX=160;
            WindowY=144;
        }
    }
    return true;
}

void ConfigLoader::LoadDefaults(void)
{
    for(uint32_t counter=0; counter < BindingEntry::BINDING_COUNT; counter++)
        Bindings[counter]=DefaultEntry[counter];
    FrameSkip=0;
    DeadZone=50;
    WindowX=160;
    WindowY=144;
    RunBootrom=false;
}

void ConfigLoader::LoadBindings(tinyxml2::XMLElement* bindingRoot)
{
    for(tinyxml2::XMLElement* childElement=bindingRoot->FirstChildElement(); childElement; childElement=childElement->NextSiblingElement())
    {
        for(uint32_t counter=0; counter < BindingEntry::BINDING_COUNT; counter++)
            if(!strcmp(childElement->Name(),BindingNames[counter])) //we found a binding that matches
                LoadBinding(counter, childElement->GetText());
    }
}


void ConfigLoader::LoadBinding(uint32_t index, std::string text)
{
    for(uint32_t counter=0; counter < sf::Keyboard::KeyCount; counter++)
    {
        size_t pos=text.find(std::string(ButtonNames[counter]));
        if(pos != std::string::npos) //we found this button mapping
        {
            Bindings[index]=BindingEntry((sf::Keyboard::Key)(counter)); //so set it
        }   //TODO: Make it so multiple buttons can be mapped to the binding
    }
    for(uint32_t counter=0; counter < sf::Joystick::ButtonCount; counter++)
    {
        size_t pos=text.find(std::string(JoystickButtonNames[counter]));
        if(pos != std::string::npos) //we found this button mapping
        {
            text.erase(pos, strlen(JoystickButtonNames[counter]));  //erase the button name
            Bindings[index]=BindingEntry(std::stoul(text, nullptr),counter);
        }
    }
    for(uint32_t counter=0; counter < sf::Joystick::AxisCount; counter++)
    {
        size_t pos=text.find(std::string((JoystickAxisNames[counter])));
        if(pos != std::string::npos) //we found the axis mapping
        {
            text.erase(pos, strlen(JoystickAxisNames[counter])); //erase the axis name
            Bindings[index]=BindingEntry(std::stoul(text,nullptr), (sf::Joystick::Axis)counter);
        }
    }
}


bool ConfigLoader::IsPressed(BindingEntry::BindingTargets target)
{
    return Bindings[(uint32_t)target].IsPressed(DeadZone);
}

bool ConfigLoader::IsPressed(BindingEntry::BindingTargets target, sf::Event& ev)
{
    return Bindings[(uint32_t)target].IsPressed(ev,DeadZone);
}
