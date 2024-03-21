#pragma once
#include <SFML/Graphics.hpp>
#include "../../../Utilities/CameraService.h"
#include "../../Projectile.h"
#include "../../../Utilities/Animation.h"

class ExplosionProj : public Projectile
{
protected:
	float lifeSpan;
	float liveTimer;
public:
	ExplosionProj();

	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime);
	sf::Sprite& getSprite(void);

	bool ShouldBeDestroyed(void) const;
};