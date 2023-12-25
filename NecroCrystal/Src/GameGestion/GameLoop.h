#pragma once
#include "../Characters/Character.h"
#include "../Projectiles/ProjectilesHandler.h"
#include <vector>
#include "../World/Map.h"
#include "../Utilities/CameraService.h"
#include "../Utilities/FrameRate.h"

class GameLoop
{
protected:
	std::vector<Character*> characters; //characters[0] is always supposed to be the necromancer
	ProjectilesHandler projectileHandler;
	Map map;
	CameraService cameraService;
	sf::Clock clock;        //TODO mettre la clock en paus quand on sort de la GameLoop
	FrameRate frameRate;

public:
	GameLoop();
	~GameLoop();

	void initialize();
	void update();
	void draw();
};

