#include "Skeleton.h"
#include <iostream>
#include "../Utilities/Math.h"

Skeleton::Skeleton() :
    faceRight(true),
    activated(false), activatedTimer(0),activationTime(1000),
    aD(50)
{
    scale = 2;
    width = 64;
    height = 64;
    speed = 1.35f;
    sprites = nullptr;
    spriteNumber = 1;
    faction = -1;  //TODO -1 = inciblable même si c'est pas un problème pour le moment car les frérots ont pas de hitbox
    health = 1;
    maxHealth = 1;
}

Skeleton::~Skeleton()
{
    Character::~Character();
}

void Skeleton::Load(sf::Vector2i& windowDimensions, sf::Vector2f position)
{
    //Shouldn't be used, here because Skeleton is inherited from character
}

void Skeleton::Load(sf::Vector2i& windowDimensions, sf::Vector2f position, sf::Texture& textureLoaded)
{
    sprites = new sf::Sprite[spriteNumber];
    sprites[0].setTexture(textureLoaded);

    sprites[0].setTextureRect(sf::IntRect(0,0, width, height));
    hitbox.setSize(sprites[0].getGlobalBounds().getSize());

    sprites[0].scale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
    sprites[0].setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0, position.y * (double)windowDimensions.y / 1080.0));

    target = sprites[0].getPosition();

    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(-1);
    hitbox.setFillColor(sf::Color::Transparent);

    hitbox.setScale(sprites[0].getScale());
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());
}

void Skeleton::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters)
{
    sprites[0].setScale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
    hitbox.setScale(sprites[0].getScale());

    cameraService.UpdateVector(target);
    sf::Vector2f movement = Math::normalizeVector(target-sprites[0].getPosition())*speed*deltaTime;
    Math::CorrectMovement(movement,hitbox, map);

    cameraService.MoveSprite(sprites[0], movement);
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());


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

void Skeleton::AttackAnimation(void)
{
}

void Skeleton::StartDash(sf::Vector2f necroPosition)
{
    target = necroPosition + (necroPosition - sprites[0].getPosition());
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

const float Skeleton::GetAD(void) const
{
    return aD;
}
