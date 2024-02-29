#include "Cutscene.h"
#include <iostream>

Cutscene::Cutscene() :
	hasMouseBeenUnclicked(false)
{
}

Cutscene::~Cutscene()
{
	for (auto& text : texts)
	{
		if (text != nullptr)
			delete text;
	}
}

void Cutscene::Initialize(sf::Vector2i& windowDimensions, std::string backgroundFileName)
{
	if (texture.loadFromFile(backgroundFileName)) 
	{
		backgroundSprite.setTexture(texture);
		backgroundSprite.setScale(2.f * windowDimensions.x / 1920.f, 2.f * windowDimensions.y / 1080.f);
		backgroundSprite.setPosition(0, 0);
	}
	else
	{
		std::cout << "Cutscene Load failed" << std::endl;
	}
}

void Cutscene::AddAText(std::string text, TextManager& textManager, sf::Vector2f position)
{
	Sentence* sentence = textManager.MakeSentence(text);
	texts.push_back(sentence);
	textsPositions.push_back(position);
}

int Cutscene::Update(float deltaTime, sf::Vector2i& windowDimensions)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		hasMouseBeenUnclicked = true;

	backgroundSprite.setScale(2.f * windowDimensions.x / 1920.f, 2.f * windowDimensions.y / 1080.f); 
	backgroundSprite.setPosition(0, 0);

	for(int i = 0;i<texts.size();i++)
	{
		texts.at(i)->Update(14.f * windowDimensions.x / 1980.f, textsPositions.at(i)); 
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && hasMouseBeenUnclicked)
	{
		hasMouseBeenUnclicked = false;
		return 1;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && hasMouseBeenUnclicked)
	{
		hasMouseBeenUnclicked = false;
		return 2;
	}
	return 0;
}

void Cutscene::Draw(sf::RenderWindow* window)
{
	window->draw(backgroundSprite);
	for (auto& text : texts)
	{
		text->Draw(window);
	}
}
