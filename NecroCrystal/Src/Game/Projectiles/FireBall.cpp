#include "FireBall.h"
#include "../Utilities/Math.h"

FireBall::FireBall()
{
	speed = 0.2f;
	faction = 2;
	scale = 4.5f;
	damage = 10;
}

void FireBall::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	sprite.setScale(scale * (float)windowDimensions.x / 1920.0f, scale * windowDimensions.y / 1080.0f); //make scale a variable
	sf::Vector2f movement = Math::windowNormalizeVector(Math::normalizeVector(direction) * speed * deltaTime,windowDimensions);
	cameraService.MoveSprite(sprite, movement);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());
}

sf::Sprite& FireBall::getSprite(void)
{
	return sprite;
}
