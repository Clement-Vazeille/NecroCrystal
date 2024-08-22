#include "Pestimus.h"
#include <iostream>
#include "../Necromancer.h"
#include "../../Utilities/Math.h"
#include "../../Projectiles/IndividualProjectiles/Pestimus/PoisonDot.h"

void Pestimus::SelectNewAttackAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
    newAttackTimer += deltaTime;
    if (newAttackTimer >= newAttackCooldown)
    {
        newAttackTimer = 0;

        currentAttack = Circu;// Pestimus::AttackAction(randomLSFR.randomUpTo(3));//choisit aleatoirement de faire une action parmis les 4 possibles
        if (willStartNewPhase)
        {
            willStartNewPhase = false;
            currentAttack = PhaseSwitchAttack;
        }
        switch (currentAttack)
        {
        case Laser:
        {
            damageMultiplier = 1.f;
            newAttackTimer = 0;
        }
        break;
        case Bulles:
        {
            damageMultiplier = 1.f;
            newAttackTimer = 0;
        }
        break;
        case Circu:
        {
            damageMultiplier = 1.f;
            newAttackTimer = 0;
        }
        break;
        case Flaques:
        {
            damageMultiplier = 1.f;
            newAttackTimer = 0;
        }
        break;
        case PhaseSwitchAttack:
        {
            damageMultiplier = 0.f;
            newAttackTimer = newAttackCooldown-phaseSwitchDuration;
        }
        break;
        default:
        {
            std::cout << "Unknown movement asked for Pestimus" << std::endl;
        }
        break;
        }
    }
}

void Pestimus::SelectNewMovementAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
    newMovementTimer += deltaTime;
    if (newMovementTimer >= newMovementCooldown)
    {
        newMovementTimer = 0;

        movementYSwitch = randomLSFR.randomUpTo(1);
        movementXSwitch = randomLSFR.randomUpTo(1);
        currentMovement = Pestimus::MovementAction(randomLSFR.randomUpTo(3));//choisit aleatoirement de faire une action parmis les 4 possibles
        if (willStartNewPhase)
        {
            willStartNewPhase = false;
            currentMovement = PhaseSwitchMovement;
        }
        switch (currentMovement)
        {
        case Avance:
        {
            newMovementTimer =0;

            circuInitialPosition = sprites[0].getPosition() +
                (sf::Vector2f(sprites[0].getScale().x * sprites[0].getGlobalBounds().getSize().x * 0.22f, sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y * 0.4f));
            sf::Vector2f necroPosition = characters.at(0)->getHitbox()->getPosition() +
                sf::Vector2f(0, characters.at(0)->getHitbox()->getGlobalBounds().height * 0.5f);
            sf::Vector2f trajectory = (necroPosition - circuInitialPosition);

            circuTarget = circuInitialPosition + trajectory;
            circuTargetDrift = sf::Vector2f(trajectory.y, -trajectory.x);
        }
        break;
        case Recule:
        {
            newMovementTimer = 0;

            circuInitialPosition = sprites[0].getPosition() +
                (sf::Vector2f(sprites[0].getScale().x * sprites[0].getGlobalBounds().getSize().x * 0.22f, sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y * 0.4f));
            sf::Vector2f necroPosition = characters.at(0)->getHitbox()->getPosition() +
                sf::Vector2f(0, characters.at(0)->getHitbox()->getGlobalBounds().height * 0.5f);
            sf::Vector2f trajectory = (circuInitialPosition - necroPosition);

            circuTarget = circuInitialPosition + trajectory;
            circuTargetDrift = sf::Vector2f(trajectory.y, -trajectory.x);
        }
        break;
        case FuiteCircu:
        {
            newMovementTimer = 0;
        }
        break;
        case Imo:
        {
            newMovementTimer = 0;
        }
        break;
        case PhaseSwitchMovement:
        {
            newMovementTimer = newMovementCooldown-phaseSwitchDuration;
        }
        break;
        default:
        {
            std::cout << "Unknown movement asked for Pestimus" << std::endl;
        }
        break;
        }
    }
}

void Pestimus::Flip(void)
{
	for (auto& animation : animations)
	{
		animation.Flip();
	}
}

