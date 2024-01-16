#include "SkeletonHandler.h"
#include <iostream>
#include "../Utilities/Math.h"

SkeletonHandler::SkeletonHandler() :
	skeletonRange(0.f)
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
}

void SkeletonHandler::SkeletonDash(sf::Vector2f posititon)
{
}

void SkeletonHandler::UpdateSkeletons(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters)
{
	for (auto skeleton : skeletons)
	{
		skeleton->Update(cameraService, windowDimensions, deltaTime,map,characters);
	}
}

void SkeletonHandler::DrawSkeletons(sf::RenderWindow* window) const
{
	for (auto skeleton : skeletons)
	{
		if(skeleton->IsActivated())
			skeleton->Draw(window);
	}
}
