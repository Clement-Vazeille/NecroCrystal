#include <iostream>

#include <SFML/Graphics.hpp>

int main()
{
    //------------------------Initialize---------------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; 

    sf::RenderWindow window(sf::VideoMode(800, 600), " RPG Game ", sf::Style::Default, settings);
    //------------------------Initialize---------------------------------------

    //------------------------Load---------------------------------------------
    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    if (playerTexture.loadFromFile("Assets/Player/Textures/necromancerWalking.png"))
    {
        std::cout << "Necromancer image loaded successfully" << std::endl;
        playerSprite.setTexture(playerTexture);
        
        int XNIndex = 0;
        int YNIndex = 0;
        playerSprite.setTextureRect(sf::IntRect(XNIndex*64, YNIndex*64, 64, 64));
    }
    else
    {
        std::cout << "Necromancer image failed to load" << std::endl;
    }
    
    //------------------------Load---------------------------------------------

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

        sf::Vector2f position = playerSprite.getPosition();
        sf::Vector2f new_position = position;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            new_position+= sf::Vector2f(0.07f,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            new_position -= sf::Vector2f(0.07f, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            new_position -= sf::Vector2f(0, 0.07f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            new_position += sf::Vector2f(0, 0.07f);
        }
        playerSprite.setPosition(new_position);
        //------------------------UPDATE---------------------------------------

        //-------------------------DRAW---------------------------------------
        window.clear(sf::Color::Black);
        window.draw(playerSprite);
        window.display();
        //-------------------------DRAW---------------------------------------
    }

    return 0;
}