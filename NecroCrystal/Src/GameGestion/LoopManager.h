#pragma once

#include "../Game/GameLoop.h"
#include "../BasicLoops/PauseLoop.h"
#include "../BasicLoops/ClearLoop.h"
#include "../BasicLoops/LooseLoop.h"
#include "../GlobalUtility/TextManager.h"
#include "../GlobalUtility/Timer.h"
#include "MouseCursor.h"

class LoopManager
{
protected:
	PauseLoop pauseLoop;
	ClearLoop clearLoop;
	LooseLoop looseLoop;
	GameLoop gameLoop;
	TextManager textManager;
	Timer timer;
	MouseCursor mouseCursor;

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

	void initialize(sf::Vector2i& windowDimensions);    //TODO mettre une maj aux la fonction ....
	bool update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition); //true if game is closed
	void draw(sf::RenderWindow* window);
};

