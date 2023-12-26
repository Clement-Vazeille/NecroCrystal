#include "DarkProjectile.h"
#include "../Utilities/Math.h"
#include <iostream>

DarkProjectile::DarkProjectile()
{
	speed = 0.5f;
	faction = 1;
}

void DarkProjectile::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	sprite.setScale(2.5f*(float)windowDimensions.x/1920.0f,2.5f*windowDimensions.y/1080.0f); //make scale a variable
	sf::Vector2f movement = Math::normalizeVector(direction) * speed * deltaTime *(float)windowDimensions.x/1920.0f;
	cameraService.MoveSprite(sprite, movement);
}


sf::Sprite& DarkProjectile::getSprite(void)
{
	return sprite;
}
