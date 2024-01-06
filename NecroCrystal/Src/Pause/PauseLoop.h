#pragma once
#include <SFML/Graphics.hpp>

class PauseLoop
{
protected:
	PauseLoop();
	~PauseLoop();

	void initialize(sf::Vector2i& windowDimensions);
	void update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition);
	void draw(sf::RenderWindow* window);
};

