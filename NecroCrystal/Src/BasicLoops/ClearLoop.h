#pragma once
#include <SFML/Graphics.hpp>
#include "../GlobalUtility/TextManager.h"
#include "../GlobalUtility/Sentence.h"
#include "../GlobalUtility/Bouton.h"
class ClearLoop
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	Bouton quitGameButton;

	Sentence* clearText;
	Sentence* timerText;
public:
	ClearLoop();
	~ClearLoop();

	void initialize(sf::Vector2i& windowDimensions, TextManager& textManager);
	void setTimer(std::string timeText, TextManager& textManager);
	int update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition); //0 nothing | 1 quit game | 2 next level
	void draw(sf::RenderWindow* window);
};

