#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "Projectiles/DarkProjectiles.h"
#include "Characters/Necromancer.h"
#include "Characters/FireMage.h"
#include "Utilities/FrameRate.h"
#include "World/Map.h"


int main()
{
    //------------------------Initialize window---------------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0; 
    int xSize = 1320;
    int ySize = 650;
    sf::RenderWindow window(sf::VideoMode(xSize, ySize), " RPG Game ", sf::Style::Default, settings);
    
    window.setFramerateLimit(60); 
    //------------------------Initialize window---------------------------------------

    //------------------------Initialize and load objects---------------------------------------
    Necromancer necromancer;
    necromancer.Load(xSize, ySize);

    DarkProjectiles darkProjectiles;
    darkProjectiles.Load();

    FireMage fireMage;
    fireMage.Load(xSize,ySize);

    FrameRate frameRate;
    frameRate.Load();

    Map map;
    map.Load();
    
    //------------------------Initialize and load objects---------------------------------------
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time deltaTimeTimer = clock.restart();
        double deltaTime = ((double) deltaTimeTimer.asMicroseconds())/1000.0;

        //------------------------UPDATE---------------------------------------
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
        frameRate.Update(deltaTime);
        map.Update(deltaTime);
        fireMage.Update();
        necromancer.Update(fireMage,deltaTime);
        darkProjectiles.Update(necromancer,fireMage,deltaTime,mousePosition);
        
        //------------------------UPDATE---------------------------------------

        //-------------------------DRAW---------------------------------------
        window.clear(sf::Color::Black);

        map.Draw(window);
        necromancer.Draw(window);
        darkProjectiles.Draw(window);
        fireMage.Draw(window);
        frameRate.Draw(window);
        window.display();
        //-------------------------DRAW---------------------------------------
        
    }

    return 0;
}