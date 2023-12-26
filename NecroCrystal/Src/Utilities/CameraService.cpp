#include "CameraService.h"

CameraService::CameraService(sf::Vector2f windowSize):
	diff(0),cameraPosition(0), 
	windowSizeChange(sf::Vector2f(0.0f,0.0f))
{
	windowSizeMem = windowSize;
}

void CameraService::MoveSprite(sf::Sprite& sprite, sf::Vector2f& movement) //change for the camera and screen window position
{
	sf::Vector2f position(sprite.getPosition() + sf::Vector2f(0, diff));
	sprite.setPosition(position + movement+sf::Vector2f(windowSizeChange.x*position.x/windowSizeMem.x, windowSizeChange.y * position.y / windowSizeMem.y));
}

void CameraService::SetSprite(sf::Sprite& sprite, sf::Vector2f& position) //only change for the camera
{
	sprite.setPosition(position + sf::Vector2f(0,cameraPosition));
}

void CameraService::Update(float new_diff, sf::Vector2f windowSize)
{
	diff = new_diff;
	cameraPosition += diff;
	windowSizeChange = windowSize - windowSizeMem;
	windowSizeMem = windowSize;
}
