#include "Sentence.h"

sf::IntRect Sentence::LetterToRect(char c) const
{
	if(c>='a' && c<='z')
		return sf::IntRect((c-'a')*charWidth + 1, 2, 5, 6);
	if (c >= 'A' && c <= 'Z')
		return sf::IntRect((c - 'A' + 26) * charWidth + 1, 1, 5, 7);
	if (c >= '0' && c <= '9')
		return sf::IntRect((c - '0' + 52) * charWidth + 1, 1, 5, 7);

	if(c == '.')
		return sf::IntRect(62 * charWidth + 2, 5, 3, 3);
	if (c == '!')
		return sf::IntRect(63 * charWidth + 1, 1, 5, 7);
	if (c == '?')
		return sf::IntRect(64 * charWidth + 1, 1, 5, 7);
	if (c == ' ')
		return sf::IntRect(65 * charWidth + 1, 1, 5, 7);
	return sf::IntRect(0, 0, 0, 0);
}

Sentence::Sentence() :
	sprites(nullptr), size(0) //size compte les espaces
	,charHeight(8),charWidth(6)
{
}


void Sentence::Initialise(std::string string, sf::Texture& texture)
{
	size = string.length();
	sprites = new sf::Sprite[size];
	for (size_t i = 0; i < size; ++i)
	{
		sprites[i].setTexture(texture);
		sprites[i].setTextureRect(LetterToRect(string[i]));
		sprites[i].setOrigin(0,sprites[i].getTextureRect().height);
	}
}

void Sentence::Update(float scale, sf::Vector2f position) //la position est en bas à gauche de la première lettre
{
	if (size > 0)
	{
		sprites[0].setScale(scale, scale);
		sprites[0].setPosition(position);
	}
	for (size_t i = 1; i < size; ++i)
	{
		sprites[i].setScale(scale, scale);
		sprites[i].setPosition(sprites[i-1].getPosition() + sf::Vector2f(sprites[i-1].getGlobalBounds().width, 0));
	}
}

void Sentence::Draw(sf::RenderWindow* window) const
{
	for (size_t i = 0; i < size; ++i)
	{
		window->draw(sprites[i]);
	}
}

