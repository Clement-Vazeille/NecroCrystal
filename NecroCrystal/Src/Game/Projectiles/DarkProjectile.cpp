#include "DarkProjectile.h"
#include "../Utilities/Math.h"
#include <iostream>

DarkProjectile::DarkProjectile()
{
	speed = 0.5f;
	faction = 1;
	scale = 2.5f;
	damage = 10;
}

void DarkProjectile::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	sprite.setScale(scale*(float)windowDimensions.x/1920.0f,scale*windowDimensions.y/1080.0f); //make scale a variable
	sf::Vector2f movement = Math::windowNormalizeVector(Math::normalizeVector(direction) * speed * deltaTime, windowDimensions);
	cameraService.MoveSprite(sprite, movement);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());
}


sf::Sprite& DarkProjectile::getSprite(void)
{
	return sprite;
}
