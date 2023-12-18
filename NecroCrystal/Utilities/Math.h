#pragma once
#include <SFML/Graphics.hpp>

class Math
{
public:
	static sf::Vector2f convertVector(sf::Vector2i vectorI)
	{
		return sf::Vector2f(vectorI.x, vectorI.y);
	}
	static sf::Vector2f normalizeVector(sf::Vector2f direction);
	static bool SpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2);

};

