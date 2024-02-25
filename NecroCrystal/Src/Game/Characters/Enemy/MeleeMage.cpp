#include "MeleeMage.h"
#include <iostream>
#include "../Necromancer.h"
#include "../../Utilities/Math.h"
#include "../../Projectiles/SwordSlash.h"

void MeleeMage::SelectNewAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
    newActionTimer += deltaTime;
    if (newActionTimer >= newActionCooldown)
    {
        newActionTimer = 0;
        //Les actions possibles
        //Marcher: il court simplement vers le nécormancien un peu moins vite qui lui
        //Attaquer: léger dash avec un coup d'épée, plus probable si il est proche, lock la direction
        //Proteger: avance lentement en se protégeant avec son épée, débat subis /2 (variable dammage multiplier), lock la direction, 
        //          plus probable si low hp

        int randomIntChoixAction = randomLSFR.randomUpTo(100);//nombre choisis entre 0 et 100
        int barreDefMax = 15 + ((maxHealth-health)/maxHealth) * 40; //le melee mage a entre 10 et 45% de chance de se protéger

        float distToNecro = Math::Distance(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition(), windowDimensions);
        float distProche = 450;
        float distMoyen = 220;

        int barreAttMin = 80;
        if (distToNecro < distMoyen)
            barreAttMin = 60;
        if (distToNecro < distProche)
            barreAttMin = 35;

        currentAction = Marcher;
        if (randomIntChoixAction < barreDefMax)
            currentAction = Proteger;
        if (randomIntChoixAction > barreAttMin)
            currentAction = Attaquer;

        switch (currentAction)
        {
        case Marcher:
        {
            damageMultiplier = 1.f;
        }
        break;

        case Attaquer:
        {
            animations.at(currentAction).Reset(sprites[0]);
            if (characters[0]->getHitbox()->getPosition().x < hitbox.getPosition().x && isFacingRight) //mage turn to left
            {
                isFacingRight = false;
                this->Flip();
            }
            if (characters[0]->getHitbox()->getPosition().x > hitbox.getPosition().x && !isFacingRight) //mage turn to right
            {
                isFacingRight = true;
                this->Flip();
            }

            newActionTimer = newActionCooldown - attackDuration;
            direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());
            damageMultiplier = 1.2f;

            canLaunchAttack = true;
        }
        break;

        case Proteger:
        {
            newActionTimer = (int)((float)newActionCooldown * 0.20f);
            direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());
            damageMultiplier = 0.5f;
        }
        break;

        default:
        {
            std::cout << "Unknown action asked for melee mage" << std::endl;
        }
        break;
        }
    }
}

void MeleeMage::Flip(void)
{
    for (auto& animation : animations)
    {
        animation.Flip();
    }
}

MeleeMage::MeleeMage() :
    newActionCooldown(1600), newActionTimer(1600),
    currentAction(Attaquer), canLaunchAttack(false),
    dashSpeedBoost(2.5f), protectSpeedBoost(0.5f),
    isFacingRight(true),
    attackDuration(newActionCooldown*0.6f),
    animations({ Animation(120,4,88,64,0,0),Animation(240,4,88,64,4,0),Animation(120,4,88,64,8,0) })
{
    scale = 2;
    width = 64;
    height = 64;
    speed = 0.25f;
    spriteNumber = 2;  //compte la barre de vie
    sprites.resize(spriteNumber);
    faction = 2;
    maxHealth = 300;
    health = maxHealth;
    activationTime = 1200;
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

        animations.at(currentAction).SetTextureRect(sprites[0]);
        hitbox.setSize(sprites[0].getGlobalBounds().getSize());
        sprites[0].scale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));//multiplie la taille par scale (c'est 2)
        sprites[0].setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0, position.y * (double)windowDimensions.y / 1080.0));
    }
    else
    {
        std::cout << "Melee Mage image failed to load" << std::endl;
    }

    this->LoadHealthBar(windowDimensions, position+sf::Vector2f(20.f,0));

    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(-1);
    hitbox.setFillColor(sf::Color::Transparent);

    hitbox.setScale(sprites[0].getScale().x*0.5, sprites[0].getScale().y);
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition()+
        Math::windowNormalizeVector(sf::Vector2f(sprites[0].getGlobalBounds().width*0.25,0),windowDimensions) );
}

void MeleeMage::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, 
    std::vector<Character*>& characters,RandomLSFR& randomLSFR)
{

    sf::Vector2f movement = sf::Vector2f();
    sprites[0].setScale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));
    sprites[1].setScale(sf::Vector2f(healthBarScaleX * (double)windowDimensions.x / 1920.0, healthBarScaleY * (double)windowDimensions.y / 1080.0));
    
    if (!activated)
    {
        activationTimer += deltaTime;
        if (activationTimer > activationTime)
            activated = true;
    }
    
    if (characters[0]->getHitbox()->getPosition().x < hitbox.getPosition().x && isFacingRight &&currentAction != Attaquer) //mage turn to left
    {
        isFacingRight = false;
        this->Flip();
    }
    if (characters[0]->getHitbox()->getPosition().x > hitbox.getPosition().x && !isFacingRight && currentAction != Attaquer) //mage turn to right
    {
        isFacingRight = true;
        this->Flip();
    }

    this->SelectNewAction(windowDimensions, deltaTime, map, characters,randomLSFR);
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

        case Attaquer:
        {
            movement = Math::windowNormalizeVector(direction * speed * dashSpeedBoost * deltaTime, windowDimensions);
        }
        break;

        case Proteger:
        {
            movement = Math::windowNormalizeVector(direction * speed * protectSpeedBoost * deltaTime, windowDimensions);
        }
        break;

        default:
        {
            std::cout << "Unknown movement asked for melee mage" << std::endl;
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

Projectile* MeleeMage::LaunchProjectile(float deltaTime, sf::Texture* projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
    if (activated && canLaunchAttack)
    {
        canLaunchAttack = false;
        Projectile* swordSlash = new SwordSlash();
        sf::Vector2f initialPosition = sprites[0].getPosition() + (sf::Vector2f(0, sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y *0.05f));
        sf::Vector2f spellTarget = direction;
        //((Necromancer*)characters[0])->getSprite().getPosition() + 2.0f *
            //sf::Vector2f(48 * (float)windowDimensions.x / 1920.0f, 6 * (float)windowDimensions.y / 1080.0f);
        if (isFacingRight)
        {
            initialPosition = initialPosition + sf::Vector2f(sprites[0].getScale().x * sprites[0].getTextureRect().getSize().x *0.8f, 0);
            ((SwordSlash*) swordSlash)->Load(projectilesTextures[2], initialPosition, spellTarget, windowDimensions,false);
        }
        else
        {
            initialPosition = initialPosition + sf::Vector2f(sprites[0].getScale().x * sprites[0].getTextureRect().getSize().x * 0.15f, 0);
            ((SwordSlash*) swordSlash)->Load(projectilesTextures[2], initialPosition, spellTarget, windowDimensions,true);
        }
        return swordSlash;
    }
	return nullptr;
}

const sf::Sprite& MeleeMage::getSprite(void) const
{
    return sprites.at(0);
}
