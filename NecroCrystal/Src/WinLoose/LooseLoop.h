#pragma once
#include <SFML/Graphics.hpp>
#include "../GlobalUtility/TextManager.h"
#include "../GlobalUtility/Sentence.h"
class LooseLoop
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	Sentence* loseText;
public:
	LooseLoop();
	~LooseLoop();

	void initialize(sf::Vector2i& windowDimensions, TextManager& textManager);
	void update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition);
	void draw(sf::RenderWindow* window);
};

