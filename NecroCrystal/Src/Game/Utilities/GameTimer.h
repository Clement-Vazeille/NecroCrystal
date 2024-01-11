#pragma once
#include "../../GlobalUtility/TextManager.h"
#include "../../GlobalUtility/Sentence.h"

class GameTimer
{
protected:
	Sentence* timerText;
public:
	GameTimer();

	void Initialize(TextManager& textManager);
	void Update(sf::Vector2i& windowDimensions, std::string string);
	void Draw(sf::RenderWindow* window);
};

