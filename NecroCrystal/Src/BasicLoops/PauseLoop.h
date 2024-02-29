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
	Bouton mainMenuButton;

	Sentence* pauseText;
public:
	PauseLoop();
	~PauseLoop();

	void initialize(sf::Vector2i& windowDimensions, TextManager& textManager);
	int update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition); // 0 nothing | 1 quit game | 2 main menu 
	void draw(sf::RenderWindow* window);

	void ResetButton(void);
};

