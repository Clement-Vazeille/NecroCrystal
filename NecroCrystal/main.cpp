#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "Necromancer.h"
#include "DarkProjectiles.h"
#include "DarkProjectile.h"

int main()
{
    //------------------------Initialize and Load---------------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0; 
    int xSize = 1320;
    int ySize = 650;
    sf::RenderWindow window(sf::VideoMode(xSize, ySize), " RPG Game ", sf::Style::Default, settings);

    Necromancer necromancer;
    necromancer.Initialize();
    necromancer.Load(xSize, ySize);

    DarkProjectiles darkProjectiles;
    darkProjectiles.Initialize();
    darkProjectiles.Load();

    //------------------------Initialize and Load---------------------------------------

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

        necromancer.Update();
        darkProjectiles.Update(necromancer);
        
        //------------------------UPDATE---------------------------------------

        //-------------------------DRAW---------------------------------------
        window.clear(sf::Color::Black);

        necromancer.Draw(window);
        darkProjectiles.Draw(window);
        window.display();
        //-------------------------DRAW---------------------------------------
    }

    return 0;
}