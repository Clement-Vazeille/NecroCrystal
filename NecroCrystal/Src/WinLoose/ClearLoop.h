#pragma once
#include <SFML/Graphics.hpp>
class ClearLoop
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	ClearLoop();
	~ClearLoop();

	void initialize(sf::Vector2i& windowDimensions);
	void update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition);
	void draw(sf::RenderWindow* window);
};

