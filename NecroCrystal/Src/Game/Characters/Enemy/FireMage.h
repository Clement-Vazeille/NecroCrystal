#pragma once
#include <SFML/Graphics.hpp>
#include "../../Utilities/CameraService.h"
#include "../../Utilities/Animation.h"
#include "Enemy.h"
#include "../../World/Map.h"

class FireMage : public Enemy
{
protected:
	Animation loopAnimation;
	float fireBallTimer;
	float fireBallRefreshTime;

	float newDirectionTimer;
	float newDirectionCooldown;
	sf::Vector2f direction;

	float fearDistance;

public:
	FireMage();
	~FireMage();

	void Load(sf::Vector2i& windowDimensions,sf::Vector2f position);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime,Map& map,std::vector<Character*>& characters, 
		RandomLSFR& randomLSFR, VFXHandler& vFXHandler);

	Projectile* LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters, VFXHandler& vFXHandler);

	const sf::Sprite& getSprite(void) const;
};

