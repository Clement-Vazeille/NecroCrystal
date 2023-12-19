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

void Necromancer::Load(int xSize, int ySize)
{
    if (texture.loadFromFile("Assets/Player/Textures/necromancerWalking.png"))
    {
        std::cout << "Necromancer image loaded successfully" << std::endl;
        sprite.setTexture(texture);

        int XNIndex = 0;
        int YNIndex = 0;
        sprite.setTextureRect(sf::IntRect(XNIndex * width, YNIndex * height, width, height));
        sprite.scale(sf::Vector2f(scale, scale));//multiplie la taille par 3
        sprite.setPosition(sf::Vector2f(xSize / 2, ySize / 2));
    }
    else
    {
        std::cout << "Necromancer image failed to load" << std::endl;
    }
    
}

void Necromancer::Update(FireMage& fireMage,float deltaTime)
{
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2f new_position = position;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        new_position += sf::Vector2f(1, 0)*speed*deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        new_position -= sf::Vector2f(1, 0)*speed*deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        new_position -= sf::Vector2f(0, 1) * speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        new_position += sf::Vector2f(0, 1) * speed * deltaTime;
    }
    sprite.setPosition(new_position);

    if (Math::SpriteCollision(sprite, fireMage.sprite))
    {
        std::cout << "COLLISION !!!!" << std::endl;
    }
}

void Necromancer::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}