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
	std::array<Animation, 6> animations;

	float newActionTimer;
	float newActionCooldown;
	sf::Vector2f direction;


	float lancerTime;
	float marcherTime;
	float prayTime;
	
	float jumpTime;
	float jumpTimer;
	float jumpAirTime;
	float jumpSpeed;
	bool hasNotJumpAttacked;

	float shieldingSpeed;
	float shieldTime;
	float shieldPrepTime;
	float shieldingTimer;

	float hammerThrowTimer;
	int throwNumber; //captain rotate through 3 differents throws the number 0 aims too high, the number 1 aims for necro and 2 aims too low

	bool isFacingRight;

	bool willStartPraying;
	int prayCounter;

	std::array<float,3> invincibilityStarters;
	int invincibilityStartersIndex;

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

	int pickAnimation(void) const;

public:
	KnightCaptain();
	~KnightCaptain();

	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters,
		RandomLSFR& randomLSFR, VFXHandler& vFXHandler);

	Projectile* LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters, VFXHandler& vFXHandler);

	const sf::Sprite& getSprite(void) const;

	bool TakeDamage(int hp) override;
};

