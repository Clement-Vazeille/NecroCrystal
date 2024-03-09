#pragma once

#include <SFML/Graphics.hpp>
#include "../../Utilities/CameraService.h"
#include "../Projectile.h"

class FireBall : public Projectile
{
public:
	FireBall();

	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime);
	sf::Sprite& getSprite(void);
};

