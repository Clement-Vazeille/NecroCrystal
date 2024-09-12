#include "CameraService.h"

CameraService::CameraService(sf::Vector2i windowSize):
	diff(0),cameraPosition(0), 
	windowSizeChangeRatio(sf::Vector2f(0.0f,0.0f))
{
	windowSizeMem = sf::Vector2f(windowSize);
}

void CameraService::MoveSprite(sf::Sprite& sprite, sf::Vector2f& movement) //change for the camera and screen window position
{
	sf::Vector2f position(sprite.getPosition() + sf::Vector2f(0, diff) + movement);
	sprite.setPosition(position.x*windowSizeChangeRatio.x, position.y * windowSizeChangeRatio.y);
}

void CameraService::SetSprite(sf::Sprite& sprite, sf::Vector2f& position) //only change for the camera
{
	sprite.setPosition(position + sf::Vector2f(0,cameraPosition));
}

void CameraService::SetRectangle(sf::RectangleShape& rect, sf::Vector2f& position)
{
	rect.setPosition(position + sf::Vector2f(0, cameraPosition));
}

sf::Vector2f CameraService::SetVector(sf::Vector2f vector)
{
	return vector = vector + sf::Vector2f(0, cameraPosition);
}

void CameraService::UpdateVector(sf::Vector2f& vect)
{
	vect.y = vect.y + diff;
}

float CameraService::GetDiff(void)
{
	return diff;
}

void CameraService::Update(float new_diff, sf::Vector2f windowSize)
{
	diff = new_diff;
	cameraPosition += diff;
	windowSizeChangeRatio.x = windowSize.x / windowSizeMem.x;
	windowSizeChangeRatio.y = windowSize.y / windowSizeMem.y;
	windowSizeMem = windowSize;
}
