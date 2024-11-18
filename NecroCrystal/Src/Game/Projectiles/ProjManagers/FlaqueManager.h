#pragma once

#include "../../Effects/VFXHandler.h"

class FlaqueManager
{
private:

	bool fxLaunched;
	bool spawnFxLaunched;

	float yDrift;
	float xPlacement;
	float yPlacement;
	float yCameraPosition;

	float aliveTime;
	float spawnTime;
	float lifeTime;

	float spawnAttackCD;
	float spawnAttackTimer;

public:
	FlaqueManager();

	void Load(float xPlacement,float yPlacement,float yCameraPosition);
	void DataUpdate(const float& yCamera, const float& deltaTime);
	bool AttackUpdate(sf::Vector2i& windowDimensions, VFXHandler& vFXHandler, 
		float& yFlaquePosition, float& xFlaquePosition); //Return true if a laser should be shot
	bool ShouldBeDestroyed(void);
};
