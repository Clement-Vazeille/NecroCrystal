#include "FireMage.h"

#include <iostream>
#include "../../Projectiles/IndividualProjectiles/FireBall.h"
#include "../Necromancer.h"
#include "../../Utilities/Math.h"

FireMage::FireMage() : 
    loopAnimation(80,20,128,128),
    fireBallTimer(700),fireBallRefreshTime(1900),  // devrait scale avec les hp ?
    newDirectionCooldown(1800),newDirectionTimer(1800),
    fearDistance(200) // doit scale entre 200 et 700 selon les hp manquants
{
    scale = 1;
    width = 64;
    height = 64;
    speed = 0.13f;
    spriteNumber = 2; //compte la barre de vie
    sprites.resize(spriteNumber);
    faction = 2;
    maxHealth = 140;
    health = maxHealth;
    activationTime = 800;
}

FireMage::~FireMage()
{
}

void FireMage::Load(sf::Vector2i& windowDimensions,sf::Vector2f position)
{
    if (texture.loadFromFile("Assets/OtherMages/FireMage/fireMageSpriteSheet.png"))
    {
        //std::cout << "FireMage image loaded successfully" << std::endl;
        sprites[0].setTexture(texture);

        loopAnimation.SetTextureRect(sprites[0]);
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

    hitbox.setScale(sprites[0].getScale().x * 0.5, sprites[0].getScale().y);
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition() +
        Math::windowNormalizeVector(sf::Vector2f(sprites[0].getGlobalBounds().width * 0.25, 0), windowDimensions));
    //std::cout << "fire Mage Serial is : " << serial << std::endl;
}

void FireMage::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map,std::vector<Character*>& characters, 
    RandomLSFR& randomLSFR, VFXHandler& vFXHandler)
{
    sf::Vector2f movement = sf::Vector2f();
    newDirectionTimer += deltaTime;

    if (!activated)
    {
        activationTimer += deltaTime;
        if(activationTimer>activationTime)
            activated = true;
    }

    if(activated)
    {
        if (newDirectionTimer > newDirectionCooldown)
        {
            newDirectionTimer = 0;
            direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());
            if (Math::Distance(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition(),windowDimensions) < fearDistance * (3.f - 2.f * (float)health / (float)maxHealth))
                direction = -direction * 1.2f;
        }
        movement = Math::windowNormalizeVector(direction * speed * (2.5f - 1.5f * (float)health / (float)maxHealth) * deltaTime, windowDimensions);
        //speed boosted when low hp
        Math::CorrectMovement(movement, hitbox, map);
    }

    cameraService.MoveSprite(sprites[0], movement);
    cameraService.MoveSprite(sprites[1], movement);
    sprites[0].setScale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));
    sprites[1].setScale(sf::Vector2f(healthBarScaleX * (double)windowDimensions.x / 1920.0, healthBarScaleY * (double)windowDimensions.y / 1080.0));
    loopAnimation.Update(sprites[0],deltaTime);

    hitbox.setScale(sprites[0].getScale().x * 0.5, sprites[0].getScale().y);
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition() +
        Math::windowNormalizeVector(sf::Vector2f(sprites[0].getGlobalBounds().width * 0.25, 0), windowDimensions));
}

Projectile* FireMage::LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
    if(activated)
    {
        fireBallTimer += deltaTime;
        if (fireBallTimer >= fireBallRefreshTime)
        {
            fireBallTimer = 0;
            Projectile* fireBall = new FireBall();
            sf::Vector2f initialPosition = sprites[0].getPosition() + (sf::Vector2f(sprites[0].getScale().x * sprites[0].getTextureRect().getSize().x / 8.0f, sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y / 2.0f));
            sf::Vector2f spellTarget = ((Necromancer*)characters[0])->getSprite().getPosition() + 2.0f *
                sf::Vector2f(48 * (float)windowDimensions.x / 1920.0f, 6 * (float)windowDimensions.y / 1080.0f);
            fireBall->Load(projectilesTextures.GetFireBall(), initialPosition, spellTarget, windowDimensions);
            return fireBall;
        }
    }
    return nullptr;
}

const sf::Sprite& FireMage::getSprite(void) const
{
    return sprites.at(0);
}