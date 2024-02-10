#include "MeleeMage.h"
#include <iostream>
#include "../Necromancer.h"
#include "../../Utilities/Math.h"

MeleeMage::MeleeMage() :
    loopAnimation(80, 2, 64, 64),
    newActionCooldown(1800), newActionTimer(1800)
{
    scale = 2;
    width = 64;
    height = 64;
    speed = 0.16f;
    spriteNumber = 2;  //compte la barre de vie
    sprites.resize(spriteNumber);
    faction = 2;
    maxHealth = 250;
    health = maxHealth;
    activatedDistance = 800;
}

MeleeMage::~MeleeMage()
{
}

void MeleeMage::Load(sf::Vector2i& windowDimensions, sf::Vector2f position)
{

    if (texture.loadFromFile("Assets/OtherMages/MeleeMage/MeleeMage.png"))
    {
        //std::cout << "FireMage image loaded successfully" << std::endl;
        sprites[0].setTexture(texture);

        loopAnimation.SetTextureRect(sprites[0]);
        hitbox.setSize(sprites[0].getGlobalBounds().getSize());
        sprites[0].scale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));//multiplie la taille par scale (c'est 2)
        sprites[0].setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0, position.y * (double)windowDimensions.y / 1080.0));
    }
    else
    {
        std::cout << "Melee Mage image failed to load" << std::endl;
    }

    this->LoadHealthBar(windowDimensions, position);

    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(-1);
    hitbox.setFillColor(sf::Color::Transparent);

    hitbox.setScale(sprites[0].getScale());
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());
}

void MeleeMage::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters)
{

    sf::Vector2f movement = sf::Vector2f();
    if (Math::DistanceLat(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition(), windowDimensions) < activatedDistance)
        activated = true;
    if (activated)
    {
        movement = Math::windowNormalizeVector(direction * speed * (2.5f - 1.5f * (float)health / (float)maxHealth) * deltaTime, windowDimensions);
        //speed boosted when low hp
        Math::CorrectMovement(movement, hitbox, map);
    }

    cameraService.MoveSprite(sprites[0], movement);
    cameraService.MoveSprite(sprites[1], movement);
    sprites[0].setScale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));
    sprites[1].setScale(sf::Vector2f(healthBarScaleX * (double)windowDimensions.x / 1920.0, healthBarScaleY * (double)windowDimensions.y / 1080.0));
    loopAnimation.Update(sprites[0], deltaTime);

    hitbox.setScale(sprites[0].getScale());
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());
}

Projectile* MeleeMage::LaunchProjectile(float deltaTime, sf::Texture* projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
    if (activated)
    {
        newActionTimer += deltaTime;
        if (newActionTimer >= newActionCooldown)
        {
            newActionTimer = 0;
        }
    }
	return nullptr;
}

const sf::Sprite& MeleeMage::getSprite(void) const
{
    return sprites.at(0);
}
