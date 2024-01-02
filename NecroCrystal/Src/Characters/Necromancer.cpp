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
    Character::~Character();
}

void Necromancer::Load(sf::Vector2i& windowDimensions,sf::Vector2f position)
{
    if (texture.loadFromFile("Assets/Player/Textures/necromancerWalking.png"))
    {
        std::cout << "Necromancer image loaded successfully" << std::endl;
        sprites = new sf::Sprite[1];
        sprites[0].setTexture(texture);

        int XNIndex = 0;
        int YNIndex = 0;
        sprites[0].setTextureRect(sf::IntRect(XNIndex * width, YNIndex * height, width, height));
        hitbox.setSize(sprites[0].getGlobalBounds().getSize());

        sprites[0].scale(sf::Vector2f(scale* ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
        sprites[0].setPosition(sf::Vector2f(position.x* (double)windowDimensions.x / 1920.0, position.y* (double)windowDimensions.y / 1080.0));

        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(-1);
        hitbox.setFillColor(sf::Color::Transparent);

        hitbox.setScale(sprites[0].getScale());
        hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());
    }
    else
    {
        std::cout << "Necromancer image failed to load" << std::endl;
    }
    
}

void Necromancer::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime,Map& map)
{
    sprites[0].setScale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
    hitbox.setScale(sprites[0].getScale());

    sf::Vector2f position = sprites[0].getPosition();
    sf::Vector2f change = sf::Vector2f(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        change += sf::Vector2f(1, 0)*speed*deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        change -= sf::Vector2f(1, 0)*speed*deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
         change -= sf::Vector2f(0, 1) * speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        change += sf::Vector2f(0, 1) * speed * deltaTime;
    }

    //-----------------------------------------WALL COLLISION TEST------------------------------------------------------
    sf::Vector2f movement_x = sf::Vector2f(change.x * (float)windowDimensions.x / 1920.0f,0.0f);
    sf::Vector2f movement_y = sf::Vector2f(0.0f, change.y * (float)windowDimensions.y / 1080.0f);
    
    hitbox.move(movement_x);
    if (map.ColideWithWall(&hitbox))
    {
        hitbox.move(-movement_x);                 //because if we do it after it won't move
        movement_x.x = 0.0f;
    }
    hitbox.move(-movement_x);

    hitbox.move(movement_y);
    if (map.ColideWithWall(&hitbox))
    {
        hitbox.move(-movement_y);
        movement_y.y = 0.0f;
    }
    hitbox.move(-movement_y);
    //-----------------------------------------WALL COLLISION TEST------------------------------------------------------

    sf::Vector2f movement = movement_x + movement_y;
    if (movement.x != 0.0f && movement.y != 0.0f)
        movement = movement * 0.85f;

    cameraService.Update(-movement.y,sf::Vector2f(windowDimensions));
    cameraService.MoveSprite(sprites[0], movement);

    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());
}


sf::Sprite& Necromancer::getSprite(void) const
{
    return sprites[0];
}