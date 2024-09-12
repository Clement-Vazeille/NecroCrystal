#include "LaserManager.h"

LaserManager::LaserManager() : 
	fxLaunched(false),aliveTime(0),yDrift(0),
	speed(0.8f)
{
}

LaserManager::~LaserManager()
{
}

void LaserManager::Load()
{
}

void LaserManager::DataUpdate(const float& yCameraDiff, const float& deltaTime)
{
	aliveTime += deltaTime;
	yDrift += yCameraDiff;

}

void LaserManager::AttackUpdate(sf::Vector2i& windowDimensions,VFXHandler& vFXHandler)
{
	if(!fxLaunched)
	{
		vFXHandler.SpawnVFX(windowDimensions, sf::Vector2f(windowDimensions.x*0.033,windowDimensions.y*(-0.1f)), sf::Vector2f(windowDimensions.x * 0.033, windowDimensions.y * 1.6f), 3);
		fxLaunched = true;
	}
	vFXHandler.SpawnVFX(windowDimensions, sf::Vector2f(windowDimensions.x * 0.033, windowDimensions.y * (-0.1f)+yDrift+aliveTime*speed), sf::Vector2f(windowDimensions.x * 0.033, windowDimensions.y * 1.6f), 2);
}

bool LaserManager::ShouldBeDestroyed(void)
{
	return false;
}
