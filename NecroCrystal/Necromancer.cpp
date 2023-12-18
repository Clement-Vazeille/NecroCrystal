#include "Necromancer.h"
#include <iostream>

void Necromancer::Initialize()
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
        sprite.setTextureRect(sf::IntRect(XNIndex * 64, YNIndex * 64, 64, 64));
    }
    else
    {
        std::cout << "Necromancer image failed to load" << std::endl;
    }
    sprite.setPosition(sf::Vector2f(xSize / 2, ySize / 2));
}

void Necromancer::Update()
{
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2f new_position = position;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        new_position += sf::Vector2f(0.25f, 0);
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
    sprite.setPosition(new_position);
}

void Necromancer::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}