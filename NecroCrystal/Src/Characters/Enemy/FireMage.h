#pragma once
#include <SFML/Graphics.hpp>
#include "../../Utilities/CameraService.h"
#include "../../Utilities/LoopAnimation.h"
#include "Enemy.h"
#include "../../World//Map.h"
#include "../../Projectiles/ProjectilesHandler.h"

class FireMage : public Enemy
{
protected:
	LoopAnimation loopAnimation;

public:
	FireMage();
	~FireMage();

	void Load(sf::Vector2i& windowDimensions,sf::Vector2f position);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime,Map& map);

	void FireBall(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime,ProjectilesHandler projectileHandler);

	sf::Sprite& getSprite(void) const;
};

