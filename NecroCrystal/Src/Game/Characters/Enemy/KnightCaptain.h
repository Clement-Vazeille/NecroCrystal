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
	std::array<Animation, 5> animations;

	float newActionTimer;
	float newActionCooldown;
	sf::Vector2f direction;

	float shieldingSpeed;
	float jumpBaseSpeed;

	float lancerTime;
	float jumpTime;
	float marcherTime;
	float prayTime;
	
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

public:
	KnightCaptain();
	~KnightCaptain();

	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters,
		RandomLSFR& randomLSFR, VFXHandler& vFXHandler);

	Projectile* LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters);

	const sf::Sprite& getSprite(void) const;

	bool TakeDamage(int hp) override;
};

