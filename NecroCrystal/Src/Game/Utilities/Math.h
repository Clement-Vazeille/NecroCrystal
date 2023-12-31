#pragma once
#include <SFML/Graphics.hpp>

class Math
{
public:
	static sf::Vector2f convertVector(sf::Vector2i vectorI);
	static sf::Vector2f normalizeVector(sf::Vector2f direction);
	static bool SpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2);
	static sf::Vector2f windowNormalizeVector(sf::Vector2f direction, sf::Vector2i& windowDimensions);

};

