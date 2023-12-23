#include "Necromancer.h"
#include"../Utilities/Math.h"
#include <iostream>

Necromancer::Necromancer() :
    width(64),height(64),speed(0.25f)
{
}

Necromancer::~Necromancer()
{
}

void Necromancer::Load(sf::Vector2i& windowDimensions)
{
    if (texture.loadFromFile("Assets/Player/Textures/necromancerWalking.png"))
    {
        std::cout << "Necromancer image loaded successfully" << std::endl;
        sprite.setTexture(texture);

        int XNIndex = 0;
        int YNIndex = 0;
        sprite.setTextureRect(sf::IntRect(XNIndex * width, YNIndex * height, width, height));
        sprite.scale(sf::Vector2f(scale, scale));//multiplie la taille par 3
        sprite.setPosition(sf::Vector2f(windowDimensions.x / 2, windowDimensions.y *0.42));
    }
    else
    {
        std::cout << "Necromancer image failed to load" << std::endl;
    }
    
}

void Necromancer::Update(FireMage& fireMage,float deltaTime,sf::RenderWindow& window,CameraService& cameraService)
{
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2f horizontal_change = sf::Vector2f(0, 0);
    sf::Vector2f vertical_change = sf::Vector2f(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        horizontal_change += sf::Vector2f(1, 0)*speed*deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        horizontal_change -= sf::Vector2f(1, 0)*speed*deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
         vertical_change -= sf::Vector2f(0, 1) * speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        vertical_change += sf::Vector2f(0, 1) * speed * deltaTime;
    }
    sf::Vector2f movement =vertical_change + horizontal_change;
    cameraService.Update(-movement.y);
    cameraService.MoveSprite(sprite, movement);
    //sprite.setPosition(position+vertical_change+horizontal_change);
    //TODO faire qu'on va un peu moins vite en diagonale (mais toujours un peu plus vite qu'en ligne droite)
    //actuellement, on va 40% plus vite en ligne droite, on pourrait le passer à 20%

    if (Math::SpriteCollision(sprite, fireMage.sprite))
    {
        std::cout << "COLLISION !!!!" << std::endl;
    }
    
}

void Necromancer::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}