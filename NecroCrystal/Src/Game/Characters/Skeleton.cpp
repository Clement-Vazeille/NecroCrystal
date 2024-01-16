#include "Skeleton.h"
#include <iostream>

Skeleton::Skeleton() :
    faceRight(true),
    activated(false), activatedTimer(0),activationTime(1000)
{
    scale = 2;
    width = 64;
    height = 64;
    speed = 1.35f;
    sprites = nullptr;
    spriteNumber = 1;
    faction = -1;  //TODO -1 = inciblable
    health = 1;
    maxHealth = 1;
}

Skeleton::~Skeleton()
{
    Character::~Character();
}

void Skeleton::Load(sf::Vector2i& windowDimensions, sf::Vector2f position)
{
    if (texture.loadFromFile("Assets/Skeleton/Skeleton.png")) //c'est pas opti de load à chaque fois
    {
        sprites = new sf::Sprite[spriteNumber];
        sprites[0].setTexture(texture);

        int XNIndex = 0;
        int YNIndex = 0;
        sprites[0].setTextureRect(sf::IntRect(XNIndex * width, YNIndex * height, width, height));

        sprites[0].scale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
        sprites[0].setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0, position.y * (double)windowDimensions.y / 1080.0));

        hitbox.setSize(sf::Vector2f(0,0));
        hitbox.setPosition(sf::Vector2f(0, 0));
    }
    else
    {
        std::cout << "Necromancer image failed to load" << std::endl;
    }
}

void Skeleton::Load(sf::Vector2i& windowDimensions, sf::Vector2f position, sf::Texture& textureLoaded)
{
    sprites = new sf::Sprite[spriteNumber];
    sprites[0].setTexture(textureLoaded);

    sprites[0].setTextureRect(sf::IntRect(0,0, width, height));

    sprites[0].scale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
    sprites[0].setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0, position.y * (double)windowDimensions.y / 1080.0));

    hitbox.setSize(sf::Vector2f(0, 0));
    hitbox.setPosition(sf::Vector2f(0, 0));
}

void Skeleton::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters)
{
    sprites[0].setScale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
    sf::Vector2f movement = sf::Vector2f();
    cameraService.MoveSprite(sprites[0], movement);

    if (!activated)
    {
        activatedTimer += deltaTime;
        if (activatedTimer > activationTime)
            activated = true;
    }
}

Projectile* Skeleton::LaunchProjectile(float deltaTime, sf::Texture* projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
	return nullptr;
}

sf::Sprite& Skeleton::getSprite(void) const
{
    return sprites[0];
}

bool Skeleton::SetHealth(int hp)
{
	return false;
}

bool Skeleton::IsActivated(void) const
{
    return activated;
}
