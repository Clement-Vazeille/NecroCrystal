#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "Projectiles/DarkProjectiles.h"
#include "Characters/Necromancer.h"
#include "Characters/FireMage.h"

int main()
{
    //------------------------Initialize window---------------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0; 
    int xSize = 1320;
    int ySize = 650;
    sf::RenderWindow window(sf::VideoMode(xSize, ySize), " RPG Game ", sf::Style::Default, settings);
    //------------------------Initialize window---------------------------------------

    //------------------------Initialize and load objects---------------------------------------
    Necromancer necromancer;
    necromancer.Initialize();
    necromancer.Load(xSize, ySize);

    DarkProjectiles darkProjectiles;
    darkProjectiles.Initialize();
    darkProjectiles.Load();

    FireMage fireMage;
    fireMage.Initialize();
    fireMage.Load(xSize,ySize);
    //------------------------Initialize and load objects---------------------------------------

    while (window.isOpen())
    {
        //------------------------UPDATE---------------------------------------
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        fireMage.Update();
        necromancer.Update(fireMage);
        darkProjectiles.Update(necromancer);
        
        //------------------------UPDATE---------------------------------------

        //-------------------------DRAW---------------------------------------
        window.clear(sf::Color::Black);

        necromancer.Draw(window);
        darkProjectiles.Draw(window);
        fireMage.Draw(window);
        window.display();
        //-------------------------DRAW---------------------------------------
    }

    return 0;
}