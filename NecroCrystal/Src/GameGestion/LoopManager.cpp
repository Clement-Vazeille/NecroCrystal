#include "LoopManager.h"
#include <iostream>

void LoopManager::LoadLevel(sf::Vector2i& windowDimensions)
{
	if (gameLoop != nullptr)
	{
		delete gameLoop;
	}
	gameLoop = new GameLoop(windowDimensions);
	gameLoop->initialize(windowDimensions, textManager, levelsMapFiles.at(actualLevel));
}

LoopManager::LoopManager(sf::Vector2f windowSize) :
	gameLoop(nullptr), state(4),
	pauseTimer(0),pauseCooldown(800),
	actualLevel(0)
{
}

LoopManager::~LoopManager()
{
	if (gameLoop != nullptr)
	{
		delete gameLoop;
	}
}

void LoopManager::initialize(sf::Vector2i& windowDimensions)
{
	textManager.Initialize(); //important to initialize GlobalUtility services before initializing Loops

	pauseLoop.initialize(windowDimensions,textManager);
	clearLoop.initialize(windowDimensions,textManager);
	looseLoop.initialize(windowDimensions,textManager);

	levelsMapFiles.at(0)=("Assets/World/NecroDungeon/Level1.map");
	this->LoadLevel(windowDimensions);
	
	mouseCursor.Load(windowDimensions);
}

bool LoopManager::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	mouseCursor.Update(mousePosition, windowDimensions);
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
	{
		if (pauseLoop.update(deltaTime, windowDimensions, mousePosition))
			return true;
	}
	if(state == 2)
	{
		int loopState = clearLoop.update(deltaTime, windowDimensions, mousePosition);
		if (loopState == 1) //1 mean player leave the game
			return true;

	}
	if(state == 3)
	{
		int loopState = looseLoop.update(deltaTime, windowDimensions, mousePosition);
		if (loopState == 1) //1 mean player leave the game
			return true;
		if (loopState == 2) //2 mean player retry the level
		{
			this->LoadLevel(windowDimensions);
			state = 4;
		}
	}
	if(state == 4)
	{
		timer.Add(deltaTime);
		int gameState = gameLoop->update(deltaTime, windowDimensions, mousePosition,timer.ToMiniString()); //0 if RAS
		if (gameState == 1)//win for player
		{
			clearLoop.setTimer(timer.ToString(), textManager);
			state = 2;
		}
		if (gameState == 2)//player is dead
			state = 3;
	}

	return false;
}

void LoopManager::draw(sf::RenderWindow* window)
{
	if (state == 1|| state == 2 || state == 3 || state == 4)
		gameLoop->draw(window);
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

	mouseCursor.Draw(window);
}
