#pragma once
#include <SFML/Graphics.hpp>

class Math
{
public:
	static sf::Vector2f convertVector(sf::Vector2i vectorI);
	static sf::Vector2f normalizeVector(sf::Vector2f direction);

};

