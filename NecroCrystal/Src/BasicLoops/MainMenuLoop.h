#pragma once
#include <SFML/Graphics.hpp>
#include "../GlobalUtility/TextManager.h"
#include "../GlobalUtility/Sentence.h"
#include "../GlobalUtility/Bouton.h"

class MainMenuLoop
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	Bouton startButton;
	Bouton quitGameButton;

	Sentence* necroCrystalText;
public:
	MainMenuLoop();
	~MainMenuLoop();

	void initialize(sf::Vector2i& windowDimensions, TextManager& textManager);
	int update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition); //0 nothing | 1 quit game | 2 launch game
	void draw(sf::RenderWindow* window);

};

