#pragma once
#include <SFML/Graphics.hpp>
#include "../../Utilities/CameraService.h"
#include "../../Utilities/LoopAnimation.h"
#include "Enemy.h"
#include "../../World/Map.h"

class FireMage : public Enemy
{
protected:
	LoopAnimation loopAnimation;
	float fireBallTimer;
	float fireBallRefreshTime;

public:
	FireMage();
	~FireMage();

	void Load(sf::Vector2i& windowDimensions,sf::Vector2f position);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime,Map& map,std::vector<Character*>& characters);

	Projectile* LaunchProjectile(float deltaTime, sf::Texture* projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters);

	sf::Sprite& getSprite(void) const;
};

