#pragma once
#include <vector>
#include "Characters/Character.h"
#include "Characters/Necromancer.h"
#include "Characters/Enemy/Enemy.h"
#include "Characters/SkeletonHandler.h"
#include "Effects/VFXHandler.h"
#include "Projectiles/ProjectilesHandler.h"
#include "World/Map.h"
#include "World/MapData.h"
#include "Utilities/CameraService.h"
#include "Utilities/FrameRate.h"
#include "Utilities/HitboxDisplay.h"
#include "Utilities/GameTimer.h"
#include "Utilities/RandomLSFR.h"
#include"../GlobalUtility/TextManager.h"

class GameLoop
{
protected:
	std::vector<Character*> characters; //characters[0] is always supposed to be the necromancer
	ProjectilesHandler projectileHandler;
	HitboxDisplay hitboxDisplay;
	Map map;
	CameraService cameraService;  
	GameTimer gameTimer;
	SkeletonHandler skeltonHandler;
	VFXHandler vFXHandler;

	FrameRate frameRate;

	RandomLSFR randomLSFR;
	int currentWave;
	void LoadWave(MapData* mapData, sf::Vector2i& windowDimensions);

	int waveInstruction;
	float waveSpawnTimer;    //for wave Instruction 2
	float waveSpawnCooldown;
public:
	GameLoop(sf::Vector2i windowSize);
	~GameLoop();

	void initialize(sf::Vector2i& windowDimensions,TextManager& textManager, std::string& mapFileName);
	int update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition, std::string timerString);
	// 0 : R A S
	// 1 : win
	// 2 : necro is dead
	void draw(sf::RenderWindow* window);
};

