#include "Necromancer.h"
#include"../Utilities/Math.h"
#include "../Projectiles/DarkProjectile.h"
#include <iostream>

Necromancer::Necromancer() : 
    darkProjectileTimer(0), darkProjectileCastSpeed(600),
    loopAnimation(120, 7, 64, 64),faceRight(true),
    healthAnimation(0, 17, 64, 64), removedNotCountedHealth(0)
{
    scale = 2;
    width = 64;
    height = 64;
    speed = 0.35f;
    sprites = nullptr;
    spriteNumber = 2;
    faction = 1;
    health =100;
    maxHealth = 100;
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
        sprites = new sf::Sprite[spriteNumber];
        sprites[0].setTexture(texture);

        int XNIndex = 0;
        int YNIndex = 0;
        sprites[0].setTextureRect(sf::IntRect(XNIndex * width, YNIndex * height, width, height));
        hitbox.setSize(sprites[0].getGlobalBounds().getSize());

        sprites[0].scale(sf::Vector2f(scale* ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
        sprites[0].setPosition(sf::Vector2f(position.x* (double)windowDimensions.x / 1920.0, position.y* (double)windowDimensions.y / 1080.0));
        loopAnimation.Initialize(sprites[0]);

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

    if (healthTexture.loadFromFile("Assets/Player/Textures/necroHealthBar.png"))
    {
        std::cout << "Necro HealthBar image loaded successfully" << std::endl;
        sprites[1].setTexture(healthTexture);

        healthAnimation.Initialize(sprites[1]);
        sprites[1].setScale(sf::Vector2f(2.5 * scale *  (double)windowDimensions.x / 1920.0, 2.5*scale * (double)windowDimensions.y / 1080.0));
        sprites[1].setPosition(sf::Vector2f(0,0));
    }
    else
    {
        std::cout << "Healthbar image failed to load" << std::endl;
    }
}

void Necromancer::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime,Map& map, std::vector<Character*>& characters)
{
    sprites[0].setScale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
    sprites[1].setScale(sf::Vector2f(2.5 * scale * (double)windowDimensions.x / 1920.0, 2.5 * scale * (double)windowDimensions.y / 1080.0));
    hitbox.setScale(sprites[0].getScale());

    sf::Vector2f position = sprites[0].getPosition();
    sf::Vector2f change = sf::Vector2f(0.0f, 0.0f);
    bool moved = false;
    bool turned = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        change += sf::Vector2f(1 * (float)windowDimensions.x / 1920.f, 0)*speed*deltaTime;
        moved = true;
        if (!faceRight)
            turned = true;
        faceRight = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        change -= sf::Vector2f(1 * (float)windowDimensions.x /1920.f, 0)*speed*deltaTime;
        moved = true;
        if (faceRight && !turned)
        {
            turned = true;
            faceRight = false;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
         change -= sf::Vector2f(0, 1 * (float)windowDimensions.y / 1080.f) * speed * deltaTime;
         moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        change += sf::Vector2f(0, 1 * (float)windowDimensions.y / 1080.0f) * speed * deltaTime;
        moved = true;
    }

    //-----------------------------------------WALL COLLISION TEST------------------------------------------------------
    Math::CorrectMovement(change, hitbox, map);

    if (change.x != 0.0f && change.y != 0.0f)
        change = change * 0.85f;

    cameraService.Update(-change.y,sf::Vector2f(windowDimensions));
    cameraService.MoveSprite(sprites[0], change);

    if (turned)
        loopAnimation.Flip();
    if (moved)
        loopAnimation.Update(sprites[0], deltaTime);
    else
        loopAnimation.Reset(sprites[0]);

    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());
}

Projectile* Necromancer::LaunchProjectile(float deltaTime,sf::Texture* projectilesTextures,sf::Vector2i windowDimensions,sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
    darkProjectileTimer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && darkProjectileTimer > darkProjectileCastSpeed) //darkSpell Creator
    {
        darkProjectileTimer = 0;

        Projectile* darkProjectile = new DarkProjectile();
        sf::Vector2f spellPosition = (sprites[0].getPosition() + 2.0f *
            sf::Vector2f(48 * (float)windowDimensions.x / 1920.0f, 6 * (float)windowDimensions.y / 1080.0f));
        darkProjectile->Load(projectilesTextures[0], spellPosition, mousePosition, windowDimensions);
        return darkProjectile;
    }
    return nullptr;
}


sf::Sprite& Necromancer::getSprite(void) const
{
    return sprites[0];
}

bool Necromancer::SetHealth(int hp)
{
    removedNotCountedHealth += health - hp;
    health = hp;

    while (removedNotCountedHealth / (double)maxHealth >= 1.0 / 16.0)    //update the sprite of the health bar
    {
        removedNotCountedHealth -= (double)maxHealth / 16.0;
        healthAnimation.Update(sprites[1], 0);
    }

    return(health <= 0);
}
