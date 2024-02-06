#pragma once
#include <SFML/Graphics.hpp>
#include "../GlobalUtility/TextManager.h"
#include "../GlobalUtility/Sentence.h"
#include "../GlobalUtility/Bouton.h"

class PauseLoop
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	Bouton quitGameButton;

	Sentence* pauseText;
public:
	PauseLoop();
	~PauseLoop();

	void initialize(sf::Vector2i& windowDimensions, TextManager& textManager);
	bool update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition); // true to quit game
	void draw(sf::RenderWindow* window);
};

