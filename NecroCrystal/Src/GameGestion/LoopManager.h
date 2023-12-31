#pragma once

#include "../Game/GameLoop.h"
#include "../Pause/PauseLoop.h"
#include "../WinLoose/ClearLoop.h"
#include "../WinLoose/LooseLoop.h"
class LoopManager
{
protected:
	PauseLoop pauseLoop;
	ClearLoop clearLoop;
	LooseLoop looseLoop;
	GameLoop gameLoop;
	int state;
	// 0 for main menu
	// 1 for pause
	// 2 for win
	// 3 for lose
	// 4 for level 1

	//l'upadate de main menu, pause et win est un bool sur si on doit quitt� cet �cran

	float pauseTimer;
	float pauseCooldown;
public:
	LoopManager(sf::Vector2f windowSize);
	~LoopManager();

	void initialize(sf::Vector2i& windowDimensions);
	void update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition);
	void draw(sf::RenderWindow* window);
};

