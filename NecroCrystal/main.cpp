#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

sf::Vector2f convertVector(sf::Vector2i vectorI)
{
    return sf::Vector2f(vectorI.x, vectorI.y);
}

sf::Vector2f normalizeVector(sf::Vector2f direction)
{
    int norm = std::sqrtf((direction.x*direction.x)+(direction.y*direction.y));
    sf::Vector2f new_direction(direction.x/norm,direction.y/norm);

    return new_direction;
}

int main()
{
    //------------------------Initialize---------------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0; 
    int xSize = 1320;
    int ySize = 650;
    sf::RenderWindow window(sf::VideoMode(xSize, ySize), " RPG Game ", sf::Style::Default, settings);

    float spellSpeed = 0.5f;
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

    playerSprite.setPosition(sf::Vector2f(xSize/2,ySize/2));

    sf::Texture darkProjectileTexture;

    std::vector<sf::Sprite> darkProjectiles;

    if (darkProjectileTexture.loadFromFile("Assets/Projectiles/darkProjectile.png"))
    {
        std::cout << "darkProjectile image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "darkProjectile image failed to load" << std::endl;
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
            new_position+= sf::Vector2f(0.25f,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            new_position -= sf::Vector2f(0.25f, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            new_position -= sf::Vector2f(0, 0.25f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            new_position += sf::Vector2f(0, 0.25f);
        }
        playerSprite.setPosition(new_position);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Sprite darkProjectile;
            darkProjectile.setTexture(darkProjectileTexture);
            darkProjectile.setPosition(new_position + sf::Vector2f(64, 20));
            darkProjectiles.push_back(darkProjectile);
        }
        for (size_t i = 0; i < darkProjectiles.size(); i++)
        {
            sf::Vector2f direction = convertVector(sf::Mouse::getPosition())-darkProjectiles[i].getPosition();
            darkProjectiles[i].setPosition(darkProjectiles[i].getPosition() + normalizeVector(direction) * spellSpeed);
        }
        //------------------------UPDATE---------------------------------------

        //-------------------------DRAW---------------------------------------
        window.clear(sf::Color::Black);
        window.draw(playerSprite);
        for (size_t i = 0; i < darkProjectiles.size(); i++)
        {
            window.draw(darkProjectiles[i]);
        }
        window.display();
        //-------------------------DRAW---------------------------------------
    }

    return 0;
}