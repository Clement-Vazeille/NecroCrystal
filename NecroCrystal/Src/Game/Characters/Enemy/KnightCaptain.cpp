#include "KnightCaptain.h"
#include <iostream>
#include "../Necromancer.h"
#include "../../Utilities/Math.h"
#include "../../Projectiles/IndividualProjectiles/KnightCaptain/HammerThrow.h"
#include "../../Projectiles/IndividualProjectiles/KnightCaptain/CaptainSlash.h"

void KnightCaptain::SelectNewAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
    newActionTimer += deltaTime;
    if (newActionTimer >= newActionCooldown)
    {
        newActionTimer = 0;

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

        //Les actions possibles
        // Globalement le choix des actions est pas hyper influencé par quoi que ce soit
        //Marcher: elle court simplement vers le nécromancien un peu moins vite que lui (dure pas longtemps)
        //  action de base influence par rien
        //Lancer: devient immobile et lance 2/3 fois (dépend du nombre de prieres) 3 marteaux celui du milieu visant le necro
        //Jump: Saute sur le necro et une fois arrive fait boom boom avec son marteau sur le son (vitesse augment avec le nombre de pri鑽e?)
        //Bouclier: Se protège avec son bouclier et à la fin met un coup circulaire de marteau autour d'elle
        //Priere: Se lance automatiquement lorsqu'elle a 70%, 40%, et 10% hp, elle est invincible pendant ce temps,à la boost et à la fin elle aoe (meme aoe que bouclier)

        currentAction = KnightCaptain::Action(randomLSFR.randomUpTo(3));//choisit aleatoirement de faire une action parmis les 4 possibles
        if (willStartPraying)
        {
            willStartPraying = false;
            currentAction = Priere;
        }
        switch (currentAction)
        {
        case Marcher:
        {
            damageMultiplier = 0.8;
            newActionTimer = newActionCooldown - (marcherTime* (1.f - (prayCounter*0.2f) ));
        }
        break;
        case Lancer:
        {
            damageMultiplier = 1.f;
            newActionTimer = newActionCooldown - lancerTime;
        }
        break;
        case Jump:
        {
            hasNotJumpAttacked = true;

            damageMultiplier = 1.2f;
            sf::Vector2f target = characters[0]->getHitbox()->getPosition() +
                sf::Vector2f(sprites[0].getScale().x * sprites[0].getTextureRect().getSize().x* 0.32f, 0);
            if (isFacingRight)
            {
                 target = characters[0]->getHitbox()->getPosition() -
                    sf::Vector2f(sprites[0].getScale().x * sprites[0].getTextureRect().getSize().x * 0.32f, 0);
            }
                
            direction = Math::normalizeVector(target - sprites[0].getPosition());
            jumpSpeed = Math::Distance(target - sprites[0].getPosition(),windowDimensions)/jumpAirTime;
            newActionTimer = newActionCooldown - jumpTime ;
            jumpTimer = 0;
        }
        break;
        case Bouclier:
        {
            damageMultiplier = 0.6f;
            shieldingTimer = 0;
            newActionTimer = newActionCooldown - shieldTime;
        }
        break;
        case Priere:
        {
            damageMultiplier = 0.f;
            prayCounter++;
            newActionTimer = newActionCooldown - prayTime ;
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
    animations({ Animation(120,1,88,64,0,0),Animation(120,1,88,64,1,0),Animation(120,1,88,64,2,0),
        Animation(120,1,88,64,3,0) ,Animation(120,1,88,64,4,0) }),
    shieldingSpeed(0.15f),hasNotJumpAttacked(true),
    prayTime(1100),lancerTime(1400),marcherTime(800),
    shieldTime(1800),shieldPrepTime(1200),shieldingTimer(0),
    jumpTime(2400),jumpTimer(0),jumpAirTime(400),jumpSpeed(0),
    hammerThrowTimer(0),throwNumber(0),
    willStartPraying(false),invincibilityStartersIndex(0),
    invincibilityStarters({0.8f,0.5f,0.2f}),
    prayCounter(0)
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
            jumpTimer += deltaTime;
            if (jumpTimer <= jumpAirTime)
                movement = Math::windowNormalizeVector(direction * jumpSpeed * deltaTime, windowDimensions);
            else
                movement = sf::Vector2f(0, 0);
        }
        break;
        case Bouclier:
        {            
            if (shieldingTimer < 0) //correspond à lorsque le coup de marteau est donné
            {
                direction = sf::Vector2f(0, 0);
                movement = sf::Vector2f(0, 0);
            }
            else
            {
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

                direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());
                movement = Math::windowNormalizeVector(direction * shieldingSpeed * deltaTime * (1.f+(prayCounter * 0.8f)), windowDimensions);
            }
            
        }
        break;
        case Priere:
        {
            direction = sf::Vector2f(0, 0);
            movement = sf::Vector2f(0, 0);
        }
        break;
        default:
        {
            std::cout << "Unknown movement asked for Knight Captain" << std::endl;
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

Projectile* KnightCaptain::LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
    if (activated)
    {
        switch (currentAction)
        {
        case Lancer: {
            hammerThrowTimer += deltaTime;
            if (hammerThrowTimer >= lancerTime / (2.f+(prayCounter*1.5f)))
            {
                Projectile* hammerThrow = new HammerThrow();
                sf::Vector2f initialPosition = sprites[0].getPosition() + (sf::Vector2f(0, sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y * 0.05f));
                sf::Vector2f direction(characters.at(0)->getHitbox()->getPosition());
                
                if (throwNumber == 0)
                {
                    sf::Vector2f trajectory = direction - initialPosition;
                    direction = direction + (sf::Vector2f(trajectory.y, -trajectory.x) * 0.3f);
                }
                if (throwNumber == 2)
                {
                    sf::Vector2f trajectory = direction - initialPosition;
                    direction = direction - (sf::Vector2f(trajectory.y, -trajectory.x) * 0.3f);
                }
                
                hammerThrow->Load(projectilesTextures.GetHammer(), initialPosition, direction, windowDimensions);

                if (throwNumber++ == 2)
                {
                    throwNumber = 0;
                    hammerThrowTimer -= lancerTime / (2.f + (prayCounter * 1.5f));
                }
                
                return hammerThrow;
            }
            return nullptr;
            
        }
            break;
        case Bouclier: {
            shieldingTimer += deltaTime;
            if (shieldingTimer >= shieldPrepTime)
            {
                shieldingTimer = -10000; //makes there will only be one attack per shield stance taken
                Projectile* captainSlash = new CaptainSlash();
                sf::Vector2f slashPosition = sprites[0].getPosition() + 
                    (sf::Vector2f(sprites[0].getScale().x * sprites[0].getTextureRect().getSize().x * 1.f, 
                        sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y * -1.5f));
                if(isFacingRight)
                    slashPosition = sprites[0].getPosition() +
                    (sf::Vector2f(sprites[0].getScale().x * sprites[0].getTextureRect().getSize().x * -1.f,
                        sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y * -1.5f));
                captainSlash->Load(projectilesTextures.GetCaptainSlash(), slashPosition, slashPosition, windowDimensions);
                return captainSlash;
            }
        }
            break;
        case Jump: {
            if (jumpTimer >= jumpAirTime && hasNotJumpAttacked)
            {
                hasNotJumpAttacked = false; //makes there will only be one attack per jump
                Projectile* captainSlash = new CaptainSlash();
                sf::Vector2f slashPosition = sprites[0].getPosition() +
                    (sf::Vector2f(sprites[0].getScale().x * sprites[0].getTextureRect().getSize().x * 1.f,
                        sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y * -1.5f));
                if (isFacingRight)
                    slashPosition = sprites[0].getPosition() +
                    (sf::Vector2f(sprites[0].getScale().x * sprites[0].getTextureRect().getSize().x * -1.f,
                        sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y * -1.5f));
                captainSlash->Load(projectilesTextures.GetCaptainSlash(), slashPosition, slashPosition, windowDimensions);
                return captainSlash;
            }
        }
            break;


        default:{
            return nullptr;
        }
            break;
        }

    }
    return nullptr;
}

const sf::Sprite& KnightCaptain::getSprite(void) const
{
    return sprites.at(0);
}

bool KnightCaptain::TakeDamage(int hp)
{
    if (willStartPraying)
    {
        return false;
    }
    bool ans = Enemy::TakeDamage(hp);
    if (invincibilityStartersIndex < invincibilityStarters.size())
    {
        if (health <= invincibilityStarters.at(invincibilityStartersIndex)*maxHealth)
        {
            willStartPraying = true;
            invincibilityStartersIndex++;
        }
    }
    return ans;
}

