#pragma once
#include <SFML/Graphics.hpp>
#include <string>

//class used to show a text on screen
class Sentence
{
protected:
	sf::Sprite* sprites;
	int size;
	sf::IntRect LetterToRect(char c) const;

	int charWidth;
	int charHeight; //Rect size on texture png
public:
	Sentence();

	void Initialise(std::string string, sf::Texture& texture);
	void ChangeText(std::string string); //reset position
	void Update(float scale, sf::Vector2f position); //la position est en haut � gauche de la premi�re lettre

	void Draw(sf::RenderWindow* window) const;
};

