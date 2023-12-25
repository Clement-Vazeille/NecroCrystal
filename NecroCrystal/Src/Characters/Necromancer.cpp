#include "Necromancer.h"
#include"../Utilities/Math.h"
#include <iostream>

Necromancer::Necromancer()
{
    scale = 2;
    width = 64;
    height = 64;
    speed = 0.32f;
    sprites = nullptr;
    spriteNumber = 1;
    faction = 1;
}

Necromancer::~Necromancer()
{
}

void Necromancer::Load(sf::Vector2i& windowDimensions)
{
    if (texture.loadFromFile("Assets/Player/Textures/necromancerWalking.png"))
    {
        std::cout << "Necromancer image loaded successfully" << std::endl;
        sprites = new sf::Sprite[1];
        //sprites[0] = sprite;
        sprites[0].setTexture(texture);

        int XNIndex = 0;
        int YNIndex = 0;
        sprites[0].setTextureRect(sf::IntRect(XNIndex * width, YNIndex * height, width, height));
        sprites[0].scale(sf::Vector2f(scale, scale));//multiplie la taille par 3
        sprites[0].setPosition(sf::Vector2f(windowDimensions.x / 2, windowDimensions.y * 0.42));
    }
    else
    {
        std::cout << "Necromancer image failed to load" << std::endl;
    }
    
}

void Necromancer::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
    sf::Vector2f position = sprites[0].getPosition();
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
    cameraService.MoveSprite(sprites[0], movement);
    //sprite.setPosition(position+vertical_change+horizontal_change);
    //TODO faire qu'on va un peu moins vite en diagonale (mais toujours un peu plus vite qu'en ligne droite)
    //actuellement, on va 40% plus vite en ligne droite, on pourrait le passer à 20%
    
}


