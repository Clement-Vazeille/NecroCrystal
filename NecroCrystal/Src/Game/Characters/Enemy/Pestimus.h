#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "../../Utilities/CameraService.h"
#include "../../Utilities/Animation.h"
#include "Enemy.h"
#include "../../World/Map.h"
#include "../../Projectiles/ProjManagers/LaserManager.h"
#include "../../Projectiles/ProjManagers/FlaqueManager.h"
class Pestimus : public Enemy
{
protected:
	std::array<Animation, 5> animations;

	std::vector<LaserManager*> laserManagers;
	std::vector<FlaqueManager*> flaqueManagers;

	float newAttackTimer;
	float newAttackCooldown;
	float newMovementTimer;
	float newMovementCooldown;

	sf::Vector2f direction;

	bool isFacingRight;

	bool willStartNewPhase;
	int phaseNumber;

	float laserDuration;
	float circuDuration;
	float flaqueDuration;

	float phaseSwitchDuration;

	sf::Vector2f circuInitialPosition;
	sf::Vector2f circuTarget;
	sf::Vector2f circuTargetDrift;
	bool movementYSwitch;
	bool movementXSwitch;

	float poisonDotThrowTimer;
	float poisonDotThrowCooldown;
	bool isLastPoisonDotSwitched;

	enum AttackAction {
		Laser = 0,
		Bulles = 1,
		Circu = 2,
		Flaques = 3,
		PhaseSwitchAttack = 4
	};
	AttackAction currentAttack;

	enum MovementAction {
		Avance = 0,
		Recule = 1,
		FuiteCircu = 2,
		Imo = 3,
		PhaseSwitchMovement = 4
	};
	MovementAction currentMovement;

	void SelectNewAttackAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR, CameraService& cameraService);
	void SelectNewMovementAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR);
	void Flip(void);

public:
	Pestimus();
	~Pestimus();

	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters,
		RandomLSFR& randomLSFR, VFXHandler& vFXHandler);

	Projectile* LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters, VFXHandler& vFXHandler);

	const sf::Sprite& getSprite(void) const;

	bool TakeDamage(int hp) override;
	int GiveWaveInstruction(void) const override;
};

