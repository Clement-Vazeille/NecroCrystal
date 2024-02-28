#pragma once

#include <SFML/Graphics.hpp>
#include "Sentence.h"

class Bouton
{
protected:
	Sentence* boutonText;
	sf::RectangleShape hitbox; //on va activer son contour et le mettre en blanc
	sf::Vector2f textPosistionRatio;

	bool hasClickBeenUnpressed;

	float scale;
public:
	Bouton();
	~Bouton();
	void Initialise(Sentence* sentence, sf::Vector2f hitboxPosition, sf::Vector2f hitboxSize, sf::Vector2i windowDimensions,
		sf::Vector2f textPosistionRatio );
	bool Update(float textScale, sf::Vector2i windowDimensions, sf::Vector2f mousePosition); //true if button is clicked, false if it isn't
	void Reset(void);//put the click check to false
	void Draw(sf::RenderWindow* window) const;
};

