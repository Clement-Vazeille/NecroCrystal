#pragma once
#include <SFML/Graphics.hpp>
#include "../Utilities/CameraService.h"
#include "Projectile.h"

class DarkProjectile : public Projectile
{
private:
	
public:
	DarkProjectile();

	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime);

	sf::Sprite& getSprite(void);
};