Pestimus::Pestimus() :
	animations({ Animation(120,1,64,88,0,0),Animation(120,1,64,88,1,0) ,Animation(120,1,64,88,2,0) ,
		Animation(120,1,64,88,3,0) ,Animation(120,1,64,88,4,0) }),
	newAttackTimer(1000), newAttackCooldown(1000),
	newMovementTimer(2200), newMovementCooldown(2200),
    phaseSwitchDuration(5000),
	direction(sf::Vector2f(0,0)), isFacingRight(true),
	willStartNewPhase(false), phaseNumber(1),
	currentAttack(Circu), currentMovement(Imo),
    poisonDotThrowTimer(0),poisonDotThrowCooldown(400),
    isLastPoisonDotSwitched(true),
    movementYSwitch(false),movementXSwitch(false)
{
	scale = 2;
	width = 64;
	height = 64;
	speed = 0.35f;
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
	if (texture.loadFromFile("Assets/OtherMages/Pestimus/Pestimus.png"))
	{
		sprites.at(0).setTexture(texture);
		animations.at(currentAttack).SetTextureRect(sprites.at(0));
		hitbox.setSize(sprites.at(0).getGlobalBounds().getSize());
		sprites.at(0).scale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));//multiplie la taille par scale (c'est 2)
		sprites.at(0).setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0, position.y * (double)windowDimensions.y / 1080.0));
	}
	else
	{
		std::cout << "Pestimus image failed to load" << std::endl;
	}
	this->LoadHealthBar(windowDimensions, position);

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
		//attack part
		switch (currentAttack)
		{
        case Laser:
        {
            
        }
        break;
        case Bulles:
        {
            
        }
        break;
        case Circu:
        {
            
        }
        break;
        case Flaques:
        {
            
        }
        break;
        case PhaseSwitchAttack:
        {
            
        }
        break;
        default:
		{
			std::cout << "Unknown attack asked for Pestimus" << std::endl;
		}
		break;
		}

		//movement part
        switch (currentMovement)
        {
        case Avance:
        {
            float ySwitcher = 1;
            if (movementYSwitch)
                ySwitcher *= -1;

            sf::Vector2f currentTarget = circuTarget- (circuTargetDrift * 2.6f * ySwitcher * cos(newMovementTimer * speed * 5.5f / Math::Distance(circuTarget - circuInitialPosition, windowDimensions)));
            direction = Math::normalizeVector(currentTarget - circuInitialPosition);
            movement = Math::windowNormalizeVector(direction * speed * deltaTime, windowDimensions);
        }
        break;
        case Recule:
        {
            float ySwitcher = 1;
            if (movementYSwitch)
                ySwitcher *= -1;

            sf::Vector2f currentTarget = circuTarget - (circuTargetDrift * 2.6f * ySwitcher * cos(newMovementTimer * speed * 4.f / Math::Distance(circuTarget - circuInitialPosition, windowDimensions)));
            direction = Math::normalizeVector(currentTarget - circuInitialPosition);
            movement = Math::windowNormalizeVector(direction * speed * deltaTime, windowDimensions);
        }
        break;
        case FuiteCircu:
        {
            //sf::Vector2f currentTarget = circuTarget - (circuTargetDrift * 2.6f * cos(newMovementTimer * speed * 20.5f / Math::Distance(circuTarget - circuInitialPosition, windowDimensions)));
            //direction = Math::normalizeVector(currentTarget - circuInitialPosition);
            float xSwitcher = 1;
            float ySwitcher = 1;
            if(movementYSwitch)
                ySwitcher*=-1;
            if (movementXSwitch)
                xSwitcher *= -1;
            direction = Math::normalizeVector(sf::Vector2f(cos(newMovementTimer * 0.003)*xSwitcher, sin(newMovementTimer * 0.003)*ySwitcher));

            movement = Math::windowNormalizeVector(direction * speed * deltaTime, windowDimensions);
        }
        break;
        case Imo:
        {
            direction = sf::Vector2f(0, 0);
            movement = Math::windowNormalizeVector(direction * speed * deltaTime, windowDimensions);
        }
        break;
        case PhaseSwitchMovement:
        {
            direction = sf::Vector2f(0, 0);
            movement = Math::windowNormalizeVector(direction * speed * deltaTime, windowDimensions);
        }
        break;
        default:
        {
            std::cout << "Unknown movement asked for Pestimus" << std::endl;
        }
        break;
        }
        Math::CorrectMovement(movement, hitbox, map);

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
    switch (currentAttack)
    {
    case Circu:
    {
        poisonDotThrowTimer += deltaTime;
        if (poisonDotThrowTimer >= poisonDotThrowCooldown)
        {
            poisonDotThrowTimer -= poisonDotThrowCooldown;
            PoisonDot* poisonDot = new PoisonDot();
            sf::Vector2f initialPosition = sprites[0].getPosition() + 
                (sf::Vector2f(sprites[0].getScale().x * sprites[0].getGlobalBounds().getSize().x * 0.22f, sprites[0].getScale().y * sprites[0].getTextureRect().getSize().y * 0.4f));
            sf::Vector2f target=characters.at(0)->getHitbox()->getPosition() + 
                sf::Vector2f(0, characters.at(0)->getHitbox()->getGlobalBounds().height*0.5f);

            poisonDot->Load(projectilesTextures.GetPoisonDot(), initialPosition, target, windowDimensions);
            if (!isLastPoisonDotSwitched)
                poisonDot->InverseTrajectory();
            isLastPoisonDotSwitched = !isLastPoisonDotSwitched;
            return poisonDot;
        }
    }
    break;
    default:
    {
        //return nullptr;
    }
    break;
    }
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
	if (ans && phaseNumber < 3)
	{
        willStartNewPhase = true;
		phaseNumber++;
		health += maxHealth;
		return false;
	}
	return ans;
	
}

int Pestimus::GiveWaveInstruction(void) const
{
	return phaseNumber;
}
