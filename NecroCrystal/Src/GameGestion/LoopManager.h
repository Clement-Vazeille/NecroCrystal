#pragma once

#include "../Game/GameLoop.h"
#include "../BasicLoops/PauseLoop.h"
#include "../BasicLoops/ClearLoop.h"
#include "../BasicLoops/LooseLoop.h"
#include "../BasicLoops/MainMenuLoop.h"
#include "../BasicLoops/VictoryLoop.h"
#include "../GlobalUtility/TextManager.h"
#include "../GlobalUtility/Timer.h"
#include "MouseCursor.h"

class LoopManager
{
protected:
	PauseLoop pauseLoop;
	ClearLoop clearLoop;
	LooseLoop looseLoop;
	VictoryLoop victoryLoop;
	MainMenuLoop mainMenuLoop;
	GameLoop* gameLoop;
	TextManager textManager;
	Timer timer;
	MouseCursor mouseCursor;

	int state;
	// 0 for main menu
	// 1 for pause
	// 2 for stage clear
	// 3 for lose
	// 4 for ingame
	// 5 for finnish screan

	int actualLevel;
	std::array<std::string, 2> levelsMapFiles;

	//l'upadate de main menu, pause et win est un bool sur si on doit quitt� cet �cran

	float pauseTimer;
	float pauseCooldown;

	void LoadLevel(sf::Vector2i&); //load the actual level
public:
	LoopManager(sf::Vector2f windowSize);
	~LoopManager();

	void initialize(sf::Vector2i& windowDimensions);    //TODO mettre une maj aux la fonction ....
	bool update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition); //true if game is closed
	//TODO : make that loop can only be changed once per frame
	void draw(sf::RenderWindow* window);
};

