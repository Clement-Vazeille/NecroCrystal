#include "Math.h"

sf::Vector2f Math::convertVector(sf::Vector2i vectorI)
{
	return sf::Vector2f(vectorI.x, vectorI.y);

}

sf::Vector2f Math::normalizeVector(sf::Vector2f direction)
{
	float norm = std::sqrtf((direction.x * direction.x) + (direction.y * direction.y));
	if (norm == 0)
	{
		return(sf::Vector2f(0, 0));
	}
	sf::Vector2f new_direction(direction.x / norm, direction.y / norm);

	return new_direction;
}

float Math::Distance(sf::Vector2f direction)
{
    return std::sqrtf((direction.x * direction.x) + (direction.y * direction.y));
}

float Math::DistanceLat(sf::Vector2f direction)
{
    return std::sqrtf((0.4f*direction.x * direction.x) + (2.5f*direction.y * direction.y));
}

bool Math::SpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2)
{

	return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

sf::Vector2f Math::windowNormalizeVector(sf::Vector2f entryVector, sf::Vector2i& windowDimensions)
{
	return sf::Vector2f(entryVector.x*windowDimensions.x/1920.0f,entryVector.y*windowDimensions.y/1080.0f);
}

void Math::CorrectMovement(sf::Vector2f& change, sf::RectangleShape& hitbox, Map& map)
{
    sf::Vector2f movement_x = sf::Vector2f(change.x, 0.0f);
    sf::Vector2f movement_y = sf::Vector2f(0.0f, change.y);

    hitbox.move(movement_x);
    if (map.ColideWithWall(&hitbox))
    {
        change.x = 0;
    }
    hitbox.move(-movement_x);

    hitbox.move(movement_y);
    if (map.ColideWithWall(&hitbox))
    {
        change.y = 0;
    }
    hitbox.move(-movement_y);
}
