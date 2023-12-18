#include "FireMage.h"
#include <iostream>

void FireMage::Initialize()
{
}

void FireMage::Load(int xSize, int ySize)
{
    if (texture.loadFromFile("Assets/OtherMages/funnyMageColored.png"))
    {
        std::cout << "Necromancer image loaded successfully" << std::endl;
        sprite.setTexture(texture);

        int XNIndex = 0;
        int YNIndex = 0;
        sprite.setTextureRect(sf::IntRect(XNIndex * width, YNIndex * height, width, height));
        sprite.scale(sf::Vector2f(scale, scale));//multiplie la taille par scale (c'est 2)
        sprite.setPosition(sf::Vector2f(4*xSize / 5, ySize / 2));
    }
    else
    {
        std::cout << "Necromancer image failed to load" << std::endl;
    }
}

void FireMage::Update()
{
}

void FireMage::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}