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
	gameLoop(nullptr), state(0),
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

	mainMenuLoop.initialize(windowDimensions, textManager);
	pauseLoop.initialize(windowDimensions,textManager);
	clearLoop.initialize(windowDimensions,textManager);
	looseLoop.initialize(windowDimensions,textManager);
	victoryLoop.initialize(windowDimensions, textManager);
	cutsceneManager.initialize(windowDimensions, textManager);

	levelsMapFiles.at(0)=("Assets/World/NecroDungeon/Level1.map");
	levelsMapFiles.at(1) = ("Assets/World/NecroDungeon/Level2.map");
	this->LoadLevel(windowDimensions);
	
	mouseCursor.Load(windowDimensions);
}

bool LoopManager::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	mouseCursor.Update(mousePosition, windowDimensions);
	//activate/desactivate loops
	if (pauseTimer <= pauseCooldown)
		pauseTimer += deltaTime;
	if (state == 4 && (sf::Keyboard::isKeyPressed(sf::Keyboard::P)||sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && pauseTimer >= pauseCooldown) //TODO remplacer le 4 par une variable active level
	{
		pauseTimer = 0;
		std::cout << "pause" << std::endl;
		state = 1;
	}
	if (state == 1 && (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && pauseTimer >= pauseCooldown)
	{
		pauseTimer = 0;
		state = 4;
		pauseLoop.ResetButton();
	}

	//update of activated loops
	if (state == 1)
	{
		int loopState = pauseLoop.update(deltaTime, windowDimensions, mousePosition);
		if (loopState == 1) //means quit game
			return true;
		if (loopState == 2) //means return to main menu
		{
			timer.Reset();
			actualLevel = 0;
			state = 0;
		}
	}
	if(state == 2)
	{
		int loopState = clearLoop.update(deltaTime, windowDimensions, mousePosition);
		if (loopState == 1) //1 mean player leave the game
			return true;
		if (loopState == 2) //2 mean player continue
		{
			actualLevel++;
			if(actualLevel<levelsMapFiles.size())
			{
				this->LoadLevel(windowDimensions);
				state = 4;
			}
			else
			{
				victoryLoop.setTimer(timer.ToString(), textManager);
				state = 5;
			}
		}

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
		if (loopState == 3) //3 means return to main menu
		{
			timer.Reset();
			actualLevel = 0;
			state = 0;
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
	if (state == 0)
	{
		int loopState = mainMenuLoop.update(deltaTime, windowDimensions, mousePosition);
		if (loopState == 1) //1 mean player leave the game
			return true;
		if (loopState == 2) //2 mean player launch game
		{
			this->LoadLevel(windowDimensions);
			state = 4;
		}
		if (loopState == 3) //2 mean player watch tutorial
			state = 6;
	}
	if (state == 6)
	{
		int loopState = cutsceneManager.update(deltaTime, windowDimensions);
		if (loopState == 1)  // means end of tutorial
		{
			state = 0;
		}
	}

	if (state == 5)
	{
		int loopState = victoryLoop.update(deltaTime, windowDimensions, mousePosition);
		if (loopState == 1) //1 mean player leave the game
			return true;
		if (loopState == 2) //2 mean player go to main menu
		{
			timer.Reset();
			actualLevel = 0;
			state = 0;
		}
	}

	return false;
}

void LoopManager::draw(sf::RenderWindow* window)
{
	if (state == 1|| state == 2 || state == 3 || state == 4)
		gameLoop->draw(window);
	if (state == 0)
	{
		mainMenuLoop.draw(window);
	}
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
	if (state == 6)
	{
		cutsceneManager.draw(window);
	}
	if (state == 5)
	{
		victoryLoop.draw(window);
	}

	mouseCursor.Draw(window);
}
