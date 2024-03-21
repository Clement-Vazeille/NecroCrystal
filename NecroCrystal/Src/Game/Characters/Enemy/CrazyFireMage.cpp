#include "CrazyFireMage.h"
#include <iostream>
#include "../Necromancer.h"
#include "../../Utilities/Math.h"
#include "../../Projectiles/IndividualProjectiles/CrazyFireMage/DashFire.h"
#include "../../Projectiles/IndividualProjectiles/CrazyFireMage/Explosion.h"

void CrazyFireMage::SelectNewAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
    newActionTimer += deltaTime;
    if (newActionTimer >= newActionCooldown)
    {
        newActionTimer = 0;

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

        //Les actions possibles
        //Tourniquet: marche plutôt lentement vers le nécromancien avec un tourniquet de feu autour de lui
        //  Plus probable si le necro est proche de lui
        //Dash: Dash (out ou in selon les hp actuels et la distance au necro)
        //  et laisse derrière lui une trainée de feu imobile qui inflige des dégats
        //Explosion: Sort de base, au début de l'action met 3 vfx de préparation d'explosion sous le nécromancien
        //  puis à la fin créer une explosion qui fait bien mal (l'explosion est un cercle qui s'agrandit)
        //Fury: un dash avec une vitesse augmentée, durée réduite,lance 1 explosions
        //  est lancé automatiquement lorsqu'il est à < 10%hp

        int randomIntChoixAction = 51;//randomLSFR.randomUpTo(100);//nombre choisis entre 0 et 100

        float distToNecro = Math::Distance(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition(), windowDimensions);
        float distProche = 200;
        float distMoyen = 650;

        int barreTourMax = 15;
        int barreDashMin = 70;

        if (distToNecro <= distMoyen)
            barreTourMax = 35;
        if (distToNecro <= distMoyen)
            barreTourMax = 50;

        currentAction = Explosion;
        if (randomIntChoixAction < barreTourMax)
            currentAction = Tourniquet;
        if (randomIntChoixAction > barreDashMin)
            currentAction = Dash;

        if (isCrazy)
            currentAction = Fury;

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
            newActionTimer = newActionCooldown - dashTime;
            direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());
        }
        break;
        case Explosion:
        {
            damageMultiplier = 1.f;
            shouldStartExplo = true;
            explosionTarget = sf::Vector2f(characters[0]->getHitbox()->getPosition().x-60*static_cast<float>(windowDimensions.x)/1920.f, 
                characters[0]->getHitbox()->getPosition().y - 28 * static_cast<float>(windowDimensions.x) / 1800.f);

            explosionTimer = 800;
        }
        break;
        case Fury:
        {
            damageMultiplier = 0.6f;
            newActionTimer = newActionCooldown - furyDashTime;
            direction = Math::normalizeVector(characters[0]->getHitbox()->getPosition() - sprites[0].getPosition());

            shouldStartExplo = true;
            explosionTarget = sf::Vector2f(characters[0]->getHitbox()->getPosition().x - 60 * static_cast<float>(windowDimensions.x) / 1920.f,
                characters[0]->getHitbox()->getPosition().y - 28 * static_cast<float>(windowDimensions.x) / 1800.f);

            explosionTimer = 800;
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

void CrazyFireMage::SpawnParticules(void) const
{
}

CrazyFireMage::CrazyFireMage() :
    newActionCooldown(2500), newActionTimer(2500),
    currentAction(Tourniquet),
    isFacingRight(true), isInvincible(false),
    animations({ Animation(120,1,64,64,0,0), Animation(120,1,64,64,1,0) ,Animation(120,1,64,64,2,0) ,Animation(120,1,64,64,3,0) }),
    dashSpeed(0.65f), furySpeed(0.90f),
    dashTime(900), furyDashTime(700),
    isCrazy(false), crazyHealthStart(100),
    invulnerabilityTimer(0), invulnerabilityDuration(2000),
    dashFireTimer(0), dashFireCooldown(120),
    shouldStartExplo(false), explosionTimer(1)
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
    if (isInvincible)
    {
        invulnerabilityTimer += deltaTime;
        if (invulnerabilityTimer > invulnerabilityDuration)
            isInvincible = false;
        this->SpawnParticules();
    }

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
        case Tourniquet:
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
        case Dash:
        {
            movement = Math::windowNormalizeVector(direction * dashSpeed * deltaTime, windowDimensions);
        }
        break;
        case Explosion:
        {
            direction = sf::Vector2f(0, 0);
            movement = sf::Vector2f(0, 0);

            if (shouldStartExplo)
            {
                shouldStartExplo = false;
                vFXHandler.SpawnVFX(windowDimensions, explosionTarget, explosionTarget, 2);
            }
        }
        break;
        case Fury:
        {
            movement = Math::windowNormalizeVector(direction * furySpeed * deltaTime, windowDimensions);

            if (shouldStartExplo)
            {
                shouldStartExplo = false;
                vFXHandler.SpawnVFX(windowDimensions, explosionTarget, explosionTarget, 2);
            }
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
    if (activated)
    {
        switch (currentAction)
        {
        case Tourniquet: {

        }
            break;
        case Dash: {
            dashFireTimer += deltaTime;
            if (dashFireTimer > dashFireCooldown)
            {
                dashFireTimer = 0;
                Projectile* dashFire = new DashFire();
                sf::Vector2f initialPosition = sprites[0].getPosition() + (sf::Vector2f(0, sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y * 0.05f));
                dashFire->Load(projectilesTextures.GetFireBall(), initialPosition, initialPosition, windowDimensions);
                return dashFire;
            }
        }
            break;
        case Explosion: {
            explosionTimer -= deltaTime;
            if (explosionTimer < 0) {
                explosionTimer = 90000;
                Projectile* explosion = new ExplosionProj();
                explosion->Load(projectilesTextures.GetExplosion(), explosionTarget, explosionTarget, windowDimensions);
                return explosion;
            }
        }
            break;
        case Fury: {

            dashFireTimer += deltaTime;
            explosionTimer -= deltaTime;
            if (explosionTimer < 0) {
                explosionTimer = 90000;
                Projectile* explosion = new ExplosionProj();
                explosion->Load(projectilesTextures.GetExplosion(), explosionTarget, explosionTarget, windowDimensions);
                return explosion;
            }

            if (dashFireTimer > dashFireCooldown)
            {
                dashFireTimer = 0;
                Projectile* dashFire = new DashFire();
                sf::Vector2f initialPosition = sprites[0].getPosition() + (sf::Vector2f(0, sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y * 0.05f));
                dashFire->Load(projectilesTextures.GetFireBall(), initialPosition, initialPosition, windowDimensions);
                return dashFire;
            }
        }
            break;
        default:
            break;
        }
    }
	return nullptr;
}

const sf::Sprite& CrazyFireMage::getSprite(void) const
{
    return sprites.at(0);
}

bool CrazyFireMage::TakeDamage(int hp)
{
    if (isInvincible)
    {
        return false;
    }
    bool ans = Enemy::TakeDamage(hp);
    if (health <= crazyHealthStart && !isCrazy)
    {
        isCrazy = true;
        isInvincible = true;
        newActionTimer = newActionCooldown;
    }
    return ans;
}
