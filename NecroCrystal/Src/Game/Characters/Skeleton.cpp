#include "Skeleton.h"
#include <iostream>
#include "../Utilities/Math.h"

Skeleton::Skeleton() :
    faceRight(true), moving(false), stopDistance(15.f),
    activated(false), activatedTimer(0), activationTime(1000),
    aD(35), dashAD(15), damageDealt(0), skeletonLevel(0),
    attackTimer(0), attackDuration(400), spawnAnimationDuration(500),
    skeletonAnimations({ Animation(120,3,64,64,0,0),Animation(attackDuration/3.f,3,64,64,3,0),Animation(120,3,64,64,6,0),Animation(spawnAnimationDuration/5.f,5,64,64,9,0) }),
    spearAnimations({ Animation(120,3,64,64,0,1),Animation(attackDuration / 3.f,3,64,64,3,1),Animation(120,3,64,64,6,1),Animation(spawnAnimationDuration / 5.f,5,64,64,9,1) }),
    armorAnimations({ Animation(120,3,64,64,0,2),Animation(attackDuration / 3.f,3,64,64,3,2),Animation(120,3,64,64,6,2),Animation(spawnAnimationDuration / 5.f,5,64,64,9,2) }),
    currentAnimation(0), goldDamageRequirement(55)

{
    scale = 2;
    width = 64;
    height = 64;
    speed = 1.35f;
    spriteNumber = 3;
    sprites.resize(spriteNumber);
    faction = -1;  //TODO -1 = inciblable même si c'est pas un problème pour le moment car les frérots sont jamais check dans les colisions (pas dans characters)
    health = 1;
    maxHealth = 1;
}

Skeleton::~Skeleton()
{
}

void Skeleton::Load(sf::Vector2i& windowDimensions, sf::Vector2f position)
{
    //Shouldn't be used, here because Skeleton is inherited from character  ^^
}

void Skeleton::Load(sf::Vector2i& windowDimensions, sf::Vector2f position, sf::Texture& textureLoaded)
{
    for (int i = 0; i < spriteNumber; i++)
    {
        sprites[i].setTexture(textureLoaded);
    }

    //sprites[0].setTextureRect(sf::IntRect(0, 0, width, height));
    skeletonAnimations.at(currentAnimation).SetTextureRect(sprites[0]);
    spearAnimations.at(currentAnimation).SetTextureRect(sprites[1]);
    armorAnimations.at(currentAnimation).SetTextureRect(sprites[2]);

    hitbox.setSize(sprites[0].getGlobalBounds().getSize());

    for(int i=0;i<spriteNumber;i++)
    {
        sprites[i].scale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
        sprites[i].setPosition(position);
    }

    target = sprites[0].getPosition();

    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(-1);
    hitbox.setFillColor(sf::Color::Transparent);

    hitbox.setScale(sprites[0].getScale());
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());
}

void Skeleton::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters)
{
    for (int i = 0; i < spriteNumber; i++)
    {
        sprites[i].setScale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
    }

    if (currentAnimation == 1)
    {
        attackTimer += deltaTime;
        if (attackTimer >= attackDuration)
        {
            currentAnimation = 0;
        }
    }

    skeletonAnimations.at(currentAnimation).Update(sprites[0], deltaTime);
    spearAnimations.at(currentAnimation).Update(sprites[1], deltaTime);
    armorAnimations.at(currentAnimation).Update(sprites[2], deltaTime);

    hitbox.setScale(sprites[0].getScale());

    cameraService.UpdateVector(target);
    sf::Vector2f movement = sf::Vector2f(0, 0);
    if (moving)
    {
        movement = Math::normalizeVector(target - sprites[0].getPosition()) * speed * deltaTime;
        Math::CorrectMovement(movement, hitbox, map);

        if (Math::Distance(target - sprites[0].getPosition(),windowDimensions) < stopDistance)
        {
            moving = false;
            currentAnimation = 0;
        }
    }

    for (int i = 0; i < spriteNumber; i++)
    {
        cameraService.MoveSprite(sprites[i], movement);
    }
    //hitbox.setPosition(sprites[0].getGlobalBounds().getPosition());
    hitbox.setPosition(sprites[0].getPosition());

    //------------------------------------Check collisions with enemies--------------------------------------------
    if(moving)
    {
        for (auto itChar = std::begin(characters)+1; itChar != std::end(characters); itChar++)
        {
            if (hitbox.getGlobalBounds().intersects((*itChar)->getHitbox()->getGlobalBounds()) && enemyDashed.count(((Enemy*)(*itChar))->GetSerial())==0
                && 1 != (*itChar)->getFaction())
            {
                enemyDashed.insert(((Enemy*)(*itChar))->GetSerial());
                this->DealDamage(dashAD);
                if ((*itChar)->TakeDamage(dashAD)) //activate if character is dead
                {
                    delete(*itChar);
                    characters.erase(itChar);
                    itChar--;
                }
            }
        }
    }
    //------------------------------------Check collisions with enemies--------------------------------------------
    

    if (!activated)
    {
        activatedTimer += deltaTime;
        
        if (activatedTimer > activationTime)
        {
            activated = true;
            currentAnimation = 0;
        }
        else if (activatedTimer > activationTime - spawnAnimationDuration)
            currentAnimation = 3;
    }
}

Projectile* Skeleton::LaunchProjectile(float deltaTime, sf::Texture* projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
	return nullptr;
}

void Skeleton::DealDamage(int hitDammage)
{
    damageDealt += hitDammage;
    if (skeletonLevel == 0 && damageDealt >= goldDamageRequirement)
    {
        skeletonLevel++;
        for (auto& animation : spearAnimations)
        {
            animation.MoveOffsets(0, 2);
        }
        for (auto& animation : armorAnimations)
        {
            animation.MoveOffsets(0, 2);
        }
        aD += 25;
        dashAD += 10;
    }
}

void Skeleton::AttackAnimation(sf::Vector2f enemy)
{
    this->DealDamage(aD);
    currentAnimation = 1;
    attackTimer = 0;
    if (enemy.x < sprites[0].getPosition().x && faceRight) 
    {
        this->FlipSkeleton();
        faceRight = !faceRight;
    }
    if (enemy.x > sprites[0].getPosition().x && !faceRight)
    {
        this->FlipSkeleton();
        faceRight = !faceRight;
    }
}

void Skeleton::StartDash(sf::Vector2f necroPosition)
{
    target = necroPosition + (necroPosition - sprites[0].getPosition());
    moving = true;
    currentAnimation = 2;
    enemyDashed.clear();
    if (target.x < sprites[0].getPosition().x && faceRight)
    {
        this->FlipSkeleton();
        faceRight = !faceRight;
    }
    if (target.x > sprites[0].getPosition().x && !faceRight)
    {
        this->FlipSkeleton();
        faceRight = !faceRight;
    }
}

const sf::Sprite& Skeleton::getSprite(void) const
{
    return sprites[0];
}

bool Skeleton::TakeDamage(int hp)
{
	return false;
}

bool Skeleton::IsActivated(void) const
{
    return activated;
}

bool Skeleton::IsDrawn(void) const
{
    return this->IsActivated() || currentAnimation == 3;
}

const float Skeleton::GetAD(void) const
{
    return aD;
}

void Skeleton::FlipSkeleton(void)
{
    for (auto& animation : skeletonAnimations)
    {
        animation.Flip();
    }
    for (auto& animation : spearAnimations)
    {
        animation.Flip();
    }
    for (auto& animation : armorAnimations)
    {
        animation.Flip();
    }
}