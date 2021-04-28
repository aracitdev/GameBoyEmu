#include "PalleteWindow.h"


PalleteWindow::PalleteWindow()
{
    Window = nullptr;
}

PalleteWindow::~PalleteWindow()
{
    if(Window)
        delete Window;
    Window=nullptr;
}

void PalleteWindow::SetEnabled(bool enabled)
{
    if(enabled && !Window)
        Window = new sf::RenderWindow(sf::VideoMode(WindowSize.x, WindowSize.y), "Pallet Debug");
    if(!enabled && Window)
    {
        delete Window;
        Window = nullptr;
    }
}

void PalleteWindow::Init(Mmu* M)
{
    MMU=M;
}

void PalleteWindow::Update(void)
{
    if(Window && Clk.getElapsedTime().asMilliseconds() > 500)
    {
        Clk.restart();
        Window->clear();
        sf::RectangleShape Rect;
        Rect.setSize(sf::Vector2f(WindowSize.x / 4, WindowSize.y / 3));
        for(uint8_t counterp=0; counterp < 3; counterp++)
        {
            Palette P;
            P.Load(MMU->HardwareRegisters[0x47 + counterp]);
            for(uint8_t counter=0; counter < 4; counter++)
            {
                Rect.setPosition(sf::Vector2f(WindowSize.x / 4 * counter , WindowSize.y / 3 * counterp));
                Rect.setFillColor(ColorSet[(uint8_t)P.GetColor(counter)]);
                Window->draw(Rect);
            }
        }
        Window->display();
    }
}
