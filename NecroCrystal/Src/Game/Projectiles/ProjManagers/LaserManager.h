#pragma once

#include "../../Effects/VFXHandler.h"

class LaserManager
{
private:
	
	bool fxLaunched;
	float yDrift;

	float aliveTime;
	float speed;
public:
	LaserManager();
	~LaserManager();

	void Load();
	void DataUpdate(const float& yCamera, const float& deltaTime);
	void AttackUpdate(sf::Vector2i& windowDimensions,VFXHandler& vFXHandler);
	bool ShouldBeDestroyed(void);
};

