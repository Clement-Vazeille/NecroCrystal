#include "Necromancer.h"
#include"../Utilities/Math.h"
#include "../Projectiles/DarkProjectile.h"
#include <iostream>

Necromancer::Necromancer() : 
    darkProjectileTimer(0), darkProjectileCastSpeed(520),
    loopAnimation(120, 7, 64, 64),faceRight(true),
    healthAnimation(0, 17, 64, 64), removedNotCountedHealth(0)
{
    scale = 2;
    width = 64;
    height = 64;
    speed = 0.35f;
    spriteNumber = 2;
    sprites.resize(spriteNumber);
    faction = 1;
    health =100;
    maxHealth = 100;
}

Necromancer::~Necromancer()
{
}

void Necromancer::Load(sf::Vector2i& windowDimensions,sf::Vector2f position)
{
    if (texture.loadFromFile("Assets/Player/Textures/necromancerWalking.png"))
    {
        std::cout << "Necromancer image loaded successfully" << std::endl;
        sprites[0].setTexture(texture);

        int XNIndex = 0;
        int YNIndex = 0;
        sprites[0].setTextureRect(sf::IntRect(XNIndex * width, YNIndex * height, width, height));
        hitbox.setSize(sprites[0].getGlobalBounds().getSize());

        sprites[0].scale(sf::Vector2f(scale* ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
        sprites[0].setPosition(sf::Vector2f(position.x* (double)windowDimensions.x / 1920.0, position.y* (double)windowDimensions.y / 1080.0));
        loopAnimation.SetTextureRect(sprites[0]);

        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(-1);
        hitbox.setFillColor(sf::Color::Transparent);

        hitbox.setScale(sprites[0].getScale().x * 0.5, sprites[0].getScale().y);
        hitbox.setPosition(sprites[0].getGlobalBounds().getPosition() +
            Math::windowNormalizeVector(sf::Vector2f(sprites[0].getGlobalBounds().width * 0.25, 0), windowDimensions));
    }
    else
    {
        std::cout << "Necromancer image failed to load" << std::endl;
    }

    if (healthTexture.loadFromFile("Assets/Player/Textures/necroHealthBar.png"))
    {
        std::cout << "Necro HealthBar image loaded successfully" << std::endl;
        sprites[1].setTexture(healthTexture);

        healthAnimation.SetTextureRect(sprites[1]);
        sprites[1].setScale(sf::Vector2f(2.5 * scale *  (double)windowDimensions.x / 1920.0, 2.5*scale * (double)windowDimensions.y / 1080.0));
        sprites[1].setPosition(sf::Vector2f(0,0));
    }
    else
    {
        std::cout << "Healthbar image failed to load" << std::endl;
    }
}

void Necromancer::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime,Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
    sprites[0].setScale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
    sprites[1].setScale(sf::Vector2f(2.5 * scale * (double)windowDimensions.x / 1920.0, 2.5 * scale * (double)windowDimensions.y / 1080.0));
    hitbox.setScale(sprites[0].getScale().x * 0.5, sprites[0].getScale().y);

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

    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition() +
        Math::windowNormalizeVector(sf::Vector2f(sprites[0].getGlobalBounds().width * 0.25, 0), windowDimensions));
}

Projectile* Necromancer::LaunchProjectile(float deltaTime,sf::Texture* projectilesTextures,sf::Vector2i windowDimensions,sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
    darkProjectileTimer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && darkProjectileTimer > darkProjectileCastSpeed) //darkSpell Creator
    {
        darkProjectileTimer = 0;

        Projectile* darkProjectile = new DarkProjectile();
        sf::Vector2f spellPosition = sprites[0].getPosition() +
            sf::Vector2f(sprites[0].getGlobalBounds().width*0.05f, sprites[0].getGlobalBounds().height*0.16f);
        if (faceRight)
            spellPosition = spellPosition + sf::Vector2f(sprites[0].getGlobalBounds().width * 0.60f, 0);
        darkProjectile->Load(projectilesTextures[0], spellPosition, mousePosition, windowDimensions);
        return darkProjectile;
    }
    return nullptr;
}


const sf::Sprite& Necromancer::getSprite(void) const
{
    return sprites[0];
}

bool Necromancer::TakeDamage(int damage)
{
    removedNotCountedHealth += damage*damageMultiplier;
    health -= damage*damageMultiplier;

    while (removedNotCountedHealth / (double)maxHealth >= 1.0 / 16.0)    //update the sprite of the health bar
    {
        removedNotCountedHealth -= (double)maxHealth / 16.0;
        healthAnimation.Update(sprites[1], 0);
    }

    return(health <= 0);
}
