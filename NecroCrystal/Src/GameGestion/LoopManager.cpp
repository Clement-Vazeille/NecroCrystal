#include "LoopManager.h"
#include <iostream>

LoopManager::LoopManager(sf::Vector2f windowSize) :
	gameLoop(windowSize), state(4),
	pauseTimer(0),pauseCooldown(800)
{
}

LoopManager::~LoopManager()
{
}

void LoopManager::initialize(sf::Vector2i& windowDimensions)
{
	textManager.Initialize(); //important to initialize GlobalUtility services before initializing Loops

	pauseLoop.initialize(windowDimensions,textManager); 
	clearLoop.initialize(windowDimensions,textManager);
	looseLoop.initialize(windowDimensions,textManager);
	gameLoop.initialize(windowDimensions,textManager); //TODO gameLoop prend en entr�e un fichier map
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
	if (state == 1)
		pauseLoop.update(deltaTime, windowDimensions, mousePosition);
	if(state == 2)
		clearLoop.update(deltaTime, windowDimensions, mousePosition);
	if(state == 3)
		looseLoop.update(deltaTime, windowDimensions, mousePosition);
	if(state == 4)
	{
		timer.Add(deltaTime);
		int gameState = gameLoop.update(deltaTime, windowDimensions, mousePosition,timer.ToMiniString()); //0 if RAS
		if (gameState == 1)//win for player
		{
			clearLoop.setTimer(timer.ToString(), textManager);
			state = 2;
		}
		if (gameState == 2)//player is dead
			state = 3;
	}
}

void LoopManager::draw(sf::RenderWindow* window)
{
	if (state == 1|| state == 2 || state == 3 || state == 4)
		gameLoop.draw(window);
	if (state == 1)
	{
		pauseLoop.draw(window);
	}
	if (state == 2)
	{
		clearLoop.draw(window);
	}
	if (state == 3)
	{
		looseLoop.draw(window);
	}
}
