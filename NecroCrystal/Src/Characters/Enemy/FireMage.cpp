#include "FireMage.h"
#include <iostream>


FireMage::FireMage() : 
    heathBarDistance(0.03)
{
    scale = 2;
    width = 64;
    height = 64;
    speed = 0.32f;
    sprites = nullptr;
    spriteNumber = 1;
    faction = 2;
    health = 100;
}

void FireMage::Load(sf::Vector2i& windowDimensions)
{
    if (texture.loadFromFile("Assets/OtherMages/funnyMageColored.png"))
    {
        sprites = new sf::Sprite[1];
        std::cout << "Necromancer image loaded successfully" << std::endl;
        sprites[0].setTexture(texture);

        int XNIndex = 0;
        int YNIndex = 0;
        sprites[0].setTextureRect(sf::IntRect(XNIndex * width, YNIndex * height, width, height));
        sprites[0].scale(sf::Vector2f(scale, scale));//multiplie la taille par scale (c'est 2)
        sprites[0].setPosition(sf::Vector2f(4 * windowDimensions.x / 5, windowDimensions.y / 2));
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
    healthText.setPosition(sprites[0].getPosition() + sf::Vector2f(0, -windowDimensions.y * heathBarDistance));
    healthText.setScale(0.8, 0.8);
    healthText.setString("Health: " + std::to_string(health));
}

void FireMage::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
    if (health > 0)
    {
        sf::Vector2f movement = sf::Vector2f(0, 0);
        cameraService.MoveSprite(sprites[0], movement);
        healthText.setPosition(sprites[0].getPosition() + sf::Vector2f(0, -windowDimensions.y * heathBarDistance));
    }
}

sf::Sprite& FireMage::getSprite(void) const
{
    return sprites[0];
}