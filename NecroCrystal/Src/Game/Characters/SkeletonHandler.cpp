#include "SkeletonHandler.h"
#include <iostream>
#include "../Utilities/Math.h"

SkeletonHandler::SkeletonHandler() :
	skeletonRange(260.f),
	skeletonDashTimer(0),skeletonDashCooldown(6000)
{
}

SkeletonHandler::~SkeletonHandler()
{
	for (auto& skeleton : skeletons)
	{
		delete skeleton;
	}
}

void SkeletonHandler::Load(void)
{ 
	if (texture.loadFromFile("Assets/Skeleton/SkeletonSpriteSheet.png"))
		std::cout << "Skeleton texture SpriteSheet loaded successfully" << std::endl;
	else
		std::cout << "failed to load Skeleton texture" << std::endl;
}

void SkeletonHandler::SpawnSkeleton(sf::Vector2i& windowDimensions, sf::Vector2f position) //TODO les faire spawn un peu plus loin 
//car sinon ils sont vite hyper stackés , les faires dash on spawn ???
{
	Skeleton* newSkeleton = new Skeleton();
	newSkeleton->Load(windowDimensions,position,texture);
	skeletons.push_back(newSkeleton);
}

void SkeletonHandler::SkeletonAttack(Character* character,VFXHandler& vFXHandler,sf::Vector2i& windowDimensions)
{
	if (character->SetHealth(character->GetHealth()))
		return;
	for (auto& skeleton : skeletons)
	{
		if (skeleton->IsActivated() && Math::Distance(skeleton->getSprite().getPosition() - character->getSprite().getPosition())<skeletonRange)
		{
			skeleton->AttackAnimation();
			sf::Vector2f projStart = skeleton->getSprite().getPosition()+sf::Vector2f(0,skeleton->getSprite().getGlobalBounds().getSize().y*0.4);
			//if skeleton is facing left, projectile face left
			vFXHandler.SpawnVFX(windowDimensions,projStart, 
				character->getSprite().getPosition()+(character->getSprite().getGlobalBounds().getSize()/2.f), 0);
			if (character->SetHealth(character->GetHealth() - skeleton->GetAD()))
				return;
		}
	}
}

void SkeletonHandler::SkeletonDash(sf::Vector2f posititon,float deltaTime)
{
	if (skeletonDashTimer < skeletonDashCooldown)
		skeletonDashTimer += deltaTime;
	if(skeletonDashTimer>skeletonDashCooldown && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		skeletonDashTimer = 0;
		for (auto& skeleton : skeletons)
		{
			if(skeleton->IsActivated())
				skeleton->StartDash(posititon);
		}
	}
}

void SkeletonHandler::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters)
{
	for (auto& skeleton : skeletons)
	{
		skeleton->Update(cameraService, windowDimensions, deltaTime,map,characters);
	}
	this->SkeletonDash(characters.at(0)->getHitbox()->getPosition(), deltaTime);
}

void SkeletonHandler::DrawSkeletons(sf::RenderWindow* window,bool showHitbox) const
{
	for (auto& skeleton : skeletons)
	{
		if (skeleton->IsActivated())
		{
			skeleton->Draw(window);
			if (showHitbox)
				skeleton->DrawHitbox(window);
		}
	}
}
