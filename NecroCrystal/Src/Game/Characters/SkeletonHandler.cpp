#include "SkeletonHandler.h"
#include <iostream>
#include "../Utilities/Math.h"
#include "../Characters/Necromancer.h"

SkeletonHandler::SkeletonHandler() :
	skeletonRange(260.f),isRightClickClicked(false)
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
//car sinon ils sont vite hyper stack�s , les faires dash on spawn ???
{
	Skeleton* newSkeleton = new Skeleton();
	newSkeleton->Load(windowDimensions,position,texture);
	skeletons.push_back(newSkeleton);
}

void SkeletonHandler::SkeletonAttack(Character* character,VFXHandler& vFXHandler,sf::Vector2i& windowDimensions)
{
	if (character->TakeDamage(0))
		return;
	for (auto& skeleton : skeletons)
	{
		if (skeleton->IsActivated() && Math::Distance(skeleton->getSprite().getPosition() - character->getSprite().getPosition(),windowDimensions)<skeletonRange)
		{
			skeleton->AttackAnimation(character->getSprite().getGlobalBounds().getPosition());
			sf::Vector2f projStart = skeleton->getSprite().getPosition()+sf::Vector2f(0,skeleton->getSprite().getGlobalBounds().getSize().y*0.4);
			//if skeleton is facing left, projectile face left
			vFXHandler.SpawnVFX(windowDimensions,projStart, 
				character->getSprite().getPosition()+(character->getSprite().getGlobalBounds().getSize()/2.f), 0);
			if (character->TakeDamage(skeleton->GetAD()))
				return;
		}
	}
}

void SkeletonHandler::SkeletonDash(sf::Vector2f posititon,float deltaTime)
{
	
	if(!isRightClickClicked && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		isRightClickClicked = true;
		for (auto& skeleton : skeletons)
		{
			if(skeleton->IsActivated())
				skeleton->StartDash(posititon);
		}
	}
	if (isRightClickClicked && !sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		isRightClickClicked = false;
	}
}

void SkeletonHandler::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, 
	RandomLSFR& randomLSFR,  VFXHandler& vFXHandler)
{
	for (auto& skeleton : skeletons)
	{
		skeleton->Update(cameraService, windowDimensions, deltaTime,map,characters,randomLSFR,vFXHandler);
		sf::Vector2f dashKillPosition = skeleton->HasDashKilledSomething();
		if (dashKillPosition.x != 0 && dashKillPosition.y != 0)
		{
			this->SpawnSkeleton(windowDimensions, dashKillPosition);
		}
	}

	if(!((Necromancer*) characters.at(0))->isInNecroZone())
		this->SkeletonDash(characters.at(0)->getHitbox()->getPosition(), deltaTime);

}

void SkeletonHandler::DrawSkeletons(sf::RenderWindow* window,bool showHitbox) const
{
	for (auto& skeleton : skeletons)
	{
		if (skeleton->IsDrawn())
		{
			skeleton->Draw(window);
			if (showHitbox)
				skeleton->DrawHitbox(window);
		}
	}
}
