#ifndef CONFIGLOADER_H_INCLUDED
#define CONFIGLOADER_H_INCLUDED
#include <tinyxml2.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <string>
#include <fstream>
#include <cstring>

extern const char* ButtonNames[];
extern const char* JoystickButtonNames[];
extern const char* JoystickAxisNames[];

extern const char* BindingNames[];

class BindingEntry
{
public:

    BindingEntry(unsigned int joyIndex, unsigned int joyBut);
    BindingEntry(unsigned int joyIndex, sf::Joystick::Axis joyAx);
    BindingEntry(sf::Keyboard::Key key);
    BindingEntry();

    enum BindingTargets
    {
        START=0,SELECT,A,B,DPAD_UP,DPAD_DOWN, DPAD_LEFT,DPAD_RIGHT,
        INCREASE_FRAMESKIP,DECREASE_FRAMESKIP,INCREASE_VOLUME,DECREASE_VOLUME,CHANNEL_1,CHANNEL_2,CHANNEL_3,
        SPEED_UP,SPEED_DOWN,EXIT,SAVESTATE_1,SAVESTATE_2,SAVESTATE_3,SAVESTATE_4,SAVESTATE_5,SAVESTATE_6,
        SAVESTATE_7,SAVESTATE_8,SAVESTATE_9,SAVESTATE_0,LOAD_SAVESTATE,SAVE_SAVESTATE,BINDING_COUNT
    };


    enum BindingType
    {
        JOYSTICK_BUTTON,
        JOYSTICK_AXIS,
        KEYBOARD_BUTTON,
        UNBOUND
    };

    bool IsPressed(float axisDeadzone);
    bool IsPressed(sf::Event& windowEvent, float axisDeadzone);

    unsigned int JoystickIndex;
    BindingType EventType;
    sf::Keyboard::Key Keypress;
    unsigned int JoyButton;
    sf::Joystick::Axis JoyAxis;
};


extern const BindingEntry DefaultEntry[];

class ConfigLoader
{
public:

    bool LoadConfig(const std::string& fileName);
    void LoadDefaults(void);

    bool IsPressed(BindingEntry::BindingTargets target);
    bool IsPressed(BindingEntry::BindingTargets target, sf::Event& ev);

    BindingEntry Bindings[BindingEntry::BINDING_COUNT];
    unsigned int FrameSkip;
    unsigned int WindowX;
    unsigned int WindowY;
    float DeadZone;
    bool RunBootrom;
    bool fullscreen;
private:
    void LoadBindings(tinyxml2::XMLElement* bindingRoot);
    void LoadBinding(uint32_t index, std::string text);
    tinyxml2::XMLDocument doc;
};

#endif // CONFIGLOADER_H_INCLUDED
