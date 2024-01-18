#include "SkeletonHandler.h"
#include <iostream>
#include "../Utilities/Math.h"

SkeletonHandler::SkeletonHandler() :
	skeletonRange(180.f),
	skeletonDashTimer(0),skeletonDashCooldown(6000)
{
}

SkeletonHandler::~SkeletonHandler()
{
	for (auto skeleton : skeletons)
	{
		delete skeleton;
	}
}

void SkeletonHandler::Load(void)
{
	if (!texture.loadFromFile("Assets/Skeleton/Skeleton.png"))
		std::cout << "failed to load Skeleton texture";
}

void SkeletonHandler::SpawnSkeleton(sf::Vector2i& windowDimensions, sf::Vector2f position)
{
	Skeleton* newSkeleton = new Skeleton();
	newSkeleton->Load(windowDimensions,position,texture);
	skeletons.push_back(newSkeleton);
}

void SkeletonHandler::SkeletonAttack(Character* character)
{
	if (character->SetHealth(character->GetHealth()))
		return;
	for (auto skeleton : skeletons)
	{
		if (skeleton->IsActivated() && Math::Distance(skeleton->getSprite().getPosition() - character->getSprite().getPosition())<skeletonRange)
		{
			skeleton->AttackAnimation();
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
		for (auto skeleton : skeletons)
		{
			if(skeleton->IsActivated())
				skeleton->StartDash(posititon);
		}
	}
}

void SkeletonHandler::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters)
{
	for (auto skeleton : skeletons)
	{
		skeleton->Update(cameraService, windowDimensions, deltaTime,map,characters);
	}
	this->SkeletonDash(characters.at(0)->getHitbox()->getPosition(), deltaTime);
}

void SkeletonHandler::DrawSkeletons(sf::RenderWindow* window,bool showHitbox) const
{
	for (auto skeleton : skeletons)
	{
		if (skeleton->IsActivated())
		{
			skeleton->Draw(window);
			if (showHitbox)
				skeleton->DrawHitbox(window);
		}
	}
}
