#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "../../Utilities/CameraService.h"
#include "../../Utilities/Animation.h"
#include "Enemy.h"
#include "../../World/Map.h"
class KnightCaptain : public Enemy
{

protected:
	std::array<Animation, 1> animations;

	float newActionTimer;
	float newActionCooldown;
	sf::Vector2f direction;

	float shieldingSpeed;

	bool isFacingRight;

	enum Action {
		Marcher = 0,
		Lancer = 1,
		Jump = 2,
		Bouclier = 3,
		Priere = 4
	};
	Action currentAction;
	void SelectNewAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR);
	void Flip(void);

public:
	KnightCaptain();
	~KnightCaptain();

	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters,
		RandomLSFR& randomLSFR, VFXHandler& vFXHandler);

	Projectile* LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters);

	const sf::Sprite& getSprite(void) const;

};

