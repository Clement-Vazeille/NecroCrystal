#include "Pestimus.h"
#include <iostream>
#include "../Necromancer.h"
#include "../../Utilities/Math.h"

void Pestimus::SelectNewAttackAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
}

void Pestimus::SelectNewMovementAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
}

void Pestimus::Flip(void)
{
	for (auto& animation : animations)
	{
		animation.Flip();
	}
}

Pestimus::Pestimus() :
	animations({ Animation(120,1,64,88,0,0),Animation(120,1,64,88,0,0) ,Animation(120,1,64,88,0,0) ,Animation(120,1,64,88,0,0) ,Animation(120,1,64,88,0,0) }),
	newAttackActionTimer(0), newAttackActionCooldown(1000),
	newMovementActionTimer(0), newMovementActionCooldown(1000),
	direction(sf::Vector2f(0,0)), isFacingRight(true),
	willStartNewPhase(false), phaseNumber(1),
	currentAttack(Circu), currentMovement(Imo)
{
	scale = 2;
	width = 64;
	height = 64;
	speed = 0.25f;
	spriteNumber = 2;  //compte la barre de vie
	sprites.resize(spriteNumber);
	faction = 2;
	maxHealth = 150;
	health = maxHealth;
	activationTime = 600;
}

Pestimus::~Pestimus()
{
}

void Pestimus::Load(sf::Vector2i& windowDimensions, sf::Vector2f position)
{
	std::cout << "test 1" << std::endl;
	if (texture.loadFromFile("Assets/OtherMages/Pestimus/Pestimus.png"))
	{
		sprites.at(0).setTexture(texture);
		std::cout << "test 3" << std::endl;
		animations.at(currentAttack).SetTextureRect(sprites.at(0));
		std::cout << "test 4" << std::endl;
		hitbox.setSize(sprites.at(0).getGlobalBounds().getSize());
		sprites.at(0).scale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));//multiplie la taille par scale (c'est 2)
		sprites.at(0).setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0, position.y * (double)windowDimensions.y / 1080.0));
	}
	else
	{
		std::cout << "Pestimus image failed to load" << std::endl;
	}
	std::cout << "test 2" << std::endl;
	this->LoadHealthBar(windowDimensions, position + sf::Vector2f(20.f, 0));

	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(-1);
	hitbox.setFillColor(sf::Color::Transparent);

	hitbox.setScale(sprites[0].getScale().x * 0.5, sprites[0].getScale().y);
	hitbox.setPosition(sprites[0].getGlobalBounds().getPosition() +
		Math::windowNormalizeVector(sf::Vector2f(sprites[0].getGlobalBounds().width * 0.25, 0), windowDimensions));
}

void Pestimus::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR, VFXHandler& vFXHandler)
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
        this->SelectNewAttackAction(windowDimensions, deltaTime, map, characters, randomLSFR);
		this->SelectNewMovementAction(windowDimensions, deltaTime, map, characters, randomLSFR);
    }
	
    
    if (activated)
    {
		//attacl part
		switch (currentAttack)
		{

        default:
		{
			std::cout << "Unknown attack asked for Knight Captain" << std::endl;
		}
		break;
		}
		//movement part
        switch (currentMovement)
        {
        
        default:
        {
            std::cout << "Unknown movement asked for Knight Captain" << std::endl;
        }
        break;
        }
        Math::CorrectMovement(movement, hitbox, map);

        animations.at(currentAttack).Update(sprites[0], deltaTime);
    }

    cameraService.MoveSprite(sprites[0], movement);
    cameraService.MoveSprite(sprites[1], movement);



    hitbox.setScale(sprites[0].getScale().x * 0.5, sprites[0].getScale().y);
    hitbox.setPosition(sprites[0].getGlobalBounds().getPosition() +
        Math::windowNormalizeVector(sf::Vector2f(sprites[0].getGlobalBounds().width * 0.25, 0), windowDimensions));

}

Projectile* Pestimus::LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
	return nullptr;
}

const sf::Sprite& Pestimus::getSprite(void) const
{
	return sprites.at(0);
}

bool Pestimus::TakeDamage(int hp)
{
	if (willStartNewPhase)
	{
		return false;
	}
	bool ans = Enemy::TakeDamage(hp);
	
	return ans;
	
}
