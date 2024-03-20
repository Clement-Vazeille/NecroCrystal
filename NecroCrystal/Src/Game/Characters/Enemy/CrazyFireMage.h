#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "../../Utilities/CameraService.h"
#include "../../Utilities/Animation.h"
#include "Enemy.h"
#include "../../World/Map.h"
class CrazyFireMage : public Enemy
{
protected:
	std::array<Animation, 4> animations;

	float newActionTimer;
	float newActionCooldown;
	sf::Vector2f direction;

	float dashSpeed;
	float furySpeed;

	float dashTime;
	float furyDashTime;

	bool isFacingRight;

	bool isCrazy;
	int crazyHealthStart;

	bool isInvincible;
	float invulnerabilityTimer;
	float invulnerabilityDuration;

	float dashFireCooldown;
	float dashFireTimer;

	enum Action {
		Tourniquet = 0,
		Dash = 1,
		Explosion = 2,
		Fury = 3
	};
	Action currentAction;
	void SelectNewAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR);
	void Flip(void);

	void SpawnParticules(void) const;
public:
	CrazyFireMage();
	~CrazyFireMage();

	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters,
		RandomLSFR& randomLSFR, VFXHandler& vFXHandler);

	Projectile* LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters);

	const sf::Sprite& getSprite(void) const;

	bool TakeDamage(int hp) override;
};

