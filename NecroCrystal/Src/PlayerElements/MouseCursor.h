#pragma once
#include <SFML/Graphics.hpp>
class MouseCursor
{
protected:

	float scale;

	sf::Texture texture;
	sf::Sprite sprite;

public:
	MouseCursor();
	~MouseCursor();

	void Load(sf::Vector2i& windowDimensions);
	void Update(sf::Vector2f position, sf::Vector2i& windowDimensions);
	void Draw(sf::RenderWindow* window) const;
};

