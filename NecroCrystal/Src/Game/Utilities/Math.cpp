#include "Math.h"

sf::Vector2f Math::convertVector(sf::Vector2i vectorI)
{
	return sf::Vector2f(vectorI.x, vectorI.y);

}

sf::Vector2f Math::normalizeVector(sf::Vector2f direction)
{
	int norm = std::sqrtf((direction.x * direction.x) + (direction.y * direction.y));
	if (norm == 0)
	{
		return(sf::Vector2f(0, 0));
	}
	sf::Vector2f new_direction(direction.x / norm, direction.y / norm);

	return new_direction;
}

bool Math::SpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2)
{

	return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

sf::Vector2f Math::windowNormalizeVector(sf::Vector2f entryVector, sf::Vector2i& windowDimensions)
{
	return sf::Vector2f(entryVector.x*windowDimensions.x/1920.0f,entryVector.y*windowDimensions.y/1080.0f);
}
