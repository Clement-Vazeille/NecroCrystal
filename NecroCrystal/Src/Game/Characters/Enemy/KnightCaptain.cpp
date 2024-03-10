#include "KnightCaptain.h"
#include <iostream>
#include "../Necromancer.h"
#include "../../Utilities/Math.h"

void KnightCaptain::SelectNewAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
    newActionTimer += deltaTime;
    if (newActionTimer >= newActionCooldown)
    {
        newActionTimer = 0;
        //Les actions possibles
        // Globalement le choix des actions est pas hyper influenc� par quoi que ce soit
        //Marcher: elle court simplement vers le n�cormancien un peu moins vite que lui (dure pas longtemps)
        //  action de base influenc�e par rien
        //Lancer: devient immobile et lance 2/3 fois (d�pend du nombre de pri�res) 3 marteaux celui du milieu visant le necro
        //Jump: Saute sur le necro et une fois arriv�e fait boom boom avec son marteau sur le son (vitesse augment avec le nombre de pri�re?)
        //Bouclier: Se prot�ge avec son bouclier et � la fin met un coup circulaire autour d'elle de marteau
        //Priere: Se lance automatiquement lorsqu'elle a 70%, 40%, et 10% hp, elle est invincible pendant ce temps et �a la boost

        currentAction = KnightCaptain::Action(randomLSFR.randomUpTo(3));//choisit al�atoirement de fa�on une action parmis les 4 possibles
        switch (currentAction)
        {
        case Marcher:
        {
            damageMultiplier = 0.8;
        }
        break;
        case Lancer:
        {
            damageMultiplier = 1.f;
        }
        break;
        case Jump:
        {
            damageMultiplier = 1.2f;
        }
        break;
        case Bouclier:
        {
            damageMultiplier = 0.6f;
        }
        case Priere:
        {
            damageMultiplier = 0.f;
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

void KnightCaptain::Flip(void)
{
    for (auto& animation : animations)
    {
        animation.Flip();
    }
}

KnightCaptain::KnightCaptain() :
    newActionCooldown(2200), newActionTimer(0),
    currentAction(Marcher),
    isFacingRight(true),
    animations({ Animation(120,1,88,64) }),
    shieldingSpeed(0.15f)
{
    scale = 2;
    width = 64;
    height = 64;
    speed = 0.25f;
    spriteNumber = 2;  //compte la barre de vie
    sprites.resize(spriteNumber);
    faction = 2;
    maxHealth = 800;
    health = maxHealth;
    activationTime = 600;
}

KnightCaptain::~KnightCaptain()
{
}

void KnightCaptain::Load(sf::Vector2i& windowDimensions, sf::Vector2f position)
{

    if (texture.loadFromFile("Assets/OtherMages/KnightCaptain/KnightCaptain.png"))
    {
        sprites.at(0).setTexture(texture);

        animations.at(currentAction).SetTextureRect(sprites.at(0));
        hitbox.setSize(sprites.at(0).getGlobalBounds().getSize());
        sprites.at(0).scale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));//multiplie la taille par scale (c'est 2)
        sprites.at(0).setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0, position.y * (double)windowDimensions.y / 1080.0));
    }
    else
    {
        std::cout << "Knight captain image failed to load" << std::endl;
    }

    this->LoadHealthBar(windowDimensions, position + sf::Vector2f(20.f, 0));

    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(-1);
    hitbox.setFillColor(sf::Color::Transparent);

    hitbox.setScale(sprites[0].getScale().x * 0.5, sprites[0].getScale().y);
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition() +
        Math::windowNormalizeVector(sf::Vector2f(sprites[0].getGlobalBounds().width * 0.25, 0), windowDimensions));
}

void KnightCaptain::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR, VFXHandler& vFXHandler)
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
        case Marcher:
        {
            direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());
            movement = Math::windowNormalizeVector(direction * speed * deltaTime, windowDimensions);
        }
        break;
        case Lancer:
        {
            direction = sf::Vector2f(0, 0);
            movement = sf::Vector2f(0, 0);
        }
        break;
        case Jump:
        {
            direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());
            movement = Math::windowNormalizeVector(direction * speed * deltaTime, windowDimensions);
        }
        break;
        case Bouclier:
        {
            direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());
            movement = Math::windowNormalizeVector(direction * shieldingSpeed * deltaTime, windowDimensions);
        }
        case Priere:
        {
            direction = sf::Vector2f(0, 0);
            movement = sf::Vector2f(0, 0);
        }
        break;
        default:
        {
            std::cout << "Unknown movement asked for Crazy Fire Mage" << std::endl;
        }
        break;
        }
        Math::CorrectMovement(movement, hitbox, map);

        //animations.at(currentAction).Update(sprites[0], deltaTime);
    }

    cameraService.MoveSprite(sprites[0], movement);
    cameraService.MoveSprite(sprites[1], movement);



    hitbox.setScale(sprites[0].getScale().x * 0.5, sprites[0].getScale().y);
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition() +
        Math::windowNormalizeVector(sf::Vector2f(sprites[0].getGlobalBounds().width * 0.25, 0), windowDimensions));

}

Projectile* KnightCaptain::LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
    return nullptr;
}

const sf::Sprite& KnightCaptain::getSprite(void) const
{
    return sprites.at(0);
}
