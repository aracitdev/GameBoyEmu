#ifndef PALLETEWINDOW_H_INCLUDED
#define PALLETEWINDOW_H_INCLUDED
#include "../Mmu.h"
#include "../Gpu.h"
#include <SFML/System.hpp>

class PalleteWindow
{
public:


    PalleteWindow();
    ~PalleteWindow();
    void Init(Mmu* M);
    void SetEnabled(bool enabled);
    void Update(void);

    sf::Vector2f WindowSize = sf::Vector2f(200,200);
private:
    sf::Clock Clk;
    sf::RenderWindow* Window;
    Mmu* MMU;
};

#endif // PALLETEWINDOW_H_INCLUDED
