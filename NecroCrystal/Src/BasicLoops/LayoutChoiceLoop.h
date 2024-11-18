#pragma once

#include <SFML/Graphics.hpp>
#include "../GlobalUtility/TextManager.h"
#include "../GlobalUtility/Sentence.h"
#include "../GlobalUtility/Bouton.h"
class LayoutChoiceLoop
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	Bouton azertyButton;
	Bouton qwertyButton;

	Sentence* necroCrystalText;

public:
	LayoutChoiceLoop();
	~LayoutChoiceLoop();

	void initialize(sf::Vector2i& windowDimensions, TextManager& textManager);
	int update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition); //0 nothing | 1 Azerty | 2 Qwerty
	void draw(sf::RenderWindow* window);

};

