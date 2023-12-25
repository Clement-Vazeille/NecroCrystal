#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "Projectiles/DarkProjectiles.h"
#include "Characters/Necromancer.h"
#include "Characters/Enemy/FireMage.h"
#include "Utilities/FrameRate.h"
#include "World/Map.h"
#include "World/MapLoader.h"
#include "World/MapData.h"
#include "Utilities/CameraService.h"
#include "GameGestion/WindowManager.h"


int main()
{
    //------------------------Initialize window---------------------------------------

    WindowManager windowManager;
    windowManager.Load();
    sf::RenderWindow* window = windowManager.GetWindow();
     
    //------------------------Initialize window---------------------------------------

    //------------------------Initialize and load objects---------------------------------------
    Character* necromancer = new Necromancer;
    necromancer->Load(windowManager.size);

    DarkProjectiles darkProjectiles;
    darkProjectiles.Load();

    Character* fireMage = new FireMage;
    fireMage->Load(windowManager.size);

    FrameRate frameRate;
    frameRate.Load();


    Map map;
    map.Load();

    CameraService cameraService;
    
    
    //------------------------Initialize and load objects---------------------------------------
    sf::Clock clock;
    while (window->isOpen())
    {
        sf::Time deltaTimeTimer = clock.restart();
        double deltaTime = ((double) deltaTimeTimer.asMicroseconds())/1000.0;

        //------------------------UPDATE---------------------------------------
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        windowManager.Update(deltaTime);
        window = windowManager.GetWindow();

        sf::Vector2f mousePosition(sf::Mouse::getPosition(*window));
        frameRate.Update(deltaTime);
        map.Update(deltaTime,cameraService);
        fireMage->Update(cameraService,windowManager.size,deltaTime);
        darkProjectiles.Update((Necromancer*)necromancer,(FireMage*)fireMage,deltaTime,mousePosition,cameraService,windowManager.size);
        necromancer->Update(cameraService,windowManager.size,deltaTime);
        
        //------------------------UPDATE---------------------------------------

        //-------------------------DRAW---------------------------------------
        window->clear(sf::Color::Black);

        map.Draw(window);
        necromancer->Draw(window);
        darkProjectiles.Draw(window);
        fireMage->Draw(window);
        frameRate.Draw(window);
        window->display();
        //-------------------------DRAW---------------------------------------
        
    }

    return 0;
}