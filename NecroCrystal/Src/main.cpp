#include <SFML/Graphics.hpp>

#include "GameGestion/WindowManager.h"
#include "GameGestion/GameLoop.h"

int main()
{
    //------------------------Initialize window and gameloop---------------------------------------
    WindowManager windowManager;
    windowManager.Load();
    sf::RenderWindow* window = windowManager.GetWindow();
     
    GameLoop gameLoop;
    gameLoop.initialize(windowManager.size);
    //------------------------Initialize window and gameloop---------------------------------------

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
        
        gameLoop.update(deltaTime,windowManager.size,mousePosition);
        //------------------------UPDATE---------------------------------------

        //-------------------------DRAW---------------------------------------
        window->clear(sf::Color::Black);

        gameLoop.draw(window);

        window->display();
        //-------------------------DRAW---------------------------------------   
    }
    return 0;
}