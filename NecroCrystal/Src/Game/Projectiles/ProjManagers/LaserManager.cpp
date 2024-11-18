#include "LaserManager.h"

LaserManager::LaserManager() : 
	fxLaunched(false),aliveTime(0),yDrift(0),
	speed(0.8f),lifeTime(2500),
	spawnLaserCD(200),spawnLaserTimer(0)
{
}

void LaserManager::DataUpdate(const float& yCameraDiff, const float& deltaTime)
{
	aliveTime += deltaTime;
	yDrift += yCameraDiff;
	spawnLaserTimer += deltaTime;

}

bool LaserManager::AttackUpdate(sf::Vector2i& windowDimensions,VFXHandler& vFXHandler,float& yLaserPosition)
{
	if(!fxLaunched)
	{
		vFXHandler.SpawnVFX(windowDimensions, sf::Vector2f(windowDimensions.x*0.033,windowDimensions.y*(-0.1f)), sf::Vector2f(windowDimensions.x * 0.033, windowDimensions.y * 1.6f), 3);
		fxLaunched = true;
	}
	yLaserPosition = windowDimensions.y * (-0.1f) + yDrift+aliveTime*speed;

	if (spawnLaserTimer > spawnLaserCD)
	{
		spawnLaserTimer -= spawnLaserCD;
		return true;
	}
	return false;
}

bool LaserManager::ShouldBeDestroyed(void)
{
	return aliveTime>=lifeTime;
}
