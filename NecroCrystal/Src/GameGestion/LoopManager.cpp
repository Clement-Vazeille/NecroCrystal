#include "LoopManager.h"

LoopManager::LoopManager(sf::Vector2f windowSize) :
	gameLoop(sf::Vector2f(windowSize)),state(3)
{
}

LoopManager::~LoopManager()
{
}

void LoopManager::initialize(sf::Vector2i& windowDimensions)
{
	gameLoop.initialize(windowDimensions); //TODO gameLoop prend en entrée un fichier map
}

void LoopManager::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	if(state == 3)
		gameLoop.update(deltaTime,windowDimensions,mousePosition);
}

void LoopManager::draw(sf::RenderWindow* window)
{
	if(state == 3)
		gameLoop.draw(window);
}
