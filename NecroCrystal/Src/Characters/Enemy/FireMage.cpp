#include "FireMage.h"
#include <iostream>


FireMage::FireMage() : 
    loopAnimation(80,20,128,128)
{
    scale = 1;
    width = 64;
    height = 64;
    speed = 0.32f;
    sprites = nullptr;
    spriteNumber = 2;
    faction = 2;
    health = 200;
    maxHealth = 200;
}

FireMage::~FireMage()
{
    Character::~Character();
}

void FireMage::Load(sf::Vector2i& windowDimensions,sf::Vector2f position)
{
    if (texture.loadFromFile("Assets/OtherMages/FireMage/fireMageSpriteSheet.png"))
    {
        sprites = new sf::Sprite[spriteNumber];
        std::cout << "FireMage image loaded successfully" << std::endl;
        sprites[0].setTexture(texture);

        loopAnimation.Initialize(sprites[0]);
        hitbox.setSize(sprites[0].getGlobalBounds().getSize());
        sprites[0].scale(sf::Vector2f(scale*(double)windowDimensions.x/1920.0, scale*(double)windowDimensions.y/1080.0));//multiplie la taille par scale (c'est 2)
        sprites[0].setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0,position.y* (double)windowDimensions.y / 1080.0));
    }
    else
    {
        std::cout << "FireMage image failed to load" << std::endl;
    }

    this->LoadHealthBar(windowDimensions,position);

    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(-1);
    hitbox.setFillColor(sf::Color::Transparent);

    hitbox.setScale(sprites[0].getScale());
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());
}

void FireMage::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map)
{
    sf::Vector2f movement = sf::Vector2f(0, 0);
    cameraService.MoveSprite(sprites[0], movement);
    sprites[0].setScale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));
    loopAnimation.Update(sprites[0],deltaTime);

    hitbox.setScale(sprites[0].getScale());
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());
}

sf::Sprite& FireMage::getSprite(void) const
{
    return sprites[0];
}