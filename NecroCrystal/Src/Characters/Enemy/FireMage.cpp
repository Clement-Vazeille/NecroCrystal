#include "FireMage.h"
#include <iostream>
#include "../../Projectiles/FireBall.h"
#include "../Necromancer.h"

FireMage::FireMage() : 
    loopAnimation(80,20,128,128),
    fireBallTimer(0),fireBallRefreshTime(400)
{
    scale = 1;
    width = 64;
    height = 64;
    speed = 0.32f;
    sprites = nullptr;
    spriteNumber = 2;
    faction = 2;
    health = 120;
    maxHealth = 120;
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

void FireMage::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map,std::vector<Character*>& characters)
{
    sf::Vector2f movement = sf::Vector2f(0, 0);
    cameraService.MoveSprite(sprites[0], movement);
    cameraService.MoveSprite(sprites[1], movement);
    sprites[0].setScale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));
    sprites[1].setScale(sf::Vector2f(2 * scale * (double)windowDimensions.x / 1920.0, 1.5 * scale * (double)windowDimensions.y / 1080.0));
    loopAnimation.Update(sprites[0],deltaTime);

    hitbox.setScale(sprites[0].getScale());
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());

    //this->LaunchFireball();
}

Projectile* FireMage::LaunchProjectile(float deltaTime, sf::Texture* projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
    fireBallTimer += deltaTime;
    if(fireBallTimer >= fireBallRefreshTime)
    {
        fireBallTimer = 0;
        Projectile* fireBall = new FireBall();
        sf::Vector2f initialPosition = sprites[0].getPosition() + (sf::Vector2f(sprites[0].getScale().x * texture.getSize().x / 1.5f, 0));
        sf::Vector2f spellTarget = ((Necromancer*)characters[0])->getSprite().getPosition() + 2.0f *
            sf::Vector2f(48 * (float)windowDimensions.x / 1920.0f, 6 * (float)windowDimensions.y / 1080.0f);
        fireBall->Load(projectilesTextures[1], initialPosition, spellTarget, windowDimensions);
        //projectileHandler.CreateFireBall(characters, windowDimensions, sprites[0].getPosition() +
        //(sf::Vector2f(sprites[0].getScale().x * texture.getSize().x / 1.5f, 0)));
        return fireBall;
    }
    return nullptr;
}

sf::Sprite& FireMage::getSprite(void) const
{
    return sprites[0];
}