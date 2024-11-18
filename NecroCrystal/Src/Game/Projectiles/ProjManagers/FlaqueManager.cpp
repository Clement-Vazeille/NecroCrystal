#include "FlaqueManager.h"

FlaqueManager::FlaqueManager() :
	fxLaunched(false),spawnFxLaunched(false), 
	aliveTime(0), yDrift(0),
	lifeTime(15000),xPlacement(0.3f),yPlacement(0.5f),
	spawnAttackCD(200), spawnAttackTimer(0),yCameraPosition(0),
	spawnTime(1000)
{
}

void FlaqueManager::Load(float xPlacementD,float yPlacementD,float yCameraPositionD)
{
	xPlacement = xPlacementD;
	yPlacement = yPlacementD;
	yCameraPosition = yCameraPositionD;
}

void FlaqueManager::DataUpdate(const float& yCameraDiff, const float& deltaTime)
{
	aliveTime += deltaTime;
	yDrift += yCameraDiff;
	if(aliveTime>=spawnTime)
		spawnAttackTimer += deltaTime;
}

bool FlaqueManager::AttackUpdate(sf::Vector2i& windowDimensions, VFXHandler& vFXHandler, 
	float& yLaserPosition,float& xFlaquePosition)
{
	if (!spawnFxLaunched)
	{
		vFXHandler.SpawnVFX(windowDimensions, sf::Vector2f(windowDimensions.x * xPlacement, windowDimensions.y * yPlacement + yCameraPosition), sf::Vector2f(windowDimensions.x * 0.033, windowDimensions.y * 1.6f), 5);
		spawnFxLaunched = true;
	}
	if (!fxLaunched&&aliveTime>=spawnTime)
	{
		vFXHandler.SpawnVFX(windowDimensions, sf::Vector2f(windowDimensions.x * xPlacement, windowDimensions.y * yPlacement + yCameraPosition+yDrift), sf::Vector2f(windowDimensions.x * 0.033, windowDimensions.y * 1.6f), 4);
		fxLaunched = true;
	}
	yLaserPosition = windowDimensions.y * yPlacement + yCameraPosition + yDrift;
	xFlaquePosition = windowDimensions.x * xPlacement;

	if (spawnAttackTimer > spawnAttackCD)
	{
		spawnAttackTimer -= spawnAttackCD;
		return true;
	}
	return false;
}

bool FlaqueManager::ShouldBeDestroyed(void)
{
	return aliveTime >= lifeTime;
}
