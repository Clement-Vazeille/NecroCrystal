#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "../../Utilities/CameraService.h"
#include "../../Utilities/Animation.h"
#include "Enemy.h"
#include "../../World/Map.h"
class Pestimus : public Enemy
{
protected:
	std::array<Animation, 5> animations;

	float newAttackActionTimer;
	float newAttackActionCooldown;
	float newMovementActionTimer;
	float newMovementActionCooldown;

	sf::Vector2f direction;

	bool isFacingRight;

	bool willStartNewPhase;
	int phaseNumber;


	enum AttackAction {
		Laser = 0,
		Bulles = 1,
		Circu = 2,
		Flaques = 3,
		PhaseSwitchMovement = 4
	};
	AttackAction currentAttack;

	enum MovementAction {
		Avance = 0,
		Recule = 1,
		FuiteCircu = 2,
		Imo = 3,
		PhaseSwitchAttack = 4
	};
	MovementAction currentMovement;

	void SelectNewAttackAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR);
	void SelectNewMovementAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR);
	void Flip(void);

public:
	Pestimus();
	~Pestimus();

	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters,
		RandomLSFR& randomLSFR, VFXHandler& vFXHandler);

	Projectile* LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters);

	const sf::Sprite& getSprite(void) const;

	bool TakeDamage(int hp) override;
};

