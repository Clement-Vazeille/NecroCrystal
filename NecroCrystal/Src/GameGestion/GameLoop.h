#pragma once
#include <vector>
#include "../Characters/Character.h"
#include "../Characters/Necromancer.h"
#include "../Characters/Enemy/Enemy.h"
#include "../Characters/Enemy/FireMage.h"
#include "../Projectiles/ProjectilesHandler.h"
#include "../World/Map.h"
#include "../World/MapData.h"
#include "../Utilities/CameraService.h"
#include "../Utilities/FrameRate.h"
#include "../Utilities/HitboxDisplay.h"

class GameLoop
{
protected:
	std::vector<Character*> characters; //characters[0] is always supposed to be the necromancer
	ProjectilesHandler projectileHandler;
	HitboxDisplay hitboxDisplay;
	Map map;
	CameraService cameraService;  

	//TODO mettre une clock du temps de jeu
	FrameRate frameRate;

public:
	GameLoop(sf::Vector2f windowSize);
	~GameLoop();

	void initialize(sf::Vector2i& windowDimensions);
	void update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition);
	void draw(sf::RenderWindow* window);
};

