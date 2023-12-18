#pragma once
#include <SFML/Graphics.hpp>

class DarkProjectile
{
public:
	sf::Sprite sprite;
public:
	void Initialize();
	void Load(sf::Texture& texture);
	void Update();
	void Draw(sf::RenderWindow& window);
};

