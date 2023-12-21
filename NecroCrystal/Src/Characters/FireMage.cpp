#include "FireMage.h"
#include <iostream>


FireMage::FireMage() :
    width(64),height(64),scale(2),health(100)
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

    if (font.loadFromFile("Assets/Fonts/arial.ttf")) //alreay loaded in frameRate, TODO make a class that store texture/fonts shared
    {
        std::cout << "Arial.ttf font has been loaded successfully" << std::endl;
        healthText.setFont(font);
    }
    else
    {
        std::cout << "Faile to load Arial.ttf" << std::endl;
    }
    healthText.setPosition(sprite.getPosition() + sf::Vector2f(0,-40));
    healthText.setScale(0.8, 0.8);
    healthText.setString("Health: " + std::to_string(health));
}

void FireMage::Update()
{
    if (health > 0)
    {
        healthText.setPosition(sprite.getPosition() + sf::Vector2f(0, -40));
    }
}

void FireMage::Draw(sf::RenderWindow& window)
{
    if (health > 0)
    {
        window.draw(sprite);
        window.draw(healthText);
    }
	
}

void FireMage::SetHealth(int hp)
{

    health = hp;
    healthText.setString("Health: " + std::to_string(health));
}
