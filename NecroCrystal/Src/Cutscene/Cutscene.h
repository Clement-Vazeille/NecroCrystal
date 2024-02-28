#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../GlobalUtility/TextManager.h"
#include "../GlobalUtility/Sentence.h"
class Cutscene
{
protected:
	bool hasMouseBeenUnclicked;

	sf::Texture texture; //a 960-540 pixel png
	sf::Sprite backgroundSprite;

	std::vector<Sentence*> texts;
	std::vector<sf::Vector2f> textsPositions;
public:
	Cutscene();
	~Cutscene();

	void Initialize(sf::Vector2i& windowDimensions, std::string backgroundFileName);
	void AddAText(std::string text, TextManager& textManager, sf::Vector2f position);
	int Update(float deltaTime, sf::Vector2i& windowDimensions); //0 nothing | 1 cutscene finished
	void Draw(sf::RenderWindow* window);
};

