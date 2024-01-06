#include "LoopManager.h"
#include <iostream>

LoopManager::LoopManager(sf::Vector2f windowSize) :
	gameLoop(sf::Vector2f(windowSize)),state(4),
	pauseTimer(0),pauseCooldown(800)
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
	//activate/desactivate loops
	if (pauseTimer <= pauseCooldown)
		pauseTimer += deltaTime;
	if (state == 4 && sf::Keyboard::isKeyPressed(sf::Keyboard::P) && pauseTimer >= pauseCooldown) //TODO remplacer le 4 par une variable active level
	{
		pauseTimer = 0;
		std::cout << "pause" << std::endl;
		state = 1;
	}
	if (state == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::P) && pauseTimer >= pauseCooldown)
	{
		pauseTimer = 0;
		state = 4;
	}

	//update of activated loops
	if(state == 4)
		gameLoop.update(deltaTime,windowDimensions,mousePosition);
}

void LoopManager::draw(sf::RenderWindow* window)
{
	if(state == 4 || state == 1)
		gameLoop.draw(window);
}
