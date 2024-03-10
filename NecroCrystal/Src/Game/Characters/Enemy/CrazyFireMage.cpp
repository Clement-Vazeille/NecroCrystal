#include "CrazyFireMage.h"
#include <iostream>
#include "../Necromancer.h"
#include "../../Utilities/Math.h"

void CrazyFireMage::SelectNewAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
    newActionTimer += deltaTime;
    if (newActionTimer >= newActionCooldown)
    {
        newActionTimer = 0;
        //Les actions possibles
        //Tourniquet: marche plutôt lentement vers le nécromancien avec un tourniquet de feu autour de lui
        //  Plus probable si le necro est proche de lui
        //Dash: Dash (out ou in selon les hp actuels et la distance au necro)
        //  et laisse derrière lui une trainée de feu imobile qui inflige des dégats
        //Explosion: Sort de base, au début de l'action met 3 vfx de préparation d'explosion sous le nécromancien
        //  puis à la fin créer une explosion qui fait bien mal (l'explosion est un cercle qui s'agrandit)
        //Fury: un dash avec une vitesse augmentée, durée réduite,lance 1 explosions
        //  est lancé automatiquement lorsqu'il est à < 10%hp

        int randomIntChoixAction = randomLSFR.randomUpTo(100);//nombre choisis entre 0 et 100

        switch (currentAction)
        {
        case Tourniquet:
        {
            damageMultiplier = 1.f;
        }
        break;
        case Dash:
        {
            damageMultiplier = 1.f;
        }
        break;
        case Explosion:
        {
            damageMultiplier = 1.f;
        }
        break;
        case Fury:
        {
            damageMultiplier = 0.6f;
        }
        break;
        default:
        {
            std::cout << "Unknown action asked for crazy fire mage" << std::endl;
        }
        break;
        }
    }
}

void CrazyFireMage::Flip(void)
{
    for (auto& animation : animations)
    {
        animation.Flip();
    }
}

CrazyFireMage::CrazyFireMage() :
    newActionCooldown(2500), newActionTimer(2500),
    currentAction(Tourniquet),
    isFacingRight(true),
    animations({Animation(120,1,64,64) }),
    dashSpeed(0.45f),furySpeed(0.65f)
{
    scale = 2;
    width = 64;
    height = 64;
    speed = 0.15f;
    spriteNumber = 2;  //compte la barre de vie
    sprites.resize(spriteNumber);
    faction = 2;
    maxHealth = 300;
    health = maxHealth;
    activationTime = 600;
}

CrazyFireMage::~CrazyFireMage()
{
}

void CrazyFireMage::Load(sf::Vector2i& windowDimensions, sf::Vector2f position)
{

    if (texture.loadFromFile("Assets/OtherMages/CrazyFireMage/CrazyFireMage.png"))
    {
        sprites.at(0).setTexture(texture);

        animations.at(currentAction).SetTextureRect(sprites.at(0));
        hitbox.setSize(sprites.at(0).getGlobalBounds().getSize());
        sprites.at(0).scale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));//multiplie la taille par scale (c'est 2)
        sprites.at(0).setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0, position.y * (double)windowDimensions.y / 1080.0));
    }
    else
    {
        std::cout << "Crazy Fire Mage image failed to load" << std::endl;
    }

    this->LoadHealthBar(windowDimensions, position);

    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(-1);
    hitbox.setFillColor(sf::Color::Transparent);

    hitbox.setScale(sprites[0].getScale().x * 0.5, sprites[0].getScale().y);
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition() +
        Math::windowNormalizeVector(sf::Vector2f(sprites[0].getGlobalBounds().width * 0.25, 0), windowDimensions));
}

void CrazyFireMage::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR, VFXHandler& vFXHandler)
{

    sf::Vector2f movement = sf::Vector2f();
    sprites.at(0).setScale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));
    sprites.at(1).setScale(sf::Vector2f(healthBarScaleX * (double)windowDimensions.x / 1920.0, healthBarScaleY * (double)windowDimensions.y / 1080.0));

    if (!activated)
    {
        activationTimer += deltaTime;
        if (activationTimer > activationTime)
        {
            activated = true;
        }
    }

    if (characters.at(0)->getHitbox()->getPosition().x < hitbox.getPosition().x && isFacingRight) //mage turn to left
    {
        isFacingRight = false;
        this->Flip();
    }
    if (characters.at(0)->getHitbox()->getPosition().x > hitbox.getPosition().x && !isFacingRight) //mage turn to right
    {
        isFacingRight = true;
        this->Flip();
    }

    if (activated)
    {
        this->SelectNewAction(windowDimensions, deltaTime, map, characters, randomLSFR);
    }
    //movement part
    if (activated)
    {
        switch (currentAction)
        {
        case Tourniquet:
        {
            direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());
            movement = Math::windowNormalizeVector(direction * speed * deltaTime, windowDimensions);
        }
        break;
        case Dash:
        {
            direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());
            movement = Math::windowNormalizeVector(direction * dashSpeed * deltaTime, windowDimensions);
        }
        break;
        case Explosion:
        {
            direction = sf::Vector2f(0, 0);
            movement = sf::Vector2f(0, 0);
        }
        break;
        case Fury:
        {
            direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());
            movement = Math::windowNormalizeVector(direction * furySpeed * deltaTime, windowDimensions);
        }
        break;

        default:
        {
            std::cout << "Unknown movement asked for Crazy Fire Mage" << std::endl;
        }
        break;
        }
        Math::CorrectMovement(movement, hitbox, map);

        animations.at(currentAction).Update(sprites[0], deltaTime);
    }

    cameraService.MoveSprite(sprites[0], movement);
    cameraService.MoveSprite(sprites[1], movement);



    hitbox.setScale(sprites[0].getScale().x * 0.5, sprites[0].getScale().y);
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition() +
        Math::windowNormalizeVector(sf::Vector2f(sprites[0].getGlobalBounds().width * 0.25, 0), windowDimensions));

}

Projectile* CrazyFireMage::LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
	return nullptr;
}

const sf::Sprite& CrazyFireMage::getSprite(void) const
{
    return sprites.at(0);
}
