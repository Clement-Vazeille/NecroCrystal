#include "CutsceneManager.h"

CutsceneManager::CutsceneManager() :
	cutsceneIndex(0)
{
}

CutsceneManager::~CutsceneManager()
{
	for (auto& cutscene : tutorial)
	{
		delete cutscene;
	}
}

void CutsceneManager::initialize(sf::Vector2i& windowDimensions, TextManager& textManager)
{
	Cutscene* tutorial1 = new Cutscene();
	tutorial1->Initialize(windowDimensions, "Assets/Cutscenes/BasicScene.png");
	tutorial1->AddAText("test", textManager, sf::Vector2f(windowDimensions.x * 0.6f, windowDimensions.y * 0.2f));
	tutorial.push_back(tutorial1);
}

int CutsceneManager::update(float deltaTime, sf::Vector2i& windowDimensions)
{
	if (tutorial.at(cutsceneIndex)->Update(deltaTime, windowDimensions) == 1)
	{
		if (++cutsceneIndex >= tutorial.size())
		{
			cutsceneIndex = 0;
			return 1;
		}
	}
	return 0;
}

void CutsceneManager::draw(sf::RenderWindow* window)
{
	tutorial.at(cutsceneIndex)->Draw(window);
}