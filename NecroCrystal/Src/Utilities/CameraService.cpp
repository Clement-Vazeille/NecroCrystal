#include "CameraService.h"

CameraService::CameraService():
	diff(0),cameraPosition(0)
{
}

void CameraService::MoveSprite(sf::Sprite& sprite, sf::Vector2f& movement)
{
	sprite.setPosition(sprite.getPosition() + movement + sf::Vector2f(0, diff));
}

void CameraService::SetSprite(sf::Sprite& sprite, sf::Vector2f& position)
{
	sprite.setPosition(position + sf::Vector2f(0,cameraPosition));
}

void CameraService::Update(float new_diff)
{
	diff = new_diff;
	cameraPosition += diff;
}
