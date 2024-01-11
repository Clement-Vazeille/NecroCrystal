#pragma once
#include <SFML/Graphics.hpp>
#include "../GlobalUtility/TextManager.h"
#include "../GlobalUtility/Sentence.h"
class ClearLoop
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	Sentence* clearText;
	Sentence* timerText;
public:
	ClearLoop();
	~ClearLoop();

	void initialize(sf::Vector2i& windowDimensions, TextManager& textManager);
	void setTimer(std::string timeText, TextManager& textManager);
	void update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition);
	void draw(sf::RenderWindow* window);
};

