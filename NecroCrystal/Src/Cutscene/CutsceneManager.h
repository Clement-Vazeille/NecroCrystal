#pragma once
#include "Cutscene.h"
class CutsceneManager
{
protected:
	std::vector<Cutscene*> tutorial;
	int cutsceneIndex;
public:
	CutsceneManager();
	~CutsceneManager();

	void initialize(sf::Vector2i& windowDimensions, TextManager& textManager);
	int update(float deltaTime, sf::Vector2i& windowDimensions); //0 nothing | 1 cutscenes finished
	void draw(sf::RenderWindow* window);
};

