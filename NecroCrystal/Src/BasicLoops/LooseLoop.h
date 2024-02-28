#pragma once
#include <SFML/Graphics.hpp>
#include "../GlobalUtility/TextManager.h"
#include "../GlobalUtility/Sentence.h"
#include "../GlobalUtility/Bouton.h"
class LooseLoop
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	Bouton retryButton;
	Bouton quitGameButton;
	Bouton mainMenuButton;

	Sentence* loseText;
public:
	LooseLoop();
	~LooseLoop();

	void initialize(sf::Vector2i& windowDimensions, TextManager& textManager);
	int update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition); 
	//0 nothing | 1 quit game | 2 retry level | 3 Main menu
	void draw(sf::RenderWindow* window);
};

