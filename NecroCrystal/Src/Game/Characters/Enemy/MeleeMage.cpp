#include "MeleeMage.h"
#include <iostream>
#include "../Necromancer.h"
#include "../../Utilities/Math.h"

void MeleeMage::SelectNewAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters)
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

        int randomIntChoixAction = 31;//nombre choisis entre 0 et 100
        int barreDefMax = 10 + ((maxHealth-health)/maxHealth) * 40; //le melee mage a entre 10 et 45% de chance de se protéger

        float distToNecro = Math::Distance(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition(),windowDimensions);
        float distProche = 200;
        float distMoyen = 100;

        int barreAttMin = 90;
        if (distToNecro < distMoyen)
            barreAttMin = 65;
        if (distToNecro < distProche)
            barreAttMin = 25;

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
            newActionTimer = (int) ((float)newActionCooldown * 0.68f);
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
    loopAnimation.Flip();
}

MeleeMage::MeleeMage() :
    loopAnimation(80, 1, 88, 64),
    newActionCooldown(2500), newActionTimer(2250),
    currentAction(Attaquer), canLaunchAttack(false),
    dashSpeedBoost(2.5f), protectSpeedBoost(0.5f),
    isFacingRight(true)
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
    sprites[0].setScale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));
    sprites[1].setScale(sf::Vector2f(healthBarScaleX * (double)windowDimensions.x / 1920.0, healthBarScaleY * (double)windowDimensions.y / 1080.0));
    if (Math::DistanceLat(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition(), windowDimensions) < activatedDistance)
        activated = true;

    this->SelectNewAction(windowDimensions, deltaTime, map, characters);
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
    }

    cameraService.MoveSprite(sprites[0], movement);
    cameraService.MoveSprite(sprites[1], movement);
    
    loopAnimation.Update(sprites[0], deltaTime);

    hitbox.setScale(sprites[0].getScale());
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());

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
}

Projectile* MeleeMage::LaunchProjectile(float deltaTime, sf::Texture* projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
    if (activated && canLaunchAttack)
    {
        canLaunchAttack = false;
    }
	return nullptr;
}

const sf::Sprite& MeleeMage::getSprite(void) const
{
    return sprites.at(0);
}
