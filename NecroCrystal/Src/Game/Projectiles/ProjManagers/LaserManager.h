#pragma once

#include "../../Effects/VFXHandler.h"

class LaserManager
{
private:
	
	bool fxLaunched;
	float yDrift;

	float aliveTime;
	float lifeTime;

	float spawnLaserCD;
	float spawnLaserTimer;

	float speed;
public:
	LaserManager();

	void DataUpdate(const float& yCamera, const float& deltaTime);
	bool AttackUpdate(sf::Vector2i& windowDimensions,VFXHandler& vFXHandler,float& yLaserPosition); //Return true if a laser should be shot
	bool ShouldBeDestroyed(void);
};

