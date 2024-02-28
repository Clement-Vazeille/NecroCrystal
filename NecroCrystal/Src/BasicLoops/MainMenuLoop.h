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
	Bouton tutorialButton;
	Bouton quitGameButton;

	Sentence* necroCrystalText;
	
	void ResetButtons(void);
public:
	MainMenuLoop();
	~MainMenuLoop();

	void initialize(sf::Vector2i& windowDimensions, TextManager& textManager);
	int update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition); //0 nothing | 1 quit game | 2 launch game | 3 watch tutorial
	void draw(sf::RenderWindow* window);

};

